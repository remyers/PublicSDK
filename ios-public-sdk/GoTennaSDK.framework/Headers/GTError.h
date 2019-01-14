//
// Created by Julietta Yaunches on 12/2/14.
// Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

/// GoTenna error list
@interface GTError : NSObject

/// Nack error
+ (NSError *)nackError;
/// Not super SDK user
+ (NSError *)notSuperSDKUser;
/// Data rate limited has exceeded
+ (NSError *)dataRateLimitExceeded;
/// goTenna is not connected
+ (NSError *)goTennaNotConnectedError;
/// Invalid firmware for the update
+ (NSError *)invalidFirmwareForUpdate;
/// Invalid app token used
+ (NSError *)invalidAppToken;
/// Invalid input message data
+ (NSError *)invalidInputMessageData;
/// Incoming message data is invalid
+ (NSError *)invalidIncomingMessageData;
/// GoTenna failed to process command
+ (NSError *)goTennaFailedToProcessCommand;
/// User has not setup their goTenna
+ (NSError *)hasNotSetupGotenna;
/// The data length exceeds the max limit
+ (NSError *)dataLengthExceedsLimits;
/// Reserved GID used in error
+ (NSError *)sendingMessageToReservedGID;
/// Group secret not found
+ (NSError *)groupSecretNotFound;
/// goTenna timed out with command
+ (NSError *)goTennaTimedOutWithCommand;
/// Invalid frequency set
+ (NSError *)invalidFrequencySet:(NSDictionary *)userInfo;
/// Bad antenna error
+ (NSError *)antennaBad:(NSDictionary *)userInfo;
/// Shout encryption key not found
+ (NSError *)shoutEncryptionKeyNotFound;
/// Send while in relay mode
+ (NSError *)sendWhileInRelayMode:(NSDictionary *)userInfo;
/// Send while in listen mode
+ (NSError *)sendWhileInListenMode:(NSDictionary *)userInfo;
+ (NSError *)tooManyMembersInGroup:(NSDictionary *)userInfo;

@end
