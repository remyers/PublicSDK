//
//  AntennaQuality.h
//  GoTennaSDK
//
//  Created by Edmund Trujillo on 4/12/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, GTAntennaQualityLevel) {
    GTAntennaQualityUnknown,
    GTAntennaQualityLevelBad,
    GTAntennaQualityLevelPoor,
    GTAntennaQualityLevelAverage,
    GTAntennaQualityLevelGood,
    GTAntennaQualityLevelExcellent
};

@interface AntennaQuality : NSObject

+ (GTAntennaQualityLevel)antennaQualityFromReflectedPowerRatio:(NSNumber *)reflectedPowerRatio;
+ (NSNumber *) reflectedPowerRatioToVSWR:(NSNumber *) reflectedPowerRatio;

@end
