//
//  GroupAckInfo.h
//  TestingThingsOut
//
//  Created by JOSHUA M MAKINDA on 4/8/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GroupAckInfo : NSObject

- (nonnull instancetype)initWithAckMembers:(nonnull NSDictionary<NSNumber*,NSNumber*>*)ackMembers nackMembers:(nonnull NSDictionary<NSNumber*,NSNumber*>*)nackMembers;

@property (nonatomic, readonly, nonnull) NSDictionary<NSNumber*,NSNumber*> *ackMembers;
@property (nonatomic, readonly, nonnull) NSDictionary<NSNumber*,NSNumber*> *nackMembers;
@property (nonatomic, readonly, nonnull) NSDictionary<NSNumber*,NSNumber*> *allMembers;

+ (nonnull NSDictionary *)parseBooleanIndexedMembersSerialized:(nonnull NSData *)serializedMembersIndexed;
- (nonnull NSData *)serializedBooleanIndexedMembers;

@end
