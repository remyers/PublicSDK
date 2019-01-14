//
//  BluetoothDebugValues.h
//  GoTennaSDK
//
//  Created by Edmund Trujillo on 7/12/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BluetoothDebugValues : NSObject

- (instancetype) initWithData:(NSData *)data;

- (NSNumber *) FECErrorCount;
- (NSNumber *) droppedControlPackets;
- (NSNumber *) droppedDataPackets;
- (NSNumber *) relayedTXPackets;
- (NSNumber *) relayedRXPackets;

@end
