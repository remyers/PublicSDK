//
// Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "NRFProtocol.h"

@class ChunkProcessor;
@class GTPacket;
@class GTCommand;
@class GTKeepAliveProcessor;

@interface GTPeripheralManager : NSObject <CBPeripheralDelegate>

@property (nonatomic, strong) CBPeripheral *peripheral;
@property (nonatomic, weak) id<NRFProtocol> nrfProtocolDelegate;

@property (nonatomic, assign) BOOL isAllowedToPullData;
@property (nonatomic, copy) void (^onNRFUpdateCompleted)();

+ (GTPeripheralManager *)shared;

- (void)updatePeripheral:(CBPeripheral *)peripheral;

- (void)writeCommandPackets:(GTCommand *)command;

- (void)disconnect;

- (BOOL)peripheralIsConnected;

- (void)scanPeripheralServices:(void (^)())onCharacteristicsReceived;
@end
