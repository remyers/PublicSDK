//
//  Group.m
//  HelloGoTenna
//
//  Created by GoTenna on 8/1/17.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import "Group.h"
#import "Contact.h"
#import <GoTennaSDK/UserDataStore.h>

@interface Group ()

@property (nonatomic, strong) NSNumber *groupGID;
@property (nonatomic, strong) NSMutableArray<Contact *> *members;

@end

@implementation Group

//MARK:- Init

- (instancetype)initWithGID:(NSNumber *)gid groupMembers:(NSArray<Contact *> *)groupMembers {
    self = [super init];
    
    if (self) {
        self.groupGID = gid;
        self.members = [NSMutableArray arrayWithArray:groupMembers];
    }
    
    return self;
}

//MARK:- queries

- (NSArray<Contact *> *)groupMembers {
    
    NSMutableArray<Contact*> *tempMembers = [self.members mutableCopy];
    
    // Display all contacts in group except self
    for (Contact *contact in self.members) {
        if ([[UserDataStore shared] isMyGID:contact.gid]) {
            [tempMembers removeObject:contact];
            break;
        }
    }
    
    return [tempMembers copy];
}

@end
