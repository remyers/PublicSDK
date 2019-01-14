//
//  GTSecurityService.h
//  GoTenna
//
//  Created by Julietta Yaunches on 5/18/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GoTennaKeyPair;

/// Generating and accessing the encryption key pair (generally for internal use)
@interface GTSecurityService : NSObject

/**
 ###Shared instance
 
 Use this for to create access the common instance of this class.
 
 @return Singleton instance
 */
+ (instancetype)shared;

/// Create the personal key pair as `GoTennaKeyPair`
- (void)generatePersonalKeyPair;

/**
 ###Get key pair
 
 Get the personal key pair
 
 @return onError    `GoTennaKeyPair`
 */
- (GoTennaKeyPair *)keyPair;

/**
 ###Generation of shared secret
 
 Generation of the shared secret (the data known only between the parties involved)
 @param remotePublicKey Other user's public key to use for generation of shared secret
 @return NSData
 */
- (NSData *)generateSharedSecretUsingRemotePublicKey:(NSData *)remotePublicKey;

@end
