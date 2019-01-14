//
//  GTFrequencyChannelData.h
//  goTenna
//
//  Created by Mike Lepore on 10/25/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
@class GTFrequencyData;

extern NSString *const kGTFrequencyErrorIsNotUnique;
extern NSString *const kGTFrequencyErrorIsIncorrectRange;
extern NSString *const kGTFrequencyErrorIsIncorrectSpacing;
extern NSString *const kGTFrequencyErrorHasMoreThanThreeChannels;
extern NSString *const kGTFrequencyErrorHasMoreThanThirteenDataChannels;

@interface GTFrequencyChannelData : NSObject <NSCoding>
@property (nonatomic, readwrite) NSUInteger hertz;
@property (nonatomic, assign) BOOL isControlChannel;
@property (nonatomic, assign) BOOL allowsMesh;
@property (nonatomic, assign) NSInteger dataRateMaskId;

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
- (instancetype)initWithFrequency:(NSUInteger)frequency isControlChannel:(BOOL)isControl;

// Parsing
- (NSDictionary *)toDictionary;

// Frequencies
- (void)addChannelForFrequency:(GTFrequencyData *)frequency;
- (void)updateChannelForFrequency:(GTFrequencyData *)frequency withChannel:(GTFrequencyChannelData *)updatedChannel;

// Helpers
//- (NSUInteger)convertMhzToHz;

// Checks
- (BOOL)isValidChannelAmongChannels:(NSArray <GTFrequencyChannelData *>*)frequencyChannels error:(NSError **)error index:(NSUInteger)index;
+ (BOOL)channelArraysMatch:(NSArray<GTFrequencyChannelData *> *)arrayA andOtherArray:(NSArray<GTFrequencyChannelData *> *)arrayB;

// Ranges
+ (NSUInteger)minimumFrequencyVHF;
+ (NSUInteger)maximumFrequencyVHF;

+ (NSUInteger)minimumFrequencyUHF;
+ (NSUInteger)maximumFrequencyUHF;

@end
