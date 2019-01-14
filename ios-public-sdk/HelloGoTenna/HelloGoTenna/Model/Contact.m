//
//  Contact.m
//  HelloGoTenna
//
//  Created by GoTenna on 7/25/17.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import "Contact.h"

@interface Contact()
@property (nonatomic, copy) NSString *name;
@property (nonatomic, strong) NSNumber *gid;
@end

@implementation Contact

- (instancetype)initWithName:(NSString *)name gid:(NSNumber *)gid {
    self = [super init];
    
    if (self) {
        self.name = name;
        self.gid = gid;
    }
    
    return self;
}

- (NSString *)invitationStateString {
    NSString *state = nil;
    
    switch (self.invitationState) {
        case GroupInvitationStateNone:
            state = @"Awaiting Invite";
            break;
        case GroupInvitationStateSending:
            state = @"Sending...";
            break;
        case GroupInvitationStateReceived:
            state = @"Received";
            break;
        case GroupInvitationStateNotReceived:
            state = @"Not Received";
            break;
    }
    
    return state;
}

@end
