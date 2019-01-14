//
//  NSNumber+Utilities.h
//  GoTenna
//
//  Created by Julietta Yaunches on 16/06/2014.
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSNumber (Utilities)

+ (NSNumber *)convertGIDStringToNumber:(NSString *)input;
- (NSData *)convertGIDToData;
+ (NSDecimalNumber *)megaHertzToHertz:(NSDecimalNumber *)megaHertz;
+ (NSDecimalNumber *)hertzToMegaHertz:(NSDecimalNumber *)hertz;
+ (NSDecimalNumber *)megaHertzToKiloHertz:(NSDecimalNumber *)megaHertz;
+ (NSDecimalNumber *)kiloHertzToMegaHertz:(NSDecimalNumber *)kiloHertz;

@end
