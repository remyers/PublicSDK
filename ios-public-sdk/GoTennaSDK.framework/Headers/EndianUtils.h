//
//  EndianUtils.h
//  Test
//
//  Created by Thomas Colligan on 12/21/15.
//  Copyright (c) 2015 Thomas Colligan. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSInteger const BYTE_LEN;
extern NSInteger const SHORT_BYTE_LEN;

@interface EndianUtils : NSObject

+ (NSData *)longToBigEndianBytes:(unsigned long long)longValue;
+ (NSData *)longToBigEndianBytes:(unsigned long long)longValue length:(int)length;

+ (NSData *)integerToBigEndianBytes:(int)integer;
+ (NSData *)integer:(int)integer toBigEndianBytesWithLength:(int)byteCount;

+ (NSData *)doubleToBigEndianBytes:(double )doubleValue;
+ (NSData *)boolToBigEndian:(BOOL)boolean;

+ (long long)bytesToLong:(NSData *)data;

+ (int)bytesToInt:(NSData *)data;

+ (short)bytesToShort:(NSData *)data;

+ (double) bytesToDouble:(NSData *)data;

+ (BOOL)bytesToBool:(NSData *)data;

+ (NSNumber *)byteToSignedNumber:(NSData *)data;

@end
