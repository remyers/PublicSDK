//
//  GTSendCommand.h
//  GoTenna
//
//  Created by JOSHUA M MAKINDA on 3/14/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import "GTCommand.h"

@class EncryptionInfoHeader;

@interface GTSendCommand : GTCommand

@property (nonatomic) BOOL isPublicKeyResponse;
@property (nonatomic) BOOL isKeyExchangeRequest;
@property (nonatomic, readonly) BOOL willEncrypt;
@property (nonatomic, readonly) NSData *outgoingData;
@property (nonatomic, readonly) NSNumber *senderGID;
@property (nonatomic, readonly) NSNumber *recipientGID;
@property (nonatomic, readonly) NSUInteger hopCount;
@property (nonatomic, strong) NSString *packetIdHash;
@property (nonatomic) int resendId;
@property (nonatomic, strong) EncryptionInfoHeader *encryptionInfoHeader;
@property (nonatomic) BOOL shouldNotAllowResend;
@property (nonatomic, readonly) BOOL shouldAllowResend;

/**
 *  Command to be sent to the goTenna that is specifically used for messages. Inherits from `GTCommand`
 */
- (instancetype)initWithOutgoingData:(NSData *)outgoingData
                           SenderGID:(NSNumber *)senderGID
                        recipientGID:(NSNumber *)recipientGID
                         willEncrypt:(BOOL)willEncrypt;
- (BOOL)hasPrivateReceiverGID;
- (void)incrementHopIndex;
- (void)setCurrentHop:(NSUInteger)hopCount;
@end
