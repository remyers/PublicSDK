//
//  GTNetRelaySuccessResponseMessageData.h
//  GoTenna
//
//  Created by Thomas Colligan on 6/10/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTNetRelayMessageData.h"

/**
 The message data that gets sent after this user has successfully relayed a GTNetRelayRequestMessageData to
 the Internet via the goTenna Server and Twillio.
 */
@interface GTNetRelaySuccessResponseMessageData : GTNetRelayMessageData<GTMessageDataProtocol>

- (id)initOutgoingWithUUID:(NSString *)uuid onError:(NSError **)error;

@end
