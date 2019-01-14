#import <Foundation/Foundation.h>
#import "GTDataTypes.h"

@class UserDataStore;

extern NSString const *EMERGENCY_GID;
extern NSString const *SHOUT_GID;

/// Handles GID operations and verifications
@interface GIDManager : NSObject

/// Shout GID value
+ (NSNumber *)shoutGID;

/// Emergency GID value
+ (NSNumber *)emergencyGID;

/**
 ###Type of GID
 
 This method is used to get the `GTGIDType` for the GID.
 
 @param number   GID to verify.
 @return GTGIDType
 */
+ (GTGIDType)gidTypeForGID:(NSNumber *)number;

/**
 ###Type of GID
 
 This method is used to generate a group GID (not recommended to use).
 
 @param date   `NSDate` to use.
 @return NSNumber
 */
- (NSNumber *)groupGIDFromDate:(NSDate *)date;

#if SDK_INTERNAL == 1
- (NSNumber *)personalGIDFromDate:(NSDate *)date;
+ (BOOL)senderIsGoTennaHQ:(NSNumber *)number;
#endif

@end
