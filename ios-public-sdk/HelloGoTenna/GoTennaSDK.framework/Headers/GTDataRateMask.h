//
//  GTDataRateMask.h
//  GoTenna
//
//  Created by Ryan Cohen on 9/11/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTDataRate.h"

@interface GTDataRateMask : NSObject

// bandwidthHZ - 4540, 7280 and 1180 for FCC
// bandwidthHzOriginal - 6250, 12500 and 25000 orig before FCC
@property (nonatomic, readonly) int identifier;
@property (nonatomic, readonly) long bandwidthHz;
@property (nonatomic, readonly) long bandwidthHzOriginal;
@property (nonatomic, readonly) NSArray<GTDataRate *> *dataRates;

- (instancetype)initWithIdentifier:(int)identifier
                       bandwidthHz:(long)bandwidthHz
                bandwidthHzOriginal:(long)bandwidthHzOriginal
                         dataRates:(NSArray<GTDataRate *> *)dataRates;

+ (NSArray<GTDataRateMask *> *)getProDataRateMasks;

@end
