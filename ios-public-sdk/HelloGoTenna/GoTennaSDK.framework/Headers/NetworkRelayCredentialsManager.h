//
//  NetworkRelayCredentialsManager.h
//  GoTenna
//
//  Created by Thomas Colligan on 8/24/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
@class NetworkRelayCredentials;

@interface NetworkRelayCredentialsManager : NSObject

@property (nonatomic, strong, readonly) NetworkRelayCredentials *networkRelayCredentials;
@property (nonatomic, assign, readonly) BOOL didSyncNetworkRelayCredentials;

+ (NetworkRelayCredentialsManager *)sharedInstance;
- (void)createNewSetOfNetworkRelayCredentialsForGid:(NSNumber *)gid;
- (void)removeNetworkRelayCredentials;
- (BOOL)hasNetworkRelayCredentials;
- (void)syncNetworkRelayCredentialsIfNecessary;

@end
