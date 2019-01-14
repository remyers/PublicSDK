//
// Created by Julietta Yaunches on 1/13/15.
// Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

/// Holds important firmware version information.
@interface GTFirmwareVersion : NSObject <NSCoding>

/// Firmware version in string format.
@property (nonatomic) NSString *firmwareVersion;
/// Firmware file name for the current firmware this represents.
@property (nonatomic, copy) NSString *filename;
/// Date firmware was installed.
@property (nonatomic, strong) NSDate *installedDate;

/**
 ###Initialize Firmware File
 
 Call this to initialize the firmware version object with filename and firmware version.
 
 @param filename            file name of the firmware
 @param firmwareVersion     firmware version string
 @return Class instance
 */
+ (instancetype)initWithFilename:(NSString *)filename andFirmwareVersion:(NSString *)firmwareVersion;

/// Major version number as int
- (unsigned int)majorVersionNumber;
/// Minor version number as int
- (unsigned int)minorVersionNumber;
/// Build version number as int
- (unsigned int)buildVersionNumber;

/// Major version number in data format
- (NSData *)majorVersionData;
/// Minor version number in data format
- (NSData *)minorVersionData;
/// Build version number in data format
- (NSData *)buildVersionData;

/// String of the full file version
- (NSString *)printableVersion;

@end
