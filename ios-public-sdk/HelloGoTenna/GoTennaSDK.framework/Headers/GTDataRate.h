//
//  GTDataRate.h
//  GoTenna
//
//  Created by Ryan Cohen on 9/11/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GTDataRate : NSObject

@property (nonatomic, readonly) int identifier;
@property (nonatomic, readonly) int bytesPerSecond;

- (instancetype)initWithIdentifier:(int)identifier bytesPerSecond:(int)bytesPerSecond;

@end
