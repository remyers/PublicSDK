//
//  GTLocationMessageData.h
//  GoTenna
//
//  Created by Julietta Yaunches on 11/14/14.
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import "GTMessageDataProtocol.h"

@class TLVSection;

@interface GTLocationMessageData : NSObject <GTMessageDataProtocol>

@property (nonatomic, strong) NSNumber *uuid;
@property (nonatomic, strong) NSNumber *locationType;
@property (nonatomic, strong) NSNumber *latitude;
@property (nonatomic, strong) NSNumber *longitude;
@property (nonatomic, readonly) int gpsTimestamp;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, strong) NSNumber *locationSharingFrequencyIndex;
@property (nonatomic, strong) NSNumber *locationSharingDurationIndex;
@property (nonatomic) short accuracyInMeters;
@property (nonatomic) BOOL isFirstPeriodicallySharedLocation;

- (instancetype)initFromOrderedData:(NSArray<TLVSection *> *)tlvSections withSenderGID:(NSNumber *)senderGID;

- (instancetype)initWithLocationType:(NSNumber *)number
                         andLatitude:(NSNumber *)latitude
                        andLongitude:(NSNumber *)longitude
                     andGPSTimestamp:(NSTimeInterval)gpsTimestamp
                             andName:(NSString *)name
                             andUUID:(NSNumber *)uuid
              locationFrequencyIndex:(NSNumber *)locationFrequencyIndex
                             onError:(NSError **)error;

- (instancetype)initWithLocationType:(NSNumber *)number
                         andLatitude:(NSNumber *)latitude
                        andLongitude:(NSNumber *)longitude
                     andGPSTimestamp:(NSTimeInterval)gpsTimestamp
                             andName:(NSString *)name
                             andUUID:(NSNumber *)uuid
              locationFrequencyIndex:(NSNumber *)locationFrequencyIndex
               locationDurationIndex:(NSNumber *)locationDurationIndex
                    accuracyInMeters:(short)accuracyInMeters
   isFirstPeriodicallySharedLocation:(BOOL)isFirstPeriodicallySharedLocation
                             onError:(NSError **)error;

- (NSArray<TLVSection *> *)getTLVSections;
- (NSData *)serializeToBytes;

@end
