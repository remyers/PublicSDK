//
//  ProConfigurationData.h
//  goTenna
//
//  Created by Mike Lepore on 10/25/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTFrequencyData.h"
#import "GTFrequencyChannelData.h"

@class GTEnabledFeaturesData;
@class GTFirmwareData;

OBJC_EXTERN NSString *const kProConfigurationDataKey_frequency_slots;

typedef NS_ENUM(NSInteger, ConfigUser_Type)
{
    ConfigUser_Normal,
    ConfigUser_Service
};


@interface ProConfigurationData : NSObject <NSCoding>

@property (nonatomic, readwrite) ConfigUser_Type userType;
@property (nonatomic, strong) GTEnabledFeaturesData *enabledFeatures;
@property (nonatomic, strong) GTFirmwareData *firmware;
@property (nonatomic, strong) NSArray *enabledAnalytics;
@property (nonatomic, strong) NSArray <GTFrequencyData *> *frequencySlots;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (void)insertFrequencies:(NSDictionary *)dictionary;

@end
