//
//  AppDelegate.m
//  HelloGoTenna
//
//  Created by GoTenna on 7/20/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import "AppDelegate.h"
#import "MessagingManager.h"

@import GoTennaSDK;

#warning Set application token
NSString * const kGoTennaApplicationToken = nil;

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    // Set application token
    @try {
        [GoTenna setApplicationToken:kGoTennaApplicationToken];
    }
    @catch (NSException *exception) {
        
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"SDK Error" message:@"The goTenna SDK Token is INVALID!  Please rebuild the sample app with a valid token." preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction* ok = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
            [NSException raise:@"Token Invalid" format:@"Invalid SDK token provided"];
        }];
        [alertController addAction:ok];
        
        UIWindow *alertWindow = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
        alertWindow.rootViewController = [[UIViewController alloc] init];
        alertWindow.windowLevel = UIWindowLevelAlert + 1;
        [alertWindow makeKeyAndVisible];
        [alertWindow.rootViewController presentViewController:alertController animated:YES completion:nil];
    }
    
    // Setup messaging handler
    [MessagingManager sharedManager];
    
    return YES;
}

@end
