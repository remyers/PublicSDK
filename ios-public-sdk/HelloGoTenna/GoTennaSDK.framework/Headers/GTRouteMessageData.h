//
//  GTRouteMessageData.h
//  GoTennaSDK
//
//  Created by JOSHUA M MAKINDA on 8/23/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTMessageDataProtocol.h"
#import <UIKit/UIKit.h>

@class TLVSection;
@class CLLocation;

@interface GTRouteMessageData : NSObject <GTMessageDataProtocol>

@property(nonatomic, copy) NSString *title;
@property(nonatomic, strong) NSArray<CLLocation *> *dataPoints;
@property(nonatomic, strong) NSNumber *uuid;
@property(nonatomic, strong) UIColor *color;

- (instancetype)initWithUUID:(NSNumber *)uuid dataPoints:(NSArray<CLLocation *> *)points title:(NSString *)title andColor:(UIColor *)color;

@end
