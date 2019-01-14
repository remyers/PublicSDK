//
//  PublicKeyManager.h
//  GoTenna
//
//  Created by JOSHUA M MAKINDA on 12/29/15.
//  Copyright © 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PublicKeyEntry;

/// Manages public key operations
@interface PublicKeyManager : NSObject

/**
 ###Shared instance
 
 Use this for to create access the common instance of this class.
 
 @return Singleton instance
 */
+ (instancetype)shared;

/// Add public key with gid and public key data (generally for internal use)
- (void)addPublicKeyWithGID:(NSNumber*)gid publicKeyData:(NSData*)publicKey;
/// Add public key with gid and public key data, mark whether the other user has the public key (generally for internal use)
- (void)addPublicKeyWithGID:(NSNumber*)gid publicKeyData:(NSData*)publicKey userHasMyPublicKey:(BOOL)hasPublicKey;
/// Add private key with gid and public key data, mark whether the other user has the public key (generally for internal use)
- (void)addPublicKeyPrivateWithGID:(NSNumber*)gid publicKeyData:(NSData*)publicKey userHasPublicKey:(BOOL)userHasPublicKey;
/// Set public key state with GID and mark that user has the public (generally for internal use)
- (void)setPublicKeyStateWithGID:(NSNumber*)gid userHasMyPublicKey:(BOOL)userHasPublicKey;
/// Mark the public key reset (for internal use)
- (void)didResetMyPublicKey;

/**
 ###Public key entry for GID?
 
 Queries the public key registry for whether a public key is associated with a GID
 
 @param gid                 The GID to check if in the registry.
 @return `PublicKeyEntry`
 */
- (PublicKeyEntry*)publicKeyEntryForGID:(NSNumber*)gid;

@end
