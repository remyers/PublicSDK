//
//  Group.m
//  HelloGoTenna
//
//  Created by Ryan Cohen on 8/1/17.
//  Copyright © 2017 goTenna. All rights reserved.
//

#import "Group.h"
#import "Contact.h"

@interface Group ()

@property (nonatomic, strong) NSNumber *groupGID;
@property (nonatomic, strong) NSArray<Contact *> *groupMembers;

@end

@implementation Group

# pragma mark - Init

- (instancetype)initWithGID:(NSNumber *)gid groupMembers:(NSArray<Contact *> *)groupMembers {
    self = [super init];
    
    if (self) {
        _groupGID = gid;
        _groupMembers = groupMembers;
        
        if (self.groupMembers) {
            for (Contact *contact in groupMembers) {
                contact.invitationState = GroupInvitationStateSending;
            }
        }
    }
    
    return self;
}

@end
