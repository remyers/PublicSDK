//
//  ResponseChunk.h
//  GoTenna
//
//  Created by Julietta Yaunches on 29/05/2014.
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTDataTypes.h"
#import "AntennaQuality.h"
#import "GTNackError.h"

@class GTMessageData;

@interface GTResponse : NSObject

@property (nonatomic, strong) NSData *commandData;
@property (nonatomic, strong) NSNumber *sequenceNumber;
@property (nonatomic, assign) NSUInteger hopCount;
@property (nonatomic, strong) NSNumber *rssiValue;
@property (nonatomic, assign) GTAntennaQualityLevel antennaQuality;
@property (nonatomic, strong) NSNumber *vswrValue;  // Voltage Standing Wave Ratio
@property (nonatomic) int resendId;
@property (nonatomic, assign) GTNackErrorTypes nackError;

@property (nonatomic) GTCommandResponseType responseCode;

- (BOOL)responsePositive;

@end
