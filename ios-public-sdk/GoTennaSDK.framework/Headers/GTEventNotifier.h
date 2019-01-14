//
//  GTEventNotifier.h
//  GoTenna
//
//  Created by Julietta Yaunches on 10/17/14.
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum : NSUInteger {
    EventNotifierLogTypeNormal,
    EventNotifierLogTypePriority,
} EventNotifierLogType;

@class GTCommand;
@class GTBaseMessageData;

@interface GTEventNotifier : NSObject

+ (GTEventNotifier *)shared;

- (void)userDisconnectInitiated;
- (void)nonUserDisconnectionOccurred:(NSError *)error;
- (void)writeError:(NSError *)error;
- (void)RSSIReceived:(NSNumber *)number;
- (void)logGoTennaEventWithType:(EventNotifierLogType)eventType logDetail:(NSString*)log, ...; //type:;
- (void)antennaIsBad:(NSError *)error;
- (void)attemptToSendMessageInRelayMode:(NSError *)error;
- (void)attemptToSendMessageInListenOnlyMode:(NSError *)error;

@property (nonatomic) BOOL rssiLoggingTurnedOn;

@end
