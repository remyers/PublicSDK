//
//  GTFrequencyValidation.h
//  GoTennaSDK
//
//  Created by JOSHUA M MAKINDA on 12/6/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
@class GTFrequencyChannelData;
@class GTFrequencyData;

extern NSUInteger const kMaxFrequencyDataChannels;
extern NSUInteger const kMaxFrequencyControlChannels;

NS_ASSUME_NONNULL_BEGIN

@interface GTFrequencyValidation : NSObject

+ (BOOL)validateFrequency:(GTFrequencyData *)frequencyData error:(NSError**)error;
+ (BOOL)validateChannelList:(NSArray<GTFrequencyChannelData*>*)channelList error:(NSError**)error;

@end

NS_ASSUME_NONNULL_END
