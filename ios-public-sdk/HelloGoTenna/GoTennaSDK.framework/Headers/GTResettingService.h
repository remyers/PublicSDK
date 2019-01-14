//
// Created by Julietta Yaunches on 2/2/15.
// Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

/// GoTenna resetting service management
@interface GTResettingService : NSObject

/**
 ###Shared instance
 
 Use this for to create access the common instance of this class.
 
 @return Singleton instance
 */
+ (instancetype)shared;

/// Perform a reset on the goTenna (generally for internal use)
- (void)resetTheGotenna;

@end
