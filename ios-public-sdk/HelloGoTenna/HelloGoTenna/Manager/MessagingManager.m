//
//  MessagingManager.m
//  HelloGoTenna
//
//  Created by GoTenna on 7/26/17.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import "MessagingManager.h"
#import "ContactManager.h"
#import "QueueManager.h"
#import "Group.h"
#import "DemoConstants.h"
#import "Message.h"
@import GoTennaSDK;

@implementation MessagingManager

# pragma mark - Init

+ (instancetype)sharedManager {
    static MessagingManager *manager = nil;
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        manager = [[MessagingManager alloc] init];
    });
    return manager;
}

- (instancetype)init {
    self = [super init];
    
    if (self) {
        __weak typeof(self) weakSelf = self;
        
        [[GTCommandCenter shared] setOnIncomingMessage:^(GTMessageData *messageData) {
            [weakSelf handleIncomingMessage:messageData];
        }];
        
        [[GTCommandCenter shared] setOnGroupCreated:^(GTGroupCreationMessageData *messageData) {
            [weakSelf handleIncomingGroupCreation:messageData];
        }];
    }
    
    return self;
}

# pragma mark - Incoming Messages

- (void)handleIncomingMessage:(GTMessageData *)response {
    
    GTBaseMessageData *baseMessageData = [GTDataSerializer parseIncomingMessageData:response.commandData withMessageData:response];
    
    if (baseMessageData) {
        baseMessageData.addresseeGID = response.addressedGID;
        baseMessageData.messageSentDate = response.messageSentDate;
        
        Message *message = [[Message alloc] initWithData:(GTTextOnlyMessageData *)baseMessageData];
        GTGIDType gidType = [GIDManager gidTypeForGID:baseMessageData.addresseeGID];
        
        switch (gidType) {
            case ShoutGID:
                if ([self.delegate respondsToSelector:@selector(messagingManager:didReceiveIncomingShout:)]) {
                    [self.delegate messagingManager:self didReceiveIncomingShout:message];
                }
                break;
            case OneToOneGID:
                if ([self.delegate respondsToSelector:@selector(messagingManager:didReceiveIncomingMessage:)]) {
                    [self.delegate messagingManager:self didReceiveIncomingMessage:message];
                }
                break;
            case GroupGID:
                if ([self.delegate respondsToSelector:@selector(messagingManager:didReceiveIncomingMessage:)]) {
                    [self.delegate messagingManager:self didReceiveIncomingMessage:message];
                }
                break;
            default:
                break;
        }
    }
}

- (void)handleIncomingGroupCreation:(GTGroupCreationMessageData *)messageData {
    NSNumber *groupGID = [messageData groupGID];
    NSMutableArray<Contact *> *groupMembers = [NSMutableArray array];
    
    for (NSNumber *gid in [messageData groupAddressees]) {
        Contact *contact = [[ContactManager sharedManager] findContactWithGID:gid];
        
        if (contact) {
            [groupMembers addObject:contact];
        }
    }
    
    Group *group = [[Group alloc] initWithGID:groupGID groupMembers:groupMembers];
    [[NSNotificationCenter defaultCenter] postNotificationName:kGroupCreatedNotification object:nil userInfo:@{ kGroupCreatedKey : group }];
}

# pragma mark - Outgoing Messages

- (void)sendBroadcastMessage:(Message *)message {
    void (^onError)(NSError *error) = ^(NSError *error) {
        if (error && [error isEqual:[GTError dataRateLimitExceeded]]) {
            [[QueueManager sharedManager] addMessageToQueue:message];
        } else {
            if ([self.delegate respondsToSelector:@selector(messagingManager:didFailSendingMessage:)]) {
                [self.delegate messagingManager:self didFailSendingMessage:message];
            }
        }
    };
    
    void (^onResponse)(GTResponse *) = ^(GTResponse *response) {
        if ([response responsePositive]) {
            // Hop count not set for broadcasts
            if ([self.delegate respondsToSelector:@selector(messagingManager:didSendOutgoingMessage:)]) {
                [self.delegate messagingManager:self didSendOutgoingMessage:message];
            }
            [[QueueManager sharedManager] removeMessageFromQueue:message];
        }
    };
    
    [[GTCommandCenter shared] sendBroadcast:[message toBytes] toGID:[GIDManager shoutGID] onResponse:onResponse onError:onError];
}

- (void)sendMessage:(Message *)message {    
    void (^onError)(NSError *error) = ^(NSError *error) {
        if (error && [error isEqual:[GTError dataRateLimitExceeded]]) {
            [[QueueManager sharedManager] addMessageToQueue:message];
        } else {
            if ([self.delegate respondsToSelector:@selector(messagingManager:didFailSendingMessage:)]) {
                [self.delegate messagingManager:self didFailSendingMessage:message];
            }
        }
    };
    
    void (^onResponse)(GTResponse *) = ^(GTResponse *response) {
        if ([response responsePositive]) {
            GTGIDType type = [GIDManager gidTypeForGID:message.receiverGID];
            
            if (type == OneToOneGID) {
                [message setHopCount:response.hopCount];
            }
            if ([self.delegate respondsToSelector:@selector(messagingManager:didSendOutgoingMessage:)]) {
                [self.delegate messagingManager:self didSendOutgoingMessage:message];
            }
            [[QueueManager sharedManager] removeMessageFromQueue:message];
        }
    };
    
    [[GTCommandCenter shared] sendMessage:[message toBytes] toGID:message.receiverGID fromGID:message.senderGID onResponse:onResponse onError:onError];
}

# pragma mark - Helpers

@end
