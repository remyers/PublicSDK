//
// Created by Julietta Yaunches on 11/18/14.
// Copyright (c) 2014 goTenna-inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTMessageDataProtocol.h"
#import "GTBaseMessageData.h"
#import "GTTextOnlyMessageData.h"

@interface GTTextAndLocationMessageData : GTTextOnlyMessageData<GTMessageDataProtocol>
- (id)initOutgoingWithText:(NSString *)text andLocationData:(GTLocationMessageData *)data onError:(NSError **)error;

- (id)initOutgoingPerimeterWithText:(NSString *)text andLocationData:(GTPerimeterMessageData *)perimeterData onError:(NSError **)error;
- (id)initFromPerimeterOrderedData:(NSArray<TLVSection*> *)array withSenderGID:(NSNumber *)senderGID;

- (id)initOutgoingRouteWithText:(NSString *)text andLocationData:(GTRouteMessageData *)routeData onError:(NSError **)error;
- (id)initFromRouteOrderedData:(NSArray<TLVSection*> *)array withSenderGID:(NSNumber *)senderGID;

- (id)initOutgoingCircleWithText:(NSString *)text andLocationData:(GTCircleMessageData *)circleData onError:(NSError **)error;
- (id)initFromCircleOrderedData:(NSArray<TLVSection *> *)array withSenderGID:(NSNumber *)senderGID;

- (id)initOutgoingRectangleWithText:(NSString *)text andLocationData:(GTRectangleMessageData *)rectangleData onError:(NSError **)error;
- (id)initFromRectangleOrderedData:(NSArray<TLVSection *> *)array withSenderGID:(NSNumber *)senderGID;

@end
