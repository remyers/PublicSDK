//
// Created by Julietta Yaunches on 11/4/14.
// Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTResponse.h"

typedef enum : NSUInteger {
    GTCommandPriorityLowest,
    GTCommandPriorityVeryLow,
    GTCommandPriorityLow,
    GTCommandPriorityMedium,
    GTCommandPriorityHigh,
    GTCommandPriorityRequired,
} GTCommandPriority;

/// Command object used to send data to the goTenna device
@interface GTCommand : NSObject

/// Data packets that are sent to the goTenna
@property (nonatomic, strong) NSArray *packets;
/// Whether a response has been received from the goTenna yet
@property (nonatomic) BOOL responseReceived;
/// Can this operation be paused (for internal use)
@property (nonatomic) BOOL isPausable;
/// Should not resend with more hops (for internal use)
@property (nonatomic) BOOL shouldNotResendWithMoreHops;
/// Response block to be set for when a positive (ACK) or negative (NACK) response is received from the device
@property (nonatomic, copy) void (^processResponse)(GTResponse *);
/// Response block to be set for when an error response is received from the device
@property (nonatomic, copy) void (^onError)(NSError *);
/// Command code specific to the command
@property (nonatomic) const char *commandCode;
/// Raw data being used by the command
@property (nonatomic, strong) NSData *rawData;
/// The message header data used for packet/s transmission
@property (nonatomic, strong) NSData *messageHeaderData;
/// The hash for the public key
@property (nonatomic, strong) NSData *pubKeyHash;
/// Message data being used by the command
@property (nonatomic, strong) NSData *messageData;
/// The hop count as data
@property (nonatomic, strong) NSData *hopCountData;
/// Positive response code
@property (nonatomic) const char *positiveResponse;
/// Negative response code
@property (nonatomic) const char *negativeResponse;
/// Command name (usually the same as the 'log')
@property (nonatomic, copy) NSString *log;
/// Command log (usually the same as the 'name')
@property (nonatomic, copy) NSString *name;
/// Send attempts for the command
@property (nonatomic) int sendAttempts;
/// Send times attempted
@property (nonatomic) int timesToAttempt;
/// The command time out count, in seconds
@property (nonatomic) NSTimeInterval commandTimeoutAmount;
/// Command sequence number
@property (nonatomic) int seqNumber;
/// The command priority (default `GTCommandPriorityVeryLow`)
@property (nonatomic) GTCommandPriority priority;
/// String version of the current priority of the command
@property (nonatomic, readonly) NSString *priorityPrintable;

/**
 ###Should Retry?
 
 If the command retry should occur or not (for internal use)
 
 @return BOOL
 */
- (BOOL)shouldRetry;

/**
 ###Prepare for next attempt
 
 Prepare for the next attempt (for internal use)
 */
- (void)prepareForNextAttempt;

/**
 ###Initiate timeout
 
 Set timeout block (generally for internal use)
 
 @param onTimeout   Called when the command times out.
 */
- (void)initiateWriteTimeoutOnTimeout:(void (^)())onTimeout;

/**
 ###Get Resend ID
 
 Get the resend ID (for internal use)
 
 @param onResponse   Called when the command finishes. See the @c responsePositive property for command success.
 @return Int
 */
- (void)invalidateTimeout;
/**
 ###Get Resend ID
 
 Get the resend ID (for internal use)
 
 @return Int
 */
- (int)getResendId;

@end
