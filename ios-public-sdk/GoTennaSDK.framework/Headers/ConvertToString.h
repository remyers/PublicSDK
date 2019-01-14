//
//  ConvertToString.h
//  goTenna
//
//  Created by App Partner on 10/31/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ConvertToString : NSObject
+ (NSString *)boolToString:(BOOL)variable;
+ (NSString *)floatToString:(float)variable;
+ (NSString *)intToString:(int)variable;
+ (NSString *)longToString:(long)variable;
+ (NSString *)doubleToString:(double)variable;
+ (NSString *)dictionaryToString:(NSDictionary *)variable;
+ (NSString *)arrayToString:(NSArray *)variable;
@end
