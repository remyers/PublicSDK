//
// Created by Julietta Yaunches on 21/10/2014.
// Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GTConfig : NSObject

+ (NSString *)retrieveCurrentVersion;
+ (NSString *)retrieveVersionDescription;
+ (NSString *)forgetThisDeviceKey;

+ (NSInteger)maxGIDlength;
+ (NSInteger)maxNameLength;
+ (NSInteger)maxGroupMembers;
+ (NSInteger)minTLVlength;
+ (NSInteger)minHopCount;
+ (NSInteger)maxHopCount;
+ (void)setMaxHopCount:(NSInteger)hops;
+ (double)meshMessageTimeoutForHopCount:(NSUInteger)hopCount;
+ (NSInteger)reconnectionScanTimeout;
+ (NSInteger)initialConnectionScanTimeout;
+ (NSUInteger)privateGIDByteLength;
+ (NSUInteger)broadcastGIDByteLength;
+ (NSInteger)maxDataPayloadLength;
+ (NSInteger)firmwareUpdateCommandTimeoutAmount;
+ (NSInteger)normalCommandTimeoutAmount;
+ (NSTimeInterval)finalizeFirmwareCommandTimeout;
+ (NSInteger)resetCommandTimeoutAmount;
+ (NSInteger)systemInfoQueryInterval;
+ (double)sendMessageTimeout;

+ (BOOL)isRSSILoggingOn;
+ (BOOL)shouldWriteLocationToFieldTestLog;
+ (BOOL)shouldLogPackets;
+ (BOOL)shouldNotifyAnalyticsEvents;
+ (BOOL)connectionNotRequired;
+ (BOOL)connectionRetryEnabled;
+ (BOOL)firmwareUpdateinEnabled;
+ (BOOL)shouldAllowChatOneToOneVisualQueue;

@end
