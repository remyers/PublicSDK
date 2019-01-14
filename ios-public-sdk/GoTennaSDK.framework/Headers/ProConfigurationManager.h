//
//  ProConfigurationManager.h
//  goTenna
//
//  Created by Mike Lepore on 10/25/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ProConfigurationData.h"

@class GTResponse;

extern NSString * const kProConfigurationDataURL;
extern NSString * const kProConfigurationGoKitURL;

@protocol ProConfigurationManagerDelegate <NSObject>
- (void)proConfigurationManagerLoadedLocalConfigurationData;
@end

@interface ProConfigurationManager : NSObject
@property (nonatomic, strong) ProConfigurationData *configurationData;
@property (nonatomic, weak) id<ProConfigurationManagerDelegate> delegate;

+ (ProConfigurationManager *)shared;
- (void) setLocalServiceUser:(BOOL)isLocal;

// Helpers
- (BOOL)isServiceUser;

// Service Token
- (void)storeServiceToken:(NSString *)token;
- (void)storeRefreshToken:(NSString *)refreshToken;

- (void)storeClientID:(NSString*)clientID;

- (NSString *)serviceToken;

// Logout
- (void)logout;

// Load
- (void)loadLocalConfigData;
- (void)loadProductData:(void (^)())onSuccess onError:(void (^)(NSString *))onError;
- (void)loadGoKitData:(void (^)())onSuccess onError:(void (^)(NSString *))onError;
- (void)testLoadGoKitData:(void (^)())onSuccess onError:(void (^)(NSString *))onError;
- (void)loadWithFrequencySlot:(GTFrequencyData *)frequencySlot;

// Clear Data
- (void)removeBackupConfigurationData;

// Default data
- (GTFrequencyData *)factoryDefaultFrequencyForId:(NSString *)frequencyId;    // From server
- (GTFrequencyData *)defaultFrequencyForId:(NSString *)frequencyId;           // From local

// Start regular config refresh
- (void)startRetrievingConfigData;

@end
