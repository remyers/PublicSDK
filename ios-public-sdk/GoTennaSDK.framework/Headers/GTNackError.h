//
//  GTNackError.h
//  GoTennaSDK
//
//  Created by Edmund Trujillo on 8/17/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, GTNackErrorTypes) {
    GT_NACK_NONE,
    GT_NACK_TTL_MISSING,
    GT_NACK_MORSE_MISSING,
    GT_NACK_FW_RX_MESH_MISSING,
    GT_NACK_MSH_HDR_MISSING,
    GT_NACK_MSG_PAYLOAD_MISSING,
    GT_NACK_ENCRYPTION_HEADER_MISSING,
    GT_NACK_MESSAGE_OVERRUN,
    GT_NACK_TRANSMIT_DISABLED,          // Trying to send while in Listen Only Mode
    GT_NACK_INVALID_OPERATION_MODE,     // Trying to send while in Relay Mode
    GT_NACK_TEMP_THRESHOLD_BACKOFF,
    GT_NACK_MAC_BUSY_CHANNEL_BACKOFF
} ;

@interface GTNackError : NSObject

+ (GTNackErrorTypes)getError:(NSInteger)errorCode;

@end
