//
//  GTPortalURL.h
//  GoTennaSDK
//
//  Created by Edmund Trujillo on 8/7/18.
//  Copyright © 2018 goTenna. All rights reserved.
//
#import <Foundation/Foundation.h>

@interface GTPortalURL : NSObject
+ (NSString *)basePortalURL;
+ (void)setBasePortalURL:(NSString *)basePortalURL;
+ (void)clearBasePortalURL;
@end
