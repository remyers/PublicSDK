//
//  GTCircleMessageData.h
//  GoTennaSDK
//
//  Created by JOSHUA M MAKINDA on 12/12/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTMessageDataProtocol.h"
#import <UIKit/UIKit.h>

@class TLVSection;
@class CLLocation;

@interface GTCircleMessageData : NSObject <GTMessageDataProtocol>

@property(nonatomic, readonly) NSString *title;
@property(nonatomic, readonly) CLLocation *center;
@property(nonatomic, readonly) NSNumber *radiusInMeters;
@property(nonatomic, readonly) UIColor *color;
@property(nonatomic, strong) NSNumber *uuid;

- (instancetype)initWithUUID:(NSNumber *)uuid title:(NSString *)title center:(CLLocation*)center radius:(NSNumber*)radius color:(UIColor*)color;

@end
