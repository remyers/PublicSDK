//
//  GTMessageResponseProcessor.h
//  GoTenna
//
//  Created by Julietta Yaunches on 1/8/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTMessageDataProtocol.h"

@class GTResponse;
@class SystemInfoResponseData;
@class GTMessageData;
@class GTGroupCreationMessageData;
@class GTCommand;
@class GTBaseMessageData;
@class PacketVerifier;
@class TLVSection;

/// Serializer of message data
@interface GTDataSerializer : NSObject

/**
 ###Deserialize group message data
 
 Convert message object data to `GTGroupCreationMessageData`
 
 @param data   Message data object
 @return GTGroupCreationMessageData
 */
+ (GTGroupCreationMessageData *)deserializeGroupMessageDataObj:(GTMessageData *)data;

/**
 ###Deserialize system info
 
 Convert `GTResponse` from a system info request to `SystemInfoResponseData`

 @param response   Response object from system info request
 @return SystemInfoResponseData
 */
+ (SystemInfoResponseData *)deserializeSystemInfo:(GTResponse *)response;

/**
 ###Message deserialization
 
 Deserialize message for the given command
 
 @param data    Message data that goes with the command
 @param command Command that goes with the message data.

 @return GTResponse
 */
+ (GTResponse *)deserializeMessage:(NSData *)data forCommand:(GTCommand *)command;

/**
 ###Parse incoming data
 
 Parse incoming message data using the message data.
 
 @param commandData   Command data that is the incoming message data to parse
 @param messageData   Message data to be converted

 @return GTBaseMessageData
 */
+ (GTBaseMessageData *)parseIncomingMessageData:(NSData *)commandData withMessageData:(GTMessageData *)messageData;

/**
 ###Parse And Handle
 
 Parse and handle the response from the command that pulls messages (Get Message) from the goTenna device. Generally for internal use.
 @param response   Response object after the message is pulled
 @param onIncomingMessage   Called when the message is incoming
 @param onGroupAdded   Called at appropriate time for executing group operations, used to add group GID
 @param lastMessageDelete   Called to provide opportunity to delete message at the appropriate time
 @param isDecryptionErrorRetry used to perform actions accordingly if operations are for decryption error retry
 
 @return BOOL
 */
+ (BOOL)parseAndHandleGetMessageResponse:(GTResponse *)response
                              onIncoming:(void (^)(GTMessageData *))onIncomingMessage
                          onGroupCreated:(void (^)(GTGroupCreationMessageData *))onGroupAdded
              onSuccessLastMessageDelete:(void (^)())lastMessageDelete
                  isDecryptionErrorRetry:(BOOL)isDecryptionErrorRetry;

/**
 ###Get Token Data
 
 Get app token data

 @return NSData token data
 */
+ (NSData *)appTokenData;

@end
