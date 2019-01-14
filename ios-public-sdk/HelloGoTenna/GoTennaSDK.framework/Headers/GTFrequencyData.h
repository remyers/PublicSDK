//
//  GTFrequencyData.h
//  goTenna
//
//  Created by Mike Lepore on 10/25/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum : NSUInteger {
    k4_84_kHZ,
    k7_28_kHZ,
    k11_80_kHZ
} Bandwidth;

@class GTFrequencyChannelData;

extern NSString * const kGTFrequencyDataKey_id;
extern NSString * const kGTFrequencyDataKey_name;
extern NSString * const kGTFrequencyDataKey_call_sign;
extern NSString * const kGTFrequencyDataKey_max_power_watts;
extern NSString * const kGTFrequencyDataKey_channel_list;
extern NSString * const kGTFrequencyDataKey_modified;
extern NSString * const kGTFrequencyDataKey_datarate_mask_id;
extern NSString * const kGTFrequencyDataKey_datarate_id;

@interface GTFrequencyData : NSObject <NSCoding>

@property (nonatomic, strong) NSString *frequencyId;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *descriptionString;
@property (nonatomic, strong) NSString *instructions;
@property (nonatomic, strong) NSString *callSign;
@property (nonatomic, readwrite) double maxPowerWatts;
@property (nonatomic, strong) NSArray<GTFrequencyChannelData *> *channelList;
@property (nonatomic, readwrite) int dataRateMaskId;
@property (nonatomic, readwrite) int dataRateId;
@property (nonatomic) BOOL modified;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (instancetype)initWithDefaultData;

- (void)setBandwidth:(Bandwidth)bandwidth;
- (void)addFrequencyChannel:(GTFrequencyChannelData *)channelData;
- (void)updateWithFrequencyData:(GTFrequencyData *)freqData;

// Default data
- (BOOL)isFrequencyFactoryDefault;
- (BOOL)isFrequencyDefault;
- (void)setFrequencyBackToFactoryDefault:(void (^)(GTFrequencyData *))returnFrequency withError:(void (^)(NSString *))errorMessage;

// Queries
- (BOOL)isEqualTo:(GTFrequencyData *)frequencySlot;
- (NSDictionary *)toDictionary;
+ (NSArray <GTFrequencyChannelData *> *)sortedChannelList:(NSArray <GTFrequencyChannelData *>*)channelList;
+ (NSArray <GTFrequencyChannelData *> *)sortedChannelListControlDataOnly:(NSArray <GTFrequencyChannelData *>*)channelList;

@end
