//
//  GTFirmwareInstallationManager.h
//  GoTenna
//
//  Created by Julietta Yaunches on 1/22/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GTCommandCenter;
@class GTCommandBuilder;
@class FirmwareFileParser;
@class GTSystemInfoStore;
@class SettingsTVC;
@protocol GTFirmwareInstallationProgressProtocol;
@class FirmwareInstallationHud;

/// Manages the firmware installation.
@interface GTFirmwareInstallationManager : NSObject

/**
 ### Check And Install Firmware With Progress
 
 Retrieves version of firmware and installs that firmware by passing in an object that conforms to GTFirmwareInstallationProgressProtocol
 
 @param delegate object that conforms to GTFirmwareInstallationProgressProtocol
 */
- (void)checkAndInstallFirmwareWithFirmwareProgressDelegate:(id <GTFirmwareInstallationProgressProtocol>)delegate;

/**
 ###Is Currently Downloading
 
 Returns whether or not the GTFirmwareInstallationManager is currently downloading firmware
 
 @return BOOL
 */
- (BOOL)isCurrentlyDownloading;

/**
 ### Cancel Installation
 
 Externally cancel the firmware installation process
 */
- (void)cancelInstallation;


#if SDK_INTERNAL == 1

/**
 *  For NRF/DFU recovery
 *
 *  @param delegate object that conforms to GTFirmwareInstallationProgressProtocol
 */
- (void)setRecoveryDelegate:(id <GTFirmwareInstallationProgressProtocol>)delegate;

#endif

@end
