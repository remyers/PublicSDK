//
//  GTNetRelayMessageData.h
//  GoTenna
//
//  Created by Thomas Colligan on 6/10/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTMessageDataProtocol.h"
#import "GTBaseMessageData.h"

/**
 An 'abstract' class that is extended by GTNetRelayRequestMessageData and GTNetRelaySuccessResponseMessageData.
 Handles maintaining the Net Relay messages UUID that will be used to identify it on the goTenna Server to avoid sending duplicate messages.
 */
@interface GTNetRelayMessageData : GTBaseMessageData <GTMessageDataProtocol>

- (instancetype)initFromOrderedData:(NSArray<TLVSection *> *)array withSenderGID:(NSNumber *)senderGID;
- (instancetype)initOutgoingWithUUID:(NSString *)uuid andError:(NSError **)error;

- (NSString *)netRelayUuid;

@end
