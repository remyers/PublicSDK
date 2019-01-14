//
//  GTSystemInfo.h
//  GoTenna
//
//  Created by Julietta Yaunches on 4/23/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SystemInfoResponseData;

typedef NS_ENUM(NSUInteger, GTBatteryStatusLevel) {
    BatteryGoodGreen,
    BatterySlightlyLowYellow,
    BatteryLowRed
};

@interface GTSystemInfo : NSObject <NSCoding>

@property (nonatomic) NSString *firmwareVersion;
@property (nonatomic) NSNumber *majorRevision;
@property (nonatomic) NSNumber *minorRevision;
@property (nonatomic) NSNumber *buildRevision;
@property (nonatomic) NSNumber *batteryLevel;
@property (nonatomic) NSNumber *antennaQuality;
@property (nonatomic) NSNumber *vswrValue;
@property (nonatomic) NSNumber *isCurrentlyCharging;
@property (nonatomic, copy) NSString *goTennaSerialNumber;

+ (instancetype)initWithSystemInfo:(SystemInfoResponseData *)incomingData;
- (GTBatteryStatusLevel)currentBatteryStatus;

- (NSString *)printableVersion;
- (NSString *)printableRevisionVersion;

@end
