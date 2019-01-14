//
//  GTFirmwareRetrieveProtocol.h
//  goTenna SDK
//

#import <Foundation/Foundation.h>

typedef void (^FileCheckCompletion)(NSString *);
typedef void (^RetrievalCompletion)(NSError *);

@protocol GTFirmwareRetrieveProtocol <NSObject>

- (void)checkAvailableFirmwareFile:(FileCheckCompletion)fileCheckCompletion;
- (void)retrieveFirmwareWithStorageCompletion:(RetrievalCompletion)retrievalCompletion;

@end
