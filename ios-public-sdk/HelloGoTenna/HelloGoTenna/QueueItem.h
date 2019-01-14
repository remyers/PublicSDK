//
//  QueueItem.h
//  HelloGoTenna
//
//  Created by JOSHUA M MAKINDA on 10/3/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
@class Message;

@interface QueueItem : NSObject

@property (nonatomic, readonly) Message *message;
@property (nonatomic, assign) BOOL isBroadcast;

- (instancetype)initWithMessage:(Message *)message;
@end
