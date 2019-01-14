//
//  GTShoutEncryptionManager.h
//
//  Created by Edmund Trujillo on 6/13/18.
//  Copyright © 2018 Edmund Trujillo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreImage/CoreImage.h>

@interface GTShoutEncryptionManager : NSObject

+ (BOOL) writeRandomKeyToKeyChain:(NSString *)keyName;
+ (BOOL) writeToKeyChainWithKey:(NSString *)keyName andKey:(NSData *)key;
+ (NSData *) readKeyFromKeyChain:(NSString *)keyName;
+ (BOOL) deleteKeyFromKeyChain:(NSString *)keyName;
+ (NSArray <NSString *> *) keyFilesOnKeyChain;
+ (BOOL)keyNameExists:(NSString *)keyName;
+ (BOOL) deleteAllKeysFromKeyChain;

+ (BOOL)isUsingShoutEncryption;
+ (void)shoutEncryption:(BOOL)setOn;

+ (NSString *)activeShoutKeyFileName;
+ (void) selectActiveShoutKeyFileName:(NSString *)keyFileName;

+ (NSData *)tryToDecryptFromAllKeyFiles:(NSData *)encryptedData;
+ (NSData *)decryptFromSingleKeyFile:(NSString *)keyFile encryptedData:(NSData *)encryptedData;
+ (NSData *)encryptFromKeyFile:(NSString *)keyFile dataToEncrypt:(NSData *)dataToEncrypt;

+ (CIImage *)qrCodeImageForKeyFile:(NSString *)keyFile;
+ (NSString *)qrCodeStringForKeyFile:(NSString *)keyFile;
+ (NSDictionary *)qrCodeStringToKeyNameAndKey:(NSData *)qrCode;


@end
