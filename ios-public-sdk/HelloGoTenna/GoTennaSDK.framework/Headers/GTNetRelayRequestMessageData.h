//
//  GTNetRelayRequestMessageData.h
//  GoTenna
//
//  Created by Thomas Colligan on 6/10/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTNetRelayMessageData.h"

/**
 * The message data that gets sent when there is a message we wish to relay to others via the Internet and SMS.
 */
@interface GTNetRelayRequestMessageData : GTNetRelayMessageData<GTMessageDataProtocol>

@property (nonatomic, strong, readonly) NSData *encryptedDataToRelay;

- (instancetype)initOutgoingWithMessageToRelay:(GTBaseMessageData *)messageToRelay toGID:(NSNumber *)toGID onError:(NSError **)error;

@end
