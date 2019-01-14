//
//  FirmwareManager.h
//  HelloGoTenna
//
//  Created by GoTenna on 8/1/17.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FirmwareManager;

typedef NS_ENUM(NSUInteger, FirmwareUpdateState) {
    UpdateInitialized,
    UpdateInitializeComplete,
    UpdateFinalizeComplete,
    UpdateProgressChanged,
    UpdateSucceeded,
    UpdateFailed
};

@protocol FirmwareManagerProtocol <NSObject>

@required
- (void)firmwareManager:(FirmwareManager *)firmwareManager didUpdateState:(FirmwareUpdateState)state progress:(float)progress;

@end

@interface FirmwareManager : NSObject

- (instancetype)initWithDelegate:(id<FirmwareManagerProtocol>)delegate;

- (void)beginFirmwareUpdate:(void (^)(NSError *))errorBlock;

- (BOOL)isUpdatingFirmware;

@end
