//
//  GTFrequencySync.h
//  GoTenna
//
//  Created by Ryan Cohen on 9/14/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GTFrequencyData;

@interface GTFrequencySync : NSObject

@property (nonatomic, strong) void (^onSyncSuccess)();
@property (nonatomic, strong) void (^onSyncFailed)(NSError*);

+ (instancetype)sharedInstance;

/**
 Sync frequency settings to device
 
 Sets power level, bandwidth/bitrate, and syncs
 frequency slots and channels to the goTenna.
 
 @param frequencySlot The default/enabled frequency slot to sync
 */
- (void)syncFrequencySettingsWithSlot:(GTFrequencyData *)frequencySlot;

@end
