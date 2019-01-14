#import <Foundation/Foundation.h>

@class GTLatchedErrorInfo;

@interface SystemInfoResponseData : NSObject

@property (nonatomic) NSString *firmwareVersion;
@property (nonatomic) NSNumber *majorRevision;
@property (nonatomic) NSNumber *minorRevision;
@property (nonatomic) NSNumber *buildRevision;
@property (nonatomic) NSNumber *batteryLevel;
@property (nonatomic) NSNumber *paTemp;
@property (nonatomic) NSNumber *siLabsTemp;
@property (nonatomic) NSNumber *reflectedPowerRatio;  // antenna quality
@property (nonatomic) BOOL flashStatus;
@property (nonatomic) BOOL ledStatus;
@property (nonatomic) BOOL isCurrentlyCharging;
@property (nonatomic, strong) NSData *rawData;
@property (nonatomic, strong) NSDate *dateCreated;
@property (nonatomic, copy) NSString *goTennaSerialNumber;
@property (nonatomic, strong) GTLatchedErrorInfo *latchedErrorInfo;

- (NSString *)asString;

@end
