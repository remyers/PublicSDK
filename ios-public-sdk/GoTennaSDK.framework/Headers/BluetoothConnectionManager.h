//
//  BluetoothConnectionManager.h
//  GoTenna
//
//  Created by Julietta Yaunches on 30/05/2014.
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

typedef NS_ENUM(NSInteger, GTDeviceType) {
    GTDeviceTypeGoTenna __deprecated_enum_msg("use GTDeviceTypeMesh or GTDeviceTypePro instead."),
    GTDeviceTypePro,
    GTDeviceTypeMesh
};

@protocol BluetoothPairingProtocol;
@protocol NRFProtocol;

/// Manager for connecting to goTenna bluetooth peripheral device
@interface BluetoothConnectionManager : NSObject <CBCentralManagerDelegate>

/// Pairing delegate that adopts the bluetooth pairing protocol, it will receive updates on key connection events.
@property (nonatomic, weak) id<BluetoothPairingProtocol> pairingDelegate;

/// Indicates whether currently scanning for device.
@property (nonatomic, readonly) BOOL scanning;

/**
 ###Shared instance
 
 Use this for to create access the common instance of this class.
 
 @return Singleton instance
 */
+ (instancetype)shared;

/**
 ###Scan For Device
 
 Use this method to scan for a device type.
 
 @param GTDeviceType    deviceType
 */
- (void)scanAndConnectForDevice:(GTDeviceType)deviceType;

/// Scan and connect to device type (previously set).
- (void)scanAndConnect;

/// Stop scan for device.
- (void)stopScan;

/// Reset the internal central manager.
- (void)resetCentralManager;

/// Disconnect from device.
- (void)userDisconnect;

/**
 Check if we are connected.
 
 @return BOOL
 */
- (BOOL)isConnected;

/**
 Check if we are scanning currently.
 
 @return BOOL
 */
- (BOOL)isScanning;

/**
 Check if bluetooth is off.
 
 @return BOOL
 */
- (BOOL)bluetoothOff;

/**
 Check if it is a mesh device.
 
 @return BOOL
 */
- (BOOL)isMeshDevice;

/**
 Check if it is a pro device.
 
 @return BOOL
 */
- (BOOL)isProDevice;

/**
 ###Set Device
 
 Use this method to set the device type before you scan.
 
 @param GTDeviceType    deviceType
 */
- (void)setDevice:(GTDeviceType)deviceType;

/**
 ###Get Device
 
 Get the current device that is set.
 */
- (GTDeviceType)getDeviceType;

/**
 ###Can Mesh?
 
 Check if the current device can mesh or not (this will usually be the case for the device you use).
 
 @return BOOL
 */
- (BOOL)currentDeviceTypeCanMesh;

#if SDK_INTERNAL == 1
@property (nonatomic, weak) id<NRFProtocol> nrfProtocolDelegate;
@property (nonatomic, readonly) CBCentralManager *centralManager;

- (void)scanForPeripheralsWithServices:(nullable NSArray<CBUUID *> *)services
                               options:(nullable NSDictionary<NSString *, id> *)options;
#endif

@end
