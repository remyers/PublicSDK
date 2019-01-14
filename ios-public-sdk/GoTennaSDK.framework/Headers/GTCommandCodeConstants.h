//
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * const kMessageTypeTextOnly;
extern NSString * const kMessageTypeTextAndLocation;
extern NSString * const kMessageTypeLocationOnly;
extern NSString * const kMessageTypeLocationRequestOnly;
extern NSString * const kMessageTypeLocationRequestAndText;
extern NSString * const kMessageTypeSetGroupGID;
extern NSString * const kMessageTypePingTextOnly;
extern NSString * const kMessageTypeFirmwarePublicKeyResponse;
extern NSString * const kMessageTypeUserPublicKeyResponse;
extern NSString * const kMessageTypePublicKeyRequest;
extern NSString * const kMessageTypeNetRelayRequest;
extern NSString * const kMessageTypeNetRelaySuccessResponse;

// Mesh
extern NSString * const kMessageTypeMeshPublicKeyRequest;
extern NSString * const kMessageTypeMeshPublicKeyResponse;

// Pro
extern NSString * const kMessageTypeTextAndFrequencySlot;
extern NSString * const kMessageTypeFrequencySlotOnly;
extern NSString * const kMessageTypeTextAndMapPerimeter;
extern NSString * const kMessageTypeMapPerimeterOnly;
extern NSString * const kMessageTypeTextAndMapRoute;
extern NSString * const kMessageTypeMapRouteOnly;
extern NSString * const kMessageTypeTextAndCircle;
extern NSString * const kMessageTypeCircleOnly;
extern NSString * const kMessageTypeTextAndSquare;
extern NSString * const kMessageTypeSquareOnly;
extern NSString * const kMessageTypeAudio;

extern const char *gtSetGIDCommandCode;
extern const char *gtSetGIDResponseCode;
extern const char *gtSetGIDFailureCode;

extern const char *gtResetGotennaCommandCode;
extern const char *gtResetGotennaResponseCode;
extern const char *gtResetGotennaFailureCode;

extern const char *gtSetPublicKeyCommandCode;
extern const char *gtSetPublicKeyResponseCode;
extern const char *gtSetPublicKeyFailureCode;

extern const char *gtDeleteLastMessageCommandCode;
extern const char *gtDeleteLastMessageResponseCode;
extern const char *gtDeleteLastMessageFailureCode;

extern const char *gtGetMessageCommandCode;
extern const char *gtGetMessageResponseCode;
extern const char *gtGetMessageFailureCode;

extern const char *gtSendMessageCommandCode;
extern const char *gtSendMessageResponseCode;
extern const char *gtSendMessageFailureCode;

extern const char *gtGetSystemInfoCommandCode;
extern const char *gtGetSystemInfoResponseCode;
extern const char *gtGetSystemInfoFailureCode;

extern const char *gtEchoCommandCode;
extern const char *gtEchoResponseCode;
extern const char *gtEchoFailureCode;

extern const char *gtDisconnectGotennaCommandCode;
extern const char *gtDisconnectGotennaResponseCode;
extern const char *gtDisconnectGotennaFailureCode;

extern const char *gtDeleteGIDCommandCode;
extern const char *gtDeleteGIDResponseCode;
extern const char *gtDeleteGIDFailureCode;

extern const char *gtInitiateNewFirmwareWriteCommandCode;
extern const char *gtInitiateNewFirmwareWriteResponseCode;
extern const char *gtInitiateNewFirmwareWriteFailureCode;

extern const char *gtWriteFirmwareDataCommandCode;
extern const char *gtWriteFirmwareDataResponseCode;
extern const char *gtWriteFirmwareDataFailureCode;

extern const char *gtFinalizeFirmwareCommandCode;
extern const char *gtFinalizeFirmwareResponseCode;
extern const char *gtFinalizeFirmwareFailureCode;

extern const char *gtSetAppTokenCode;
extern const char *gtSetAppTokenResponseCode;
extern const char *gtSetAppTokenFailureCode;

extern const char *gtGIDTypeOneToOne;
extern const char *gtGIDTypeGroup;
extern const char *gtGIDTypeShout;
extern const char *gtGIDTypeEmergency;

extern const char *gtSetAppTokenCode;
extern const char *gtSetAppTokenResponseCode;

extern const char *gtActivateAntennaSweepCommandCode;
extern const char *gtActivateAntennaSweepResponseCode;
extern const char *gtActivateAntennaSweepFailureCode;

extern const char *gtChannelScanCommandCode;
extern const char *gtChannelScanResponseCode;
extern const char *gtChannelScanFailureCode;

extern const char *gtFrequencyModeCommandCode;
extern const char *gtFrequencyModeResponseCode;
extern const char *gtFrequencyModeFailureCode;

extern const char *gtFrequencyModeNormal;
extern const char *gtFrequencyModeLow;
extern const char *gtFrequencyModeHigh;

extern const char *gtHardwareTransmitCommandCode;

extern const char *gtGetBinaryLogCommandCode;
extern const char *gtGetBinaryLogResponseCode;
extern const char *gtGetBinaryLogFailureCode;

extern const char *gtDeleteBinaryLogCommandCode;
extern const char *gtDeleteBinaryLogResponseCode;
extern const char *gtDeleteBinaryLogFailureCode;

extern const char *gtBERTestCommandCode;
extern const char *gtBERTestResponseCode;
extern const char *gtBERTestFailureCode;

extern const char *gtStoreDateTimeCommandCode;
extern const char *gtStoreDateTimeResponseCode;
extern const char *gtStoreDateTimeFailureCode;

extern const char *gtPowerSavingCommandCode;
extern const char *gtPowerSavingResponseCode;
extern const char *gtPowerSavingFailureCode;

extern const char *gtHardResetCommandCode;
extern const char *gtHardResetResponseCode;
extern const char *gtHardResetFailureCode;

extern const char *gtSetConfigPropertyCommandCode;
extern const char *gtSetConfigPropertyResponseCode;
extern const char *gtSetConfigPropertyFailureCode;

extern const char *gtSetRuntimePropertyCommandCode;
extern const char *gtSetRuntimePropertyResponseCode;
extern const char *gtSetRuntimePropertyFailureCode;

extern const char *gtGetRuntimePropertyCommandCode;
extern const char *gtGetRuntimePropertyResponseCode;
extern const char *gtGetRuntimePropertyFailureCode;

extern const char *gtDebugStatsCommandCode;
extern const char *gtDebugStatsResponseCode;
extern const char *gtDebugStatsFailureCode;

extern const char *gtResetDebugStatsCommandCode;
extern const char *gtResetDebugStatsResponseCode;
extern const char *gtResetDebugStatsFailureCode;

extern const char *gtSetGeoRegionCommandCode;
extern const char *gtSetGeoRegionResponseCode;
extern const char *gtSetGeoRegionFailureCode;

extern const char *gtGetGeoRegionCommandCode;
extern const char *gtGetGeoRegionResponseCode;
extern const char *gtGetGeoRegionFailureCode;

extern const char *gtGetConfigPropertyCommandCode;
extern const char *gtGetConfigPropertyResponseCode;
extern const char *gtGetConfigPropertyFailureCode;

extern const char *gtGetBdiInfoCommandCode;
extern const char *gtGetBdiInfoResponseCode;
extern const char *gtGetBdiInfoFailureCode;

extern const char *gtGetDdiInfoCommandCode;
extern const char *gtGetDdiInfoResponseCode;
extern const char *gtGetDdiInfoFailureCode;

extern const char *gtPullDeviceAlertCommandCode;
extern const char *gtPullDeviceAlertResponseCode;
extern const char *gtPullDeviceAlertFailureCode;

extern const char *gtStoreEmergencyMessageCommandCode;
extern const char *gtStoreEmergencyMessagetResponseCode;
extern const char *gtStoreEmergencyMessageFailureCode;

extern const char *gtGetBluetoothDebugValuesCommandCode;
extern const char *gtGetBluetoothDebugValuesResponseCode;
extern const char *gtGetBluetoothDebugValuesFailureCode;

extern const char *gtResetBluetoothDebugValuesCommandCode;
extern const char *gtResetBluetoothDebugValuesResponseCode;
extern const char *gtResetBluetoothDebugValuesFailureCode;

@interface GTCommandCodeConstants : NSObject
@end
