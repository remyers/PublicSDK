//
//  NSString+Util.h
//  GoTenna
//
//  Created by Thomas Colligan on 6/15/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (Util)

- (NSData *)hexStringToData;
+ (NSString *)hertzIntegerToMhzString:(NSUInteger)hertz withDecimalPlaces:(NSInteger)places;
+ (NSString *)megaHertzToString:(NSDecimalNumber *)megaHertz withDecimalPlaces:(NSInteger)places;

@end
