//
//  NetworkRelayCredentials.h
//  goTenna SDK
//
//  Created by Thomas Colligan on 8/24/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * A set of credentials belonging to a GID.
 * These credentials are used by the Network Relay feature to encrypt data using
 * AES 128 before the data is relayed.
 */
@interface NetworkRelayCredentials : NSObject

@property (nonatomic, strong, readonly) NSNumber *gid;
@property (nonatomic, strong, readonly) NSString *password;
@property (nonatomic, strong, readonly) NSData *salt;
@property (nonatomic, strong, readonly) NSData *iv;

- (id)initWithGid:(NSNumber *)gid;
- (id)initWithJsonString:(NSString *)jsonString;
- (NSString *)toJsonString;

@end
