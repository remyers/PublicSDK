//
//  GTTextAndFrequencySlotMessageData.h
//  GoTennaSDK
//
//  Created by Ryan Cohen on 11/29/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "GTTextOnlyMessageData.h"
#import "GTMessageDataProtocol.h"
#import "GTBaseMessageData.h"
#import "GTFrequencySlotData.h"

@class GTFrequencySlotData;

@interface GTTextAndFrequencySlotMessageData : GTFrequencySlotData <GTMessageDataProtocol>

- (instancetype)initOutgoingWithText:(NSString *)text frequencyData:(GTFrequencyData *)frequencyData onError:(NSError **)error;
- (instancetype)initFromFrequencySlotOrderedData:(NSArray<TLVSection *> *)array senderGID:(NSNumber *)senderGID;

@end
