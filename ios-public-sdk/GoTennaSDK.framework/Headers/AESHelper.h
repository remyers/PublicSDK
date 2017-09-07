//
//  AESHelper.h
//  goTenna SDK
//
//  Created by Thomas Colligan on 6/22/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AESHelper : NSObject

+ (NSData *)createKeyFromPassword:(NSString *)password
                         withSalt:(NSData *)salt
                andIterationCount:(uint)iterationCount
              andKeyLenghtInBytes:(uint)keyLengthInBytes;

+ (NSData *)encryptData:(NSData *)data key:(NSData *)key iv:(NSData *)iv;
+ (NSData *)decryptData:(NSData *)data key:(NSData *)key iv:(NSData *)iv;

@end
