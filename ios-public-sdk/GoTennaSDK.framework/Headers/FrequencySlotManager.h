//
//  FrequencySlotManager.h
//  GoTennaSDK
//
//  Created by Dhananjay Suresh on 3/8/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTFrequencyData.h"

@interface FrequencySlotManager : NSObject

@property (readonly, copy, nonatomic) NSArray *frequencySlots;
@property (readonly, copy, nonatomic) NSArray *customFrequencySlots;

+ (FrequencySlotManager *)shared;
- (void)loadFrequencySets;
- (NSArray *)frequencySlotsWithCustom;

// OTA-tuning involved
- (void)applyEnabledFrequencySlotToDevice:(void (^)(BOOL succeeded))response;
- (void)sendFrequencySlot:(GTFrequencyData *)frequencySlot toGID:(NSNumber *)gid completion:(void (^)(BOOL, NSError *))completion;

// Save
- (void)saveOnSuccessForFrequency:(GTFrequencyData *)frequency response:(void (^)(BOOL succeeded))response;
- (void)saveAllFrequencyData;

// Add / Remove
- (void)insertFrequenciesForConfigurationDataWithServerFrequencySlots:(NSArray *)serverFrequencies;
- (void)addFrequencySlot:(GTFrequencyData *)frequency;
- (void)overwriteFrequencySlot:(GTFrequencyData *)frequency;
- (void)removeFrequencySlot:(GTFrequencyData *)frequency;
- (void)removeAllFrequencySlots;
- (void)removeSelectedFrequencySlot;

- (BOOL)isFrequencySlotEnabled:(GTFrequencyData *)frequency;
- (void)setFrequencySlotEnabled:(GTFrequencyData *)frequency;
- (BOOL)frequencySlotExists:(GTFrequencyData *)frequency;
- (BOOL)areFrequenciesFactoryDefault;
- (void)setFrequenciesBackToFactoryDefault;

@end
