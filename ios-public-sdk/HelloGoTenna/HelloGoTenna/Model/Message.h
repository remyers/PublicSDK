//
//  Message.h
//  HelloGoTenna
//
//  Created by GoTenna on 7/25/17.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
@class GTTextOnlyMessageData;

typedef NS_ENUM(NSUInteger, MessageStatus) {
    MessageStatusSending,
    MessageStatusSent,
    MessageStatusError
};

@interface Message : NSObject

@property (nonatomic, readonly) NSNumber *senderGID;
@property (nonatomic, readonly) NSString *text;
@property (nonatomic, readonly) NSNumber *receiverGID;
@property (nonatomic, readonly) NSDate *sentDate;
@property (nonatomic, readonly) NSString *senderInfo;
@property (nonatomic) NSUInteger hopCount;
@property (nonatomic, readonly) MessageStatus status;

- (instancetype)initWithSenderGID:(NSNumber *)senderGID
                      receiverGID:(NSNumber *)receiverGID
                             text:(NSString *)text
                         sentDate:(NSDate *)sentDate
                           status:(MessageStatus)status
                       senderInfo:(NSString *)senderInfo;

- (instancetype)initWithText:(NSString *)text
                   senderGID:(NSNumber *)senderGID
                 receiverGID:(NSNumber *)receiverGID;

- (instancetype)initWithData:(GTTextOnlyMessageData *)messageData;

- (NSData *)toBytes;

@end
