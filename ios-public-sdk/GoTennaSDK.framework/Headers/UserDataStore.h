//
//  UserDataStore.h
//  GoTenna
//
//  Created by Julietta Yaunches on 4/06/2014.
//  Copyright (c) 2014 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class User;
@class CLLocation;
@class GTSecurityService;

/// Storage class for user related operations and info
@interface UserDataStore : NSObject

/**
 ###Shared instance
 
 Use this for to create access the common instance of this class.
 
 @return Singleton instance
 */
+ (instancetype)shared;

/// Retrieve the current user
- (User *)currentUser;

/**
 ###Register User Name
 
 This method is used to create and save a new `User`, or to simply update a `User`
 
 @param username    The GID to assign to the goTenna.
 @param gid         The name of the user who's GID this is.
 @return `User`
 */
- (User *)registerUserWithName:(NSString *)username andGid:(NSNumber *)gid;

/**
 ###Add multicast
 
 Adds the GID to the multicast register.
 
 @param number    The GID to add to multicast register.
 */
- (void)addMulticastGID:(NSNumber *)number;

/**
 ###Delete multicast
 
 Deletes the GID from multicast register.
 
 @param number    The GID to remove from the multicast register.
 */
- (void)deleteMulticastGID:(NSNumber *)number;

/**
 ###Has multicast GID?
 
 Checks if the GID is associated with multicasting.
 
 @param number    The GID to check if it is a multicast GID.
 @return BOOL
 */
- (BOOL)hasMulticastGID:(NSNumber *)number;

/// Mark onboarding process completed
- (void)markOnboardingProcessCompleted;

/// Delete the current user
- (void)deleteUser;

/**
 ###Add group GID
 
 Adds the group GID.
 
 @param number    The GID to add to the group register.
 */
- (void)addGroupGID:(NSNumber *)number;

/**
 ###Delete group GID
 
 Deletes the group GID.
 
 @param number    The GID to remove from the group register.
 */
- (void)deleteGroupGID:(NSNumber *)number;

/**
 ###Save user
 
 Saves the user as current user.
 
 @param user    The user to be saved.
 */
- (BOOL)saveUser:(User *)user;

/// Checks that the user is logged in.
- (BOOL)userIsLoggedIn;

/**
 ###Is my GID?
 
 Checks if the GID is my own.
 
 @param gid    The GID to check if it is my own.
 @return BOOL
 */
- (BOOL)isMyGID:(NSNumber *)gid;

/// Has valid user stored
- (BOOL)hasValidUser;

#if SDK_INTERNAL == 1
- (BOOL)userHasOnboarded;
- (BOOL)userFinishedOnboardingProcess;
#endif

@end
