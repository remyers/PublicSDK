//
//  User.h
//  GoTenna
//
//  Created by Julietta Yaunches on 25/06/2014.
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLLocation;
@class GoTennaKeyPair;

/// User class that holds user data and important user info
@interface User : NSObject <NSCoding>

/// Gid value
@property (nonatomic, retain) NSNumber *gId;
/// User id
@property (nonatomic, retain) NSNumber *userId;
/// User name
@property (nonatomic, retain) NSString *name;
/// User email
@property (nonatomic, retain) NSString *email;
/// User last location time
@property (nonatomic, readonly) NSDate *lastLocationTime;
/// User last time connected
@property (nonatomic, strong) NSDate *lastConnectedTime;
/// User last connection started time
@property (nonatomic, strong) NSDate *lastConnectionStartedTime;

/**
 ###User initialization
 
 Initializes the user.
 
 @param username    The name to be associated with this `User`.
 @param gid         The GID to be associated with this `User`.
 @return `instancetype`
 */
+ (instancetype)initWithUsername:(NSString *)username andGid:(NSNumber *)gId;

/// User's last location
- (CLLocation *)lastLocation;
/// User's initials
- (NSString *)initials;

/**
 ###Delete group GID
 
 Removes GID from the group GID registry
 
 @param number  The GID to be removed from the group registry.
 */
- (void)deleteGroupGID:(NSNumber *)number;

/**
 ###Set last location
 
 Sets the last location for the `User`
 
 @param lastLocation    The last location to set on the `User`.
 */
- (void)setLastLocation:(CLLocation *)lastLocation;

/**
 ###Add group GID
 
 Adds GID to group GID registry
 
 @param gid     The GID to add to the group registry.
 */
- (void)addGroupGID:(NSNumber *)number;

/**
 ###Has group GID?
 
 Queries whether this GID is a group GID
 
 @param gid     The GID to check if in the group registry.
 @return BOOL
 */
- (BOOL)hasGroupGID:(NSNumber *)number;

/**
 ###Add multicast GID
 
 Adds GID to multicast GID registry
 
 @param gid     The GID to add to the multicast registry.
 */
- (void)addMulticastGID:(NSNumber *)number;

/**
 ###Delete multicast GID
 
 Removes GID from the multicast GID registry
 
 @param number  The GID to be removed from the multicast registry.
 */
- (void)deleteMulticastGID:(NSNumber *)number;

/**
 ###Has multicast GID?
 
 Queries whether this GID is a multicast GID
 
 @param gid     The GID to check if in the multicast registry.
 @return BOOL
 */
- (BOOL)hasMulticastGroupGID:(NSNumber *)number;

/// Retrieves all group GIDs
- (NSArray<NSNumber*>*)allGroupGIDs;
/// Retrieves all multicast GIDs
- (NSArray<NSNumber *> *)allMulticastGIDs;

#if SDK_INTERNAL == 1
- (BOOL)hasEmail;
- (BOOL)hasVerifiedGID;
#endif

@end
