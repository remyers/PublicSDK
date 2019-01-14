//
//  GTPairingManager.h
//  GoTenna
//
//  Created by Julietta Yaunches on 11/25/14.
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "GTPairingConnectionState.h"
#import "NRFScanResponseProtocol.h"

/// Protocol for handling state changes
@protocol GTPairingHandlerProtocol <NSObject>

- (void)updateState:(GTConnectionState)state;

@end

/// Protocol for bluetooth pairing
@protocol BluetoothPairingProtocol <NSObject>
- (void)didConnectToPeripheral;
- (void)bluetoothConnectionNotAvailable:(CBManagerState)state;
- (void)canNotConnectToPeripheral;
- (void)bluetoothPoweredOn;
- (void)nonUserDisconnectionOccurred;
@end

/// Manager for handling pairing, with finer access to commands and queries.
@interface GTPairingManager : NSObject <BluetoothPairingProtocol, NRFScanResponseProtocol>

/// Pairing handler that adopts protocol
@property (nonatomic) id<GTPairingHandlerProtocol> pairingHandler;

/// Determines whether a reconnection should occur once disconnected
@property (nonatomic) BOOL shouldReconnect;

/**
 ###Shared instance
 
 Use this for to create access the common instance of this class.
 
 @return Singleton instance
 */
+ (instancetype)shared;

/**
 ###Connect State
 
 Use this method to get the current connection status of your goTenna
 */
- (GTConnectionState)connectingState;

/**
 ###Update state
 
 Explicitly update the connection state. Used mainly to set state as `Disconnected`.
 
 @param GTConnectionState state
 */
- (void)updateState:(GTConnectionState)state;

/**
 ###Disconnect
 
 Disconnects a connected device.
 */
- (void)initiateDisconnect;

/**
 #Initiate goTenna scan
 
 Call this to connect to your goTenna.
 NOTE: before calling this, ensure to set the `pairingHandler` delegate to get callbacks on when the state changes to
 connected or any other states.
 */
- (void)initiateScanningConnect;

/**
 #Stop scan
 
 Stops scanning for devices.
 */
- (void)stopScanningConnect;

@end
