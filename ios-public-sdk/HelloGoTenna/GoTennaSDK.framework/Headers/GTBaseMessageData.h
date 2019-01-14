//
// Created by Julietta Yaunches on 11/18/14.
// Copyright (c) 2014 goTenna-inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTLocationMessageData.h"
#import "GTPerimeterMessageData.h"
#import "GTRouteMessageData.h"
#import "GTCircleMessageData.h"
#import "GTRectangleMessageData.h"
#import "GTFrequencyData.h"

@class TLVSection, GTAudioData;

@interface GTBaseMessageData : NSObject

@property (nonatomic) NSString *messageType;
@property (nonatomic, strong) NSNumber *senderGID;
@property (nonatomic, strong) NSString *senderInitials;
@property (nonatomic, strong) NSNumber *addresseeGID;
@property (nonatomic, strong) NSNumber *receivingGID;
@property (nonatomic, strong) GTLocationMessageData *locationMessageData;
@property (nonatomic, strong) GTPerimeterMessageData *perimeterMessageData;
@property (nonatomic, strong) GTRouteMessageData *routeMessageData;
@property (nonatomic, strong) GTCircleMessageData *circleMessageData;
@property (nonatomic, strong) GTRectangleMessageData *rectangleMessageData;
@property (nonatomic, strong) GTFrequencyData *frequencyMessageData;
@property (nonatomic, strong) GTAudioData *audioData;
@property (nonatomic, copy) NSString *text;
@property (nonatomic, strong) NSArray *baseDataComponents;
@property (nonatomic, strong) GTLocationMessageData *senderLocationData;
@property (nonatomic, strong) NSDate *messageSentDate;
@property (nonatomic, assign) NSUInteger hopCount;
@property (nonatomic, strong) NSNumber *rssiValue;

- (instancetype)initOutgoingOnError:(NSError **)pError;
- (instancetype)initIncoming:(NSArray<TLVSection *> *)array withSenderGID:(NSNumber *)senderGID;

- (NSNumber *)getGIDNumber:(id)value;
- (void)setAddressedGID:(NSNumber *)number;

- (NSArray<TLVSection *> *)buildTLVSections;
- (NSArray<TLVSection *> *)getTLVSections;
- (NSData *)serializeToBytes;

@end
