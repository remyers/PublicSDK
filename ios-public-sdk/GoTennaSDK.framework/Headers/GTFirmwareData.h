//
//  GTFirmwareData,h
//  goTenna
//
//  Created by Mike Lepore on 10/25/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GTFirmwareData : NSObject <NSCoding>
@property (nonatomic, strong) NSString *firmwareVersion;
@property (nonatomic, strong) NSString *firmwareDescription;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (BOOL)isValidFirmware;
@end
