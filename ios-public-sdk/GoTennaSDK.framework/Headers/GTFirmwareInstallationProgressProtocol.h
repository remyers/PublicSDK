#import <Foundation/Foundation.h>

typedef enum : NSUInteger {
    GTFirmwareWriterFailureStateNone,
    GTFirmwareWriterFailureStateShowRetry,
    GTFirmwareWriterFailureStateSomethingWrong,
    GTFirmwareWriterFailureStateNotConnected,
    GTFirmwareWriterFailureStateUserCancelled
} GTFirmwareWriterFailureState;

@protocol GTFirmwareInstallationProgressProtocol <NSObject>
- (void)initializeComplete;
- (void)finalizeComplete;
- (void)newProgressAmount:(float)progress;
- (void)updateComplete:(NSString *)firmwareVersion;
- (void)updateFailed:(GTFirmwareWriterFailureState)failState version:(NSString *)firmwareVersion;
- (void)updateInitialized;

@optional
- (void)dfuUpdateProcessing;
- (void)dfuUpdateComplete;
- (void)dfuUpdateError;
@end
