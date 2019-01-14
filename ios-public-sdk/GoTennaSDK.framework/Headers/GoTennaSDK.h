//
//  GoTennaSDK.h
//  GoTennaSDK
//
//  Created by JOSHUA M MAKINDA on 3/11/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <UIKit/UIKit.h>

#ifdef DEBUG
#   define NSLog(...) NSLog(__VA_ARGS__)
#else
#   define NSLog(...) (void)0
#endif

//! Project version number for GoTennaSDK.
FOUNDATION_EXPORT double GoTennaSDKVersionNumber;

//! Project version string for GoTennaSDK.
FOUNDATION_EXPORT const unsigned char GoTennaSDKVersionString[];

#import <GoTennaSDK/GoTennaSDK.h>

//MARK:- Categories

#import <GoTennaSDK/NSData+ByteOperations.h>
#import <GoTennaSDK/NSDate+GTLogging.h>
#import <GoTennaSDK/NSData+BytesToPrimitiveArray.h>
#import <GoTennaSDK/NSNumber+Utilities.h>
#import <GoTennaSDK/NSString+GTFormatting.h>
#import <GoTennaSDK/NSString+Util.h>
#import <GoTennaSDK/NSDictionary+Parsing.h>
#import <GoTennaSDK/NSData+GTHelper.h>
#import <GoTennaSDK/NSMutableArray+GTHelpers.h>
#import <GoTennaSDK/NSArray+GTHelpers.h>
#import <GoTennaSDK/NSData+ByteOperation.h>
#import <GoTennaSDK/ConvertToString.h>

//MARK:- Protocols

#import <GoTennaSDK/GTMessageDataProtocol.h>
#import <GoTennaSDK/GTFirmwareInstallationProgressProtocol.h>
#import <GoTennaSDK/GTFirmwareInstallationProgressProtocol.h>
#import <GoTennaSDK/GTFirmwareRetrieveProtocol.h>
#import <GoTennaSDK/GTDigestHMACGeneratorProtocol.h>
#import <GoTennaSDK/GTLogExportProtocol.h>
#if SDK_INTERNAL == 1
#import <GoTennaSDK/NRFScanResponseProtocol.h>
#import <GoTennaSDK/NRFProtocol.h>
#endif

//MARK:- MessageData

#import <GoTennaSDK/GTPingTextOnlyMessageData.h>
#import <GoTennaSDK/GTLocationRequestOnlyMessageData.h>
#import <GoTennaSDK/GTLocationMessageData.h>
#import <GoTennaSDK/SystemInfoResponseData.h>
#import <GoTennaSDK/GTTextAndLocationMessageData.h>
#import <GoTennaSDK/GTLocationOnlyMessageData.h>
#import <GoTennaSDK/GTTextAndLocationRequestMessageData.h>
#import <GoTennaSDK/GTTextOnlyMessageData.h>
#import <GoTennaSDK/GTGroupCreationMessageData.h>
#import <GoTennaSDK/GTNetRelayRequestMessageData.h>
#import <GoTennaSDK/GTNetRelaySuccessResponseMessageData.h>
#import <GoTennaSDK/GTFrequencyChannelData.h>
#import <GoTennaSDK/GTFrequencyData.h>
#import <GoTennaSDK/GTPerimeterMessageData.h>
#import <GoTennaSDK/GTRouteMessageData.h>
#import <GoTennaSDK/GTCircleMessageData.h>
#import <GoTennaSDK/GTRectangleMessageData.h>
#import <GoTennaSDK/GTFrequencySlotData.h>
#import <GoTennaSDK/GTMessageData.h>
#import <GoTennaSDK/GTBaseMessageData.h>
#import <GoTennaSDK/GTTextAndFrequencySlotMessageData.h>
#import <GoTennaSDK/GTNetRelayMessageData.h>

//MARK:- Frequency

#import <GoTennaSDK/FrequencySetPowerLevel.h>
#import <GoTennaSDK/GTDataRateMask.h>
#import <GoTennaSDK/GTDataRate.h>
#import <GoTennaSDK/GTMeshGeofence.h>
#import <GoTennaSDK/FrequencyEnumConstants.h>
#import <GoTennaSDK/GTFrequencySync.h>
#import <GoTennaSDK/GTFrequencyValidation.h>
#if SDK_INTERNAL == 1
#import <GoTennaSDK/FrequencySlotManager.h>
#import <GoTennaSDK/GTDeviceAlertResult.h>
#endif

//MARK:- Firmware

#import <GoTennaSDK/GTFirmwareRetrieverFactory.h>
#import <GoTennaSDK/GTFirmwareDownloadTaskManager.h>
#import <GoTennaSDK/GTFirmwareInstallationManager.h>
#import <GoTennaSDK/GTFirmwareVersion.h>

//MARK:- General

#import <GoTennaSDK/GTSendCommand.h>
#import <GoTennaSDK/BluetoothConnectionManager.h>
#import <GoTennaSDK/PublicKeyManager.h>
#import <GoTennaSDK/GTPairingManager.h>
#import <GoTennaSDK/GTEventNotifier.h>
#import <GoTennaSDK/GoTenna.h>
#import <GoTennaSDK/GTCommandValidator.h>
#import <GoTennaSDK/GTSystemInfoStore.h>
#import <GoTennaSDK/GTPairingConnectionState.h>
#import <GoTennaSDK/GTDocumentManager.h>
#import <GoTennaSDK/GroupSecretManager.h>
#import <GoTennaSDK/UserDataStore.h>
#import <GoTennaSDK/GTResettingService.h>
#import <GoTennaSDK/GTGid.h>
#import <GoTennaSDK/GTNotificationCodes.h>
#import <GoTennaSDK/GTPeripheralManager.h>
#import <GoTennaSDK/User.h>
#import <GoTennaSDK/GTSystemInfo.h>
#import <GoTennaSDK/GTError.h>
#import <GoTennaSDK/GTConstants.h>
#import <GoTennaSDK/GTStoreDateTime.h>
#import <GoTennaSDK/GTFileLogger.h>
#import <GoTennaSDK/GTCommunicationLogger.h>
#import <GoTennaSDK/GIDManager.h>
#import <GoTennaSDK/GTSecurityService.h>
#import <GoTennaSDK/GTDataSerializer.h>
#import <GoTennaSDK/GTConfig.h>
#import <GoTennaSDK/GTCommand.h>
#import <GoTennaSDK/GTResponse.h>
#import <GoTennaSDK/GTCommandCenter.h>
#import <GoTennaSDK/GTDataTypes.h>
#import <GoTennaSDK/PostRequestTask.h>
#import <GoTennaSDK/GTShoutEncryptionManager.h>
#import <GoTennaSDK/EncryptionCounterManager.h>
#import <GoTennaSDK/GroupAckInfo.h>
#import <GoTennaSDK/GroupAckMemberManager.h>
#import <GoTennaSDK/GTLoggingConstants.h>
#import <GoTennaSDK/GTMeshAckHandler.h>
#import <GoTennaSDK/GTReachability.h>
#import <GoTennaSDK/GTUserDefaults.h>
#if SDK_INTERNAL == 1
#import <GoTennaSDK/ProConfigurationManager.h>
#import <GoTennaSDK/ProConfigurationData.h>
#import <GoTennaSDK/GTFirmwareData.h>
#import <GoTennaSDK/GTPortalURL.h>
#import <GoTennaSDK/NetworkRelayCredentialsManager.h>
#import <GoTennaSDK/GTCommandCodeConstants.h>
#import <GoTennaSDK/EndianUtils.h>
#import <GoTennaSDK/NetworkRelayCredentials.h>
#import <GoTennaSDK/NetworkRelayRequester.h>
#import <GoTennaSDK/GTAudioData.h>
#import <GoTennaSDK/GTAudioMessageData.h>
#endif
