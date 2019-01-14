//
//  NRFProtocol.h
//  GoTennaSDK
//
//  Created by JOSHUA M MAKINDA on 9/10/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@protocol NRFProtocol <NSObject>

- (void)didAddDeviceToServices:(NSMutableArray<CBUUID*>*)services;
- (void)willStopScan;

- (BOOL)didInitiateCBManagerPoweredOnForNRF;
- (BOOL)disallowScanDueToNRF;
- (BOOL)hasDiscoveredNRFPeripheral:(CBPeripheral*)peripheral error:(NSError *)error;
- (BOOL)hasDiscoveredNRFCharacteristicForService:(CBService *)service withPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;
@end
