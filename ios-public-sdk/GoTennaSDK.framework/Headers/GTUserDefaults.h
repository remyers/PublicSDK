//
// Created by Julietta Yaunches on 21/10/2014.
// Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTPairingConnectionState.h"

@class GTFirmwareVersion;

@interface GTUserDefaults : NSObject

+ (BOOL)encryptionEnabled;

+ (void)setLastPairingState:(GTConnectionState)state;
+ (GTConnectionState)lastPairingState;
+ (void)clearLastPairingState;

+ (void)disableLED:(BOOL)disable;
+ (BOOL)isLEDDisabled;

+ (void)enableListenOnly:(BOOL)enable;
+ (BOOL)isListenOnlyEnabled;

+ (void)enableRelayMode:(BOOL)enable;
+ (BOOL)isRelayModeEnabled;

+ (void)enableShouts:(BOOL)on;
+ (BOOL)acceptingShouts;

+ (void)clearAllSettings;

#if SDK_INTERNAL == 1

+ (void)activateAntennaSweep:(BOOL)on;
+ (void)setAppJustCrashed:(BOOL)value;
+ (void)setEncryptionEnabled:(BOOL)enabled;
+ (void)setShouldGoStraightToMapDownloadsOnMap:(BOOL)value;
+ (void)setUserHasBeenPromptedOnInitialLandingAboutMaps;

+ (BOOL)shouldGoStraightToMapDownloadsOnMap;
+ (BOOL)userHasNotBeenPromptedOnInitialLandingAboutMaps;
+ (BOOL)appJustCrashed;
+ (BOOL)antennaSweepActivated;

+ (void)setLastSentFieldTestMessageIndex:(NSUInteger)index;
+ (NSUInteger)lastSentFieldTestMessageIndex;

+ (void)setFirmwareBucketToStaging;
+ (void)setFirmwareBucketToProduction;
+ (void)setFirmwareBucketToDefault;
+ (NSString *)getFirmwareS3Bucket;

#endif

@end
