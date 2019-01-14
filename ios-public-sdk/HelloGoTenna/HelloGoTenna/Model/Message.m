//
//  Message.m
//  HelloGoTenna
//
//  Created by GoTenna on 7/25/17.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import "Message.h"
#import "ContactManager.h"
#import "Contact.h"
@import GoTennaSDK;

@interface Message()
@property (nonatomic, strong) NSNumber *senderGID;
@property (nonatomic, copy) NSString *text;
@property (nonatomic, strong) NSNumber *receiverGID;
@property (nonatomic, strong) NSDate *sentDate;
@property (nonatomic, strong) NSString *senderInfo;
@property (nonatomic) MessageStatus status;
@end

@implementation Message

# pragma mark - Init

- (instancetype)initWithSenderGID:(NSNumber *)senderGID
                      receiverGID:(NSNumber *)receiverGID
                             text:(NSString *)text
                         sentDate:(NSDate *)sentDate
                           status:(MessageStatus)status
                       senderInfo:(NSString *)senderInfo {
    
    self = [super init];
    
    if (self) {
        self.senderGID = senderGID;
        self.receiverGID = receiverGID;
        self.text = text;
        self.sentDate = sentDate;
        self.status = status;
        self.senderInfo = senderInfo;
    }
    
    return self;
}

- (instancetype)initWithText:(NSString *)text
                   senderGID:(NSNumber *)senderGID
                 receiverGID:(NSNumber *)receiverGID {
    
    return [self initWithSenderGID:senderGID
                       receiverGID:receiverGID
                              text:text
                          sentDate:[NSDate date]
                            status:MessageStatusSending
                        senderInfo:nil];
}

- (instancetype)initWithData:(GTTextOnlyMessageData *)messageData {
    self = [self initWithSenderGID:messageData.senderGID
                       receiverGID:messageData.addresseeGID
                              text:messageData.text
                          sentDate:messageData.messageSentDate
                            status:MessageStatusSent
                        senderInfo:[self getSenderInfo:messageData]];
    
    if (self) {
        self.hopCount = messageData.hopCount;
    }
    
    return self;
}

# pragma mark - Helpers

- (NSData *)toBytes {
    NSError *error = nil;
    GTTextOnlyMessageData *messageData = [[GTTextOnlyMessageData alloc] initOutgoingWithText:self.text onError:&error];
    
    if (error) {
        NSLog(@"[GoTenna] Error in: %@ %@", NSStringFromSelector(_cmd), error.localizedDescription);
        return nil;
    }
    
    return [messageData serializeToBytes];
}

- (NSString *)getSenderInfo:(GTBaseMessageData *)messageData {
    Contact *contact = [[ContactManager sharedManager] findContactWithGID:messageData.senderGID];
    NSString *senderInitials = messageData.senderInitials;
    
    if (contact) {
        return contact.name;
    }
    else if (senderInitials) {
        return senderInitials;
    }
    
    return [messageData.senderGID stringValue];
}

@end
