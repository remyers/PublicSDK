//
//  NSDictionary+Parsing.h
//  goTenna
//
//  Created by Mike Lepore on 10/25/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDictionary (Parsing)
- (NSString *)stringForKey:(NSString *)key;
- (BOOL)boolForKey:(NSString *)key;
- (int)intForKey:(NSString *)key;
- (double)doubleForKey:(NSString *)key;
- (float)floatForKey:(NSString *)key;
- (NSArray *)arrayForKey:(NSString *)key;

// Helpers
- (BOOL)isValidKey:(NSString *)key;
- (BOOL)isValidKey:(NSString *)key expectingClass:(Class)className;
@end
