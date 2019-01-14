//
//  NetworkRelayRequester.h
//  GoTenna
//
//  Created by Thomas Colligan on 8/24/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
@class GTNetRelayRequestMessageData;

typedef NS_ENUM(NSInteger, RequestState)
{
    RequestStateRequestNonce,
    RequestStateRequestSessionToken,
    RequestStateRelayMessageToServer,
    RequestStateSendRelaySuccessMessage,
    RequestStateCompletedAll,
    RequestStateError
};

/**
 * Sends a network relay request to the goTenna server.
 * Handles requesting the nonce, session token, etc.. that is required when a network relay
 * request is made.
 */
@interface NetworkRelayRequester : NSObject

@property (nonatomic, copy) void(^requestStateChangedCallback)(RequestState);

- (void)relayMessage:(GTNetRelayRequestMessageData *)netRelayRequestMessageData willSendSuccessMessage:(BOOL)willSendSuccessMessage withCompletion:(void(^)(RequestState))requestStateChangedCallback;

@end
