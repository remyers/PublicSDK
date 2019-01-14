//
//  ContactManager.h
//  HelloGoTenna
//
//  Created by GoTenna on 7/25/17.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
@class Group;
@class Contact;

@interface ContactManager : NSObject

+ (instancetype)sharedManager;

- (Contact *)findContactWithGID:(NSNumber *)gid;

- (NSArray<Group *> *)allGroups;

- (NSArray<Contact *> *)allDemoContacts;
- (NSArray<Contact *> *)allDemoContactsExcludingSelf;
- (void) addToGroups:(Group *)group;

@end
