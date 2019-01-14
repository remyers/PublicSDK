//
//  GTFrequencySlotData.h
//  GoTenna
//
//  Created by JOSHUA M MAKINDA on 11/3/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import "GTBaseMessageData.h"

@class GTFrequencyData;

@interface GTFrequencySlotData : GTBaseMessageData <GTMessageDataProtocol>

- (instancetype)initOutgoingWithFrequencySlot:(GTFrequencyData *)frequencySlot onError:(NSError **)error;
- (instancetype)initFromOrderedData:(NSArray<TLVSection*> *)array withSenderGID:(NSNumber *)senderGID;

+ (GTFrequencyData *)createFrequencySlotFromMessageData:(NSData *)messageData;
+ (NSData *)createMessageDataFromFrequencySlot:(GTFrequencyData *)frequencySlot;

@end
