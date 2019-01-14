//
//  Group.h
//  HelloGoTenna
//
//  Created by GoTenna on 8/1/17.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Contact;

@interface Group : NSObject

@property (nonatomic, readonly) NSNumber *groupGID;

- (instancetype)initWithGID:(NSNumber *)gid groupMembers:(NSArray<Contact *> *)groupMembers;
- (NSArray<Contact *>*)groupMembers;

@end
