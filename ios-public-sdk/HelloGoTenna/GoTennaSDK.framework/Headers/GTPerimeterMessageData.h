//
//  GTPerimeterMessageData.h
//  goTenna
//
//  Created by JOSHUA M MAKINDA on 3/17/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "GTMessageDataProtocol.h"

@class TLVSection;
@class CLLocation;

@interface GTPerimeterMessageData : NSObject <GTMessageDataProtocol>

@property (nonatomic, copy) NSString *title;
@property (nonatomic, strong) NSArray<CLLocation *> *dataPoints;
@property (nonatomic, strong) NSNumber *uuid;
@property (nonatomic, strong) UIColor *color;

- (instancetype)initWithUUID:(NSNumber *)uuid dataPoints:(NSArray<CLLocation *> *)points title:(NSString *)title andColor:(UIColor *)color;

@end
