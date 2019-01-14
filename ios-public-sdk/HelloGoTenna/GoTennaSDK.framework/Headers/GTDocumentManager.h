//
// Created by Julietta Yaunches on 1/12/15.
// Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface GTDocumentManager : NSObject
- (NSURL *)firmwareFilePathfor:(NSString *)filename;
- (NSString *)firmwareDirectory;
- (NSString *)extractFirmwareVersion:(NSString *)filename;
- (NSString *)versionNumberOnly:(NSString *)filename;
@end
