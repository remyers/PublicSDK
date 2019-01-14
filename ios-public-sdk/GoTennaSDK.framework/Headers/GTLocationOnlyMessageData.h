//
// Created by Julietta Yaunches on 11/18/14.
// Copyright (c) 2014 goTenna. All rights reserved.
//

#import "GTBaseMessageData.h"
#import "GTMessageDataProtocol.h"

@interface GTLocationOnlyMessageData : GTBaseMessageData <GTMessageDataProtocol>

// GTLocationMessageData
- (instancetype)initFromOrderedData:(NSArray<TLVSection *> *)data withSenderGID:(NSNumber *)senderGID;
- (instancetype)initOutgoingWithLocation:(GTLocationMessageData *)data onError:(NSError **)error;

// GTPerimeterMessageData
- (instancetype)initFromPerimeterOrderedData:(NSArray<TLVSection *> *)array withSenderGID:(NSNumber *)senderGID;
- (instancetype)initOutgoingPerimeterWithLocation:(GTPerimeterMessageData *)data onError:(NSError **)error;

// GTRouteMessageData
- (instancetype)initFromRouteOrderedData:(NSArray<TLVSection *> *)array withSenderGID:(NSNumber *)senderGID;
- (instancetype)initOutgoingRouteWithLocation:(GTRouteMessageData *)data onError:(NSError **)error;

// GTCircleMessageData
- (instancetype)initFromCircleOrderedData:(NSArray<TLVSection *> *)array withSenderGID:(NSNumber *)senderGID;
- (instancetype)initOutgoingCircleWithLocation:(GTCircleMessageData *)data onError:(NSError **)error;

// GTRectangleMessageData
- (instancetype)initFromRectangleOrderedData:(NSArray<TLVSection *> *)array withSenderGID:(NSNumber *)senderGID;
- (instancetype)initOutgoingRectangleWithLocation:(GTRectangleMessageData *)data onError:(NSError **)error;

@end
