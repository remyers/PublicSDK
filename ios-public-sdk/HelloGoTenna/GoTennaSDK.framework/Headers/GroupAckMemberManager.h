//
//  GroupAckMemberManager.h
//  TestingThingsOut
//
//  Created by JOSHUA M MAKINDA on 4/6/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GroupMembershipByte;
@class GroupAckInfo;

@interface GroupAckMemberManager : NSObject

+ (nonnull instancetype)shared;
+ (NSUInteger)maxGroupMembers;

//commands
- (void)addGroupMemberGID:(nonnull NSNumber *)memberGID index:(nonnull NSNumber *)index forGroupGID:(nonnull NSNumber *)groupGID;

//queries
- (BOOL)isGroupAckValidGID:(nonnull NSNumber *)gid;

- (nonnull GroupAckInfo *)groupAckInfoFromResponseData:(nonnull NSData *)responseData groupGID:(nonnull NSNumber *)groupGID;
- (nonnull GroupMembershipByte *)groupMembershipByteForMemberGID:(nonnull NSNumber *)memberGID groupGID:(nonnull NSNumber *)groupGID;

@end
