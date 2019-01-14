//
//  ChatViewController.h
//  HelloGoTenna
//
//  Created by GoTenna on 7/26/17.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <UIKit/UIKit.h>
@import GoTennaSDK;
@class Group;

@interface ChatViewController : UIViewController

@property (nonatomic, strong) Group *group;
@property (nonatomic, assign) GTGIDType conversationType;

@end
