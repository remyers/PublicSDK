//
//  GTFirmwareRetrieverFactory.h
//  goTenna SDK
//

#import <Foundation/Foundation.h>
#import "GTFirmwareRetrieveProtocol.h"

/// Use this to retreive the firmware object/s.
@interface GTFirmwareRetrieverFactory : NSObject

/**
 ###Retrieve Amazon Firmware Object
 
 Create instance of firmware retriever using Amazon Web Services
 
 @return Object that conforms to the GTFirmwareRetrieveProtocol
*/
+ (id<GTFirmwareRetrieveProtocol>)firmwareRetrieverAmazon;

@end
