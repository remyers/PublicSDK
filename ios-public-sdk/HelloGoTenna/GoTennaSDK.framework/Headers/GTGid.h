//
//  GTGid.h
//  GoTenna
//
//  Created by Julietta Yaunches on 3/2/15.
//  Copyright (c) 2015 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTDataTypes.h"

/// GID storage object
@interface GTGid : NSObject

/// The actual GID
@property (nonatomic, strong, readonly) NSNumber *baseNumber;

/// The GID type
@property (nonatomic) GTGIDType type;

/**
 ###Init With GID
 
 Initialize the GID object using GID value.
 
 @param data   GID value.
 @return `GTGid`
 */
+ (GTGid *)initWithBase:(NSNumber *)number;

/**
 ###Init From GID Data
 
 Initialize the GID object using data.
 
 @param data   GID as data.
 @return `GTGid`
 */
+ (GTGid *)initfromData:(NSData *)data;

/// The actual GID as a string
- (NSString *)built;
/// GID as `NSData`
- (NSData *)asData;
/// GID as `NSData` with the type
- (NSData *)asDataWithType;
/// GID as `NSData` with the type and membership byte if applicable
- (NSData *)asDataWithTypeUsingMembershipByte:(NSData *)membershipByte;
/// GID byte length
- (NSUInteger)GIDDataByteLength;

@end
