//
//  ChatCell.h
//  HelloGoTenna
//
//  Created by Edmund Trujillo on 11/1/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ChatCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UILabel *chatMessageLabel;
@property (weak, nonatomic) IBOutlet UILabel *chatKeyLabel;

@end

NS_ASSUME_NONNULL_END
