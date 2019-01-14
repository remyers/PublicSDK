//
//  QueueItem.m
//  HelloGoTenna
//
//  Created by JOSHUA M MAKINDA on 10/3/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import "QueueItem.h"
#import "Message.h"
@import GoTennaSDK;

@interface QueueItem()
@property (nonatomic, strong) Message *message;
@end

@implementation QueueItem

- (instancetype)initWithMessage:(Message *)message {
    self = [super init];
    
    if (self) {
        self.message = message;
        self.isBroadcast = ([message.receiverGID isEqualToNumber:[GIDManager shoutGID]]);
    }
    
    return self;
}

@end
