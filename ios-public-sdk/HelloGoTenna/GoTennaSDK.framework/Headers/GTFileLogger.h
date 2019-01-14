//
//  GTFileLogger.h
//  GoTenna
//
//  Created by Julietta Yaunches on 6/18/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GTFileLogger : NSObject

- (instancetype)initWithDirectory:(NSString *)directory andSeparator:(NSString *const)separator;

- (void)log:(NSString *)logText;
- (void)truncateLog;
- (void)writeQueued;

- (NSArray *)allLogs;
- (NSArray *)latestLogs;

@end
