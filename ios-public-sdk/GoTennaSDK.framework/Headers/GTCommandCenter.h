//
// GTCommandCenter.h
// goTenna SDK
//

#import <Foundation/Foundation.h>
#import "GTDataTypes.h"
#import "GTResponse.h"
#import "GTCommand.h"
#import "GTGroupCreationMessageData.h"
#import "RegionBound.h"
#import "FrequencyEnumConstants.h"
#import "BluetoothDebugValues.h"

@class SystemInfoResponseData;
@class GTError;
@class FrequencyMode;
@class BinaryLogResponseData;
@class GTSendCommand;
@class GTFrequencyChannelData;
@class GTDataRateMask;
@class GTDataRate;
@class GTLatchedErrorInfo;
@class GTDeviceAlertResult;

/// Central command center singleton used to execute key tasks in an application.
@interface GTCommandCenter : NSObject

/// Set this for execution upon message data receiving.
@property (nonatomic, copy) void (^onIncomingMessage)(GTMessageData *);

/// Set this for latch error info.
@property (nonatomic, copy) void (^onIncomingLatchedError)(GTLatchedErrorInfo *);

/// Set this for a device alert result.
@property (nonatomic, copy) void (^onIncomingDeviceAlert)(GTDeviceAlertResult *);

/**
 ###Shared instance
 
 Use this for to create access the common instance of this class.
 
 @return Singleton instance
 */
+ (instancetype)shared;

/**
 ###Send echo
 
 Sends an echo command to the connected goTenna.
 Upon receiving an echo the goTenna's LED will flash.
 No actual message is transmitted when an echo is sent.
 
 @param onResponse Called when your goTenna responds with a postive or negative acknowledgement
 @param onError    Called when an error occurs (See error code for details)
 */
- (void)sendEchoCommand:(void (^)(GTResponse *))onResponse onError:(void (^)(NSError *))onError;

/**
 ###Set goTenna GID
 
 This method is used to set a goTenna's unique GID. This GID is used for one-to-one messaging.
 When this gets set, the previous one-to-one GID for the connected goTenna will be erased and the new
 GID set.
 
 @param number   The GID to assign to the goTenna.
 @param username The name of the user who's GID this is.
 @param onError  Called when an error occurs (See error code for details)
 */
- (void)setgoTennaGID:(NSNumber *)number withUsername:(NSString *)username onError:(void (^)(NSError *))onError;

/**
 ###Delete GID
 
 Use to delete Group GIDs from your goTenna. AFter calling this, you should receive no further messages for the
 given GID.
 
 NOTE: if you call this with the goTenna's unique GID, you'll need to call @c setGoTennaGID: before continueing to use
 your goTenna. You do NOT need to call this before updating your goTenna's unique GID.
 
 @param gidToDelete The GID that should be removed from the goTenna.
 @param onError     Called when an error occurs (See error code for details).
 */
- (void)deleteGID:(NSNumber *)gidToDelete onError:(void (^)(NSError *))onError;

/**
 ###Send 1-to-1 Message
 
 With this you send a single message to another goTenna user. This is the only means of
 sending a message where you'll receive negative or positive confirmation that the receiver
 received your message
 
 NOTE: Must have set goTenna GID before calling this
 NOTE: If your receiver needs to know the sender's GID, you'll need to send it in the payload
 
 @param messageData    The message's data, such as text, preferably formatted in some easily parse-able format.
 @param destinationGID The GID of the user who will receive this private message (must be 15 digits or less and not 111-111-1111).
 @param senderGID      The response listener callback for the command.
 @param onResponse     Called when your goTenna responds with a postive or negative acknowledgement.
 @param onError        Called when an error occurs (See error code for details).
 */
- (void)sendMessage:(NSData *)messageData
              toGID:(NSNumber *)destinationGID
            fromGID:(NSNumber *)senderGID
         onResponse:(void (^)(GTResponse *))success
            onError:(void (^)(NSError *))onError;

/**
 ###Resend Message
 
 With this you send a single message to another goTenna user. This is the only means of
 sending a message where you'll receive negative or positive confirmation that the receiver
 received your message
 
 NOTE: Must have set goTenna GID before calling this
 NOTE: If your receiver needs to know the sender's GID, you'll need to send it in the payload
 
 @param messageData    The message's data, such as text, preferably formatted in some easily parse-able format.
 @param destinationGID The GID of the user who will receive this private message (must be 15 digits or less and not 111-111-1111).
 @param senderGID      The response listener callback for the command.
 @param onResponse     Called when your goTenna responds with a postive or negative acknowledgement.
 @param onError        Called when an error occurs (See error code for details).
 @param resendId       The id of the message to resend that was returned in the previous @c GTResponse or @c GTError.
 */
- (void)resendMessage:(NSData *)messageData
                toGID:(NSNumber *)destinationGID
              fromGID:(NSNumber *)senderGID
           onResponse:(void (^)(GTResponse *))success
              onError:(void (^)(NSError *))onError
             resendID:(int)resendId;

/**
 ###Broadcast Message
 
 A broadcast is also referred to as a Shout. This is because every nearby goTenna will received this message.
 Broadcast messages cannot be encrypted, their data is sent as plaintext.
 
 @param messageData Message data with text 160 characters or less
 @param onResponse  Called on response
 @param onError     Called on error (See error code for details)
 */
- (void)sendBroadcast:(NSData *)messageData toGID:(NSNumber *)destinationGID onResponse:(void (^)(GTResponse *))success onError:(void (^)(NSError *))onError;

/**
 ###Send Group Invite Message
 
 With this you send a single group invite to another goTenna group member. You'll receive negative or positive confirmation that the receiver received your message, this is used to create the group.
 
 NOTE: Must have set goTenna GID before calling this
 NOTE: If your receiver needs to know the sender's GID, you'll need to send it in the payload
 
 @param messageData    The group creation message data.
 @param destinationGID The GID of the user who will receive this private message (must be 15 digits or less and not 111-111-1111).
 @param onResponse     Called when your goTenna responds with a postive or negative acknowledgement.
 @param onError        Called when an error occurs (See error code for details).
 */
- (void)sendGroupInviteMessage:(GTGroupCreationMessageData *)messageData
                         toGID:(NSNumber *)destinationGID
                    onResponse:(void (^)(GTResponse *))onResponse
                       onError:(void (^)(NSError *))onError;

/**
 ###Create Group
 
 Call this method to create a group.
 You must have the unique GIDs for all members of the group.
 When you call this, a one-to-one message is sent to each member of the group notifying them of group creation
 
 NOTE: if the group is large, this method can take a while to process as each message goes out
 
 @param memberGIDs       Cannot include either 1111111111 or 9999999999, other group GIDs, cannot exceed 10 members
 @param onMemberResponse Called for each member response, @c responseCode in @c GTResponse can be used to determine whether receiver received the message
 @param senderGID        Sender's GID
 @param onError          Required. Called on error (See error code for details)
 @return                 Created Group GID
 */
- (NSNumber *)createGroupWithGIDs:(NSArray *)memberGIDs
                 onMemberResponse:(void (^)(GTResponse *, NSNumber *memberGID))onMemberResponse
                          fromGID:(NSNumber *)senderGID
                          onError:(void (^)(NSError *, NSNumber *))onError;

/**
 ###On Group Created
 
 Set block to perform when receiving a group creation message
 As a member of a created group, you need to know when you've been added to a group. Here,
 you are added to a group
 
 NOTE: you must have called setGotennaGID with your unique GID to receive these messages
 
 @param externalOnGroupCreate Called when you are added to a group. Contains group info
 */
- (void)setOnGroupCreated:(void (^)(GTGroupCreationMessageData *))externalOnGroupCreate;

/**
 ###Get System Info (High Priority)
 
 @param onSuccess System info response object
 @param onError   Called when an error occurs (See error code for details)
 */
- (void)sendGetSystemInfoOnSuccess:(void (^)(SystemInfoResponseData *))onSuccess onError:(void (^)(NSError *))onError;

/**
 ###Get System Info Medium Priority
 
 @param onSuccess System info response object
 @param onError   Called when an error occurs (See error code for details)
 */
- (void)sendGetSystemInfoOnSuccessMediumPriority:(void (^)(SystemInfoResponseData *))onResponse onError:(void (^)(NSError *))onError;

/**
 ###Send MTU Test
 
 @param onSuccess MTU test response for whether safe to use with large chunk packet data
 @param onError   Called when an error occurs (See error code for details)
 */
- (void)sendMtuTestCommandOnSuccess:(void (^)(GTResponse *))onResponse onError:(void (^)(NSError *))onError;

/**
 ###Set Mesh Geofence Region
 
 @param onResponse Called when the command finishes. See the @c responsePositive property for command success.
 @param onError    Called when an error occurs (See error code for details)
 */
- (void)sendSetGeoRegion:(RegionID)regionID onResponse:(void (^)(GTResponse *))onResponse onError:(void (^)(NSError *))onError;

/**
 ###Get Mesh Geofence Region
 
 @param onResponse Called when the command finishes. See the @c responsePositive property for command success.
 @param onError    Called when an error occurs (See error code for details)
 */
- (void)sendGetGeoRegionOnResponse:(void (^)(GTResponse *))onResponse onError:(void (^)(NSError *))onError;

/**
 ###Create Multicast Group
 
 Allows the user to create their own multicast group. A multicast group works just like a regular
 group except there is no encryption, and you do not need to know who is in the group to join.
 
 This function is only available to Super SDK users.
 
 @param  multicastGroupGID GID for the multicast group
 @return True if the function ran successfully
 */
- (BOOL)createMulticastGroup:(NSNumber *)multicastGroupGID;

/**
 ###Send Frequency Channels OTA
 
 @param frequencyChannels Array of @c GTFrequencyChannelData objects contained in @c GTFrequencyData
 @param onResponse        Called when the command finishes. See the @c responsePositive property for command success.
 @param error             Called when an error occurs (See error code for details)
 */
- (void)sendFrequencyChannels:(NSArray <GTFrequencyChannelData *> *)frequencyChannels
                    onSuccess:(void (^)(GTResponse *))onResponse
                      onError:(void (^)(NSError *))error;

/**
 ###Set Power Level
 
 @param powerLevelIndex Index of power level to set (Levels 1/2 - 5)
 @param onResponse      Called when the command finishes. See the @c responsePositive property for command success.
 @param error           Called when an error occurs (See error code for details)
 */
- (void)sendSetPowerLevel:(int) powerLevelIndex
                onSuccess:(void (^)(GTResponse *))onResponse
                  onError:(void (^)(NSError *))error;

/**
 ###Set Bitrate
 
 @param dataRateMask @c GTDataRateMask object to set bandwidth (6.25kHz, 12.5kHz, 25kHz)
 @param dataRate     @c GTDataRate object to set data rate (4800, 9600, 19200kbps)
 @param onResponse   Called when the command finishes. See the @c responsePositive property for command success.
 @param onError      Called when an error occurs (See error code for details)
 */
- (void)sendSetBitrate:(GTDataRateMask *)dataRateMask
              dataRate:(GTDataRate *)dataRate
            onResponse:(void (^)(GTResponse *response))onResponse
               onError:(void (^)(NSError *))onError;

/**
 ###Get Bitrate
 
 @param block Block returning @c GTDataRateMask bandwith, and @c GTDataRate data rate
 @param error                 Called when an error occurs (See error code for details)
 */
- (void)sendGetConfiguredBitrate:(void (^)(GTDataRateMask *configuredMask, GTDataRate *configuredDataRate))block
                         onError:(void (^)(NSError *))error;

/**
 ###Set should enable LED
 
 @param shouldDisableLED YES if the device LED should be enabled for events other than echo
 @param onResponse      Called when the command finishes. See the @c responsePositive property for command success.
 @param onError         Called when an error occurs (See error code for details)
 */
- (void)sendShouldDisableLED:(BOOL)shouldDisableLED
                  onResponse:(void (^)(GTResponse *response))onResponse
                     onError:(void (^)(NSError *))onError;

/**
 ###Get LED enabled
 
 @param onResponse Called when the command finishes. See @c ledIsEnabled for current LED status
 */

- (void)sendGetLEDEnabled:(void (^)(BOOL ledIsEnabled))onResponse;

/**
 ###Send should enable Listen Only Mode
 
 @param shouldEnableListenOnly YES if the listen-only mode should be enabled
 @param onResponse      Called when the command finishes. See the @c responsePositive property for command success.
 @param onError         Called when an error occurs (See error code for details)
 */
- (void)sendShouldEnableListenOnlyMode:(BOOL)shouldEnableListenOnly onResponse:(void (^)(GTResponse *response))onResponse onError:(void (^)(NSError *))onError;


/**
 ###Send should enable Relay Mode
 
 @param shouldEnableRelay YES if the relay mode should be enabled, NO otherwise
 @param shouldResetGotenna - Parameter ignored
 @param onResponse      Called when the command finishes. See the @c responsePositive property for command success.
 @param onError         Called when an error occurs (See error code for details)
 */
- (void)sendShouldEnableRelayMode:(BOOL)shouldEnableRelay shouldResetGotenna:(BOOL)shouldResetGotenna onResponse:(void (^)(GTResponse *response))onResponse onError:(void (^)(NSError *))onError;

/**
 ###Get Relay Mode enabled status
 
 @param onRelayMode     Called when the command finishes. isRelayMode is returned
 @param onError         Called when an error occurs (See error code for details)
 */
- (void)sendGetRelayModeEnabled:(void (^)(BOOL isRelayMode))onRelayMode onError:(void (^)(NSError *))onError;

/**
 ###Get BDI
 
 The basic debugging info logs the causes of software-based problems like hard faults or device errors.
 This function is triggered automatically if the BCTS contains an active bit indicating available BDI.
 */
- (void)sendGetBasicDebugInfo;

/**
 ###Get DDI
 
 Detailed debugging info is a collection of lifetime statistics and information about local conditions.
 This function is triggered automatically if the BCTS contains an active bit indicating available DDI.
 */
- (void)sendGetDetailedDebugInfo;

/**
 ###Get BLE Debug Information
 
 Get an internal debug struct of message stats consisting of counters ... (see BlueToothDebugValues.m)
 */
- (void)sendGetBluetoothDebugInfo:(void (^)(BluetoothDebugValues *debugValues))onResponse onError:(void (^)(NSError *))onError;

/**
 ###Set BLE Reset Bluetooth Debug Information
 
 Reset the internal debug structure of message stats.  Cumulative counters will be reset.
 */
- (void)sendResetBluetoothDebugInfo:(void (^)(GTResponse *response))onResponse onError:(void (^)(NSError *))onError;

/**
 ###Send Set App Token
 
 Send the application token.
 
 @param onResponse   Called when the command finishes. See the @c responsePositive property for command success.
 @param onError      Called when an error occurs (See error code for details)
 */
- (void)sendSetAppTokenOnResponse:(void (^)(GTResponse *))onResponse onError:(void (^)(NSError *))error;

/**
 ###Reset goTenna
 
 Sends reset goTenna command to the device.
 */
- (void)resetGotenna;

/**
 ###Set Public Key
 
 Sets the public key on the device.
 
 @param publicKey data to send
 */
- (void)setPublicKey:(NSData *)publicKey;

/**
 ###Send Store Date Time
 
 Sends to the device an emergency message to be stored.
 
 @param emergencyMessage Emergency message to send that will be stored.
 @param onResponse   Called when the command finishes. See the @c responsePositive property for command success.
 @param onError      Called when an error occurs (See error code for details)
 */
- (void)sendStoreDateTimeWithEmergencyMessage:(NSString *)emergencyMessage
                                   onResponse:(void (^)(GTResponse *response))onResponse
                                      onError:(void (^)(NSError *))onError;

/**
 ###Send Debug Stats
 
 Sends the statistics to the device.
 
 @param onResponse   Called when the command finishes. See the @c responsePositive property for command success.
 @param onError      Called when an error occurs (See error code for details)
 */

- (void)sendDebugStatisticsCommand:(void (^)(GTResponse *))onResponse
                           onError:(void (^)(NSError *))onError;

/**
 ###Send Reset Debug Stats
 
 Sends a reset statistics command to the device.
 
 @param onResponse   Called when the command finishes. See the @c responsePositive property for command success.
 @param onError      Called when an error occurs (See error code for details)
 */

- (void)sendResetDebugStatisticsCommand:(void (^)(GTResponse *))onResponse
                                onError:(void (^)(NSError *))onError;

/**
 ###Start Emergency Beacon Broadcast
 
 Start the emergency beacon broadcast.
 
 @param onResponse   Called when the command finishes. See the @c responsePositive property for command success.
 @param onError      Called when an error occurs (See error code for details)
 */

- (void)startEmergencyBeaconBroadcastOnResponse:(void (^)(GTResponse *response))onResponse
                                        onError:(void (^)(NSError *))onError;

/**
 ###Stop Emergency Beacon Broadcast
 
 Stop the emergency beacon broadcast.
 
 @param onResponse   Called when the command finishes. See the @c responsePositive property for command success.
 @param onError      Called when an error occurs (See error code for details)
 */

- (void)stopEmergencyBeaconBroadcastOnResponse:(void (^)(GTResponse *response))onResponse
                                       onError:(void (^)(NSError *))onError;

/**
 ###Get Emergency Beacon Status
 
 The current status of the beacon broadcast.
 
 @param onStatusReceived   Called when the command finishes. See the statusReceived property for command success.
 @param onError      Called when an error occurs (See error code for details)
 */

- (void)getEmergencyBeaconBroadcastStatusOnResponse:(void (^)(BOOL statusReceived))onStatusReceived
                                            onError:(void (^)(NSError *))onError;

/// Sends a get message request to goTenna.
- (void)sendGetMessageRequest;

/// Send pull alert.
- (void)sendPullAlert;

/// Add group GID.
- (void)addGroupGID:(NSNumber *)number;

#if SDK_INTERNAL == 1

- (NSInteger)maxDataPayloadLength;
- (GTCommand *)currentQueueCommand;
- (NSArray *)remainingCommands;

- (void)sendHardwareTransmit;
- (void)sendHardReset;
- (void)sendAntennaSweep:(BOOL)sweepOn;
- (void)sendPowerSavingTransmit:(BOOL)on;

- (void)sendChannelScanForBand:(ChannelSweepType)type
                    onResponse:(void (^)(NSArray<NSNumber *> *))onResponse
                       onError:(void (^)(NSError *))onError;
#endif

@end
