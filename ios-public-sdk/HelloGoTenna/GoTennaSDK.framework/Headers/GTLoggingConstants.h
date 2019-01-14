//
//  GTLoggingConstants.h
//  GoTenna
//
//  Created by Julietta Yaunches on 6/17/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTConstants.h"

extern const int MAX_LOG_ENTRY_COUNT;
extern NSString * const BASIC_DEBUG_LOG_NAME;
extern NSString * const DETAIL_DEBUG_LOG_NAME;

@interface GTLoggingConstants : NSObject

+ (NSDictionary *)messageContentTypes;
+ (NSDictionary *)messageTypes;

+ (NSString *)goTennaBTLoggingDirectory;
+ (NSString *)goTennaBTLoggingFilename;
+ (NSString *)goTennaFieldTestLoggingDirectory;
+ (NSString *)goTennaFieldTestLoggingFilename;
+ (NSString *)goTennaBinaryLogsLoggingDirectory;
+ (NSString *)goTennaBinaryLogsLoggingFilename;
+ (NSString *)goTennaMessageTestLoggingDirectory;

@end
