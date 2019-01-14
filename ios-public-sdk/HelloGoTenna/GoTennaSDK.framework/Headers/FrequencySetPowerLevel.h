//
//  FrequencySetPowerLevel.h
//  goTenna
//
//  Created by Mike Lepore on 11/3/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, PowerLevel_Type) {
    PowerLevel_OneHalf,
    PowerLevel_One,
    PowerLevel_Two,
    PowerLevel_Four,    // Note that four and five are synonomous
    PowerLevel_Five
};

@interface FrequencySetPowerLevel : NSObject

- (NSString *)stringValue;
- (PowerLevel_Type)typeValue;

+ (double)doubleForData:(PowerLevel_Type)powerLevel;
+ (PowerLevel_Type)powerLevelForData:(double)data;
+ (NSArray *)allLevels;

- (instancetype)initWithPowerLevel:(PowerLevel_Type)powerLevel;

@end
