//
//  GTRectangleMessageData.h
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

@interface GTRectangleMessageData : NSObject <GTMessageDataProtocol>

@property(nonatomic, readonly) NSString *title;
@property(nonatomic, readonly) CLLocation *cornerOne;
@property(nonatomic, readonly) CLLocation *cornerTwo;
@property(nonatomic, readonly) CLLocation *depth;
@property(nonatomic, readonly) UIColor *color;
@property(nonatomic, strong) NSNumber *uuid;

- (instancetype)initWithUUID:(NSNumber *)uuid title:(NSString*)title cornerOne:(CLLocation*)cornerOne cornerTwo:(CLLocation*)cornerTwo depth:(CLLocation*)depth color:(UIColor *)color;

@end
