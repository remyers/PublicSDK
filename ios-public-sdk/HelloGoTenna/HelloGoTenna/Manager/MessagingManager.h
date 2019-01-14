//
//  MessagingManager.h
//  HelloGoTenna
//
//  Created by GoTenna on 7/26/17.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
@class Message;
@class GTBaseMessageData;

typedef void (^MessagingManagerResponse)(Message *message, NSError *error);

@class MessagingManager;

@protocol MessagingManagerProtocol <NSObject>

@required
- (void)messagingManager:(MessagingManager *)manager didReceiveIncomingShout:(Message *)message;
- (void)messagingManager:(MessagingManager *)manager didReceiveIncomingMessage:(Message *)message;
- (void)messagingManager:(MessagingManager *)manager didSendOutgoingMessage:(Message *)message;
- (void)messagingManager:(MessagingManager *)manager didFailSendingMessage:(Message *)message;

@optional
- (void)messagingManager:(MessagingManager *)manager didReceiveIncoming:(GTBaseMessageData *)messageData;

@end

@interface MessagingManager : NSObject

@property (nonatomic, weak) id<MessagingManagerProtocol> delegate;

+ (instancetype)sharedManager;

- (void)sendBroadcastMessage:(Message *)message;
- (void)sendMessage:(Message *)message;

@end
