//
//  LocationManager.m
//  HelloGoTenna
//
//  Created by JOSHUA M MAKINDA on 10/4/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import "LocationManager.h"
@import CoreLocation;

@interface LocationManager() <CLLocationManagerDelegate>
@property (nonatomic, strong) CLLocationManager *locationManager;
@property (nonatomic) BOOL retrieving;
@property (nonatomic, strong) RetrieveLocationBlock retrieveLocationBlock;
@end

@implementation LocationManager

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.locationManager = [[CLLocationManager alloc] init];
        self.locationManager.delegate = self;
        self.retrieving = NO;
    }
    return self;
}

- (void)retrieveMyLocation:(RetrieveLocationBlock)block {
    [self stopRetrieving];
    [self startRetrieving];
    
    if (block) {
        self.retrieveLocationBlock = block;
    }
}

//MARK:- CLLocationManagerDelegate

- (CLAuthorizationStatus)authStatus {
    return [CLLocationManager authorizationStatus];
}

- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status {
    if (status == kCLAuthorizationStatusAuthorizedWhenInUse || status == kCLAuthorizationStatusAuthorizedAlways) {
        [self.locationManager startUpdatingLocation];
    }
}

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations {
    [self stopRetrieving];
    
    if (self.retrieveLocationBlock) {
        self.retrieveLocationBlock([locations lastObject]);
    }
}

//MARK:- location functions

- (BOOL)locationEnabled {
    return [CLLocationManager locationServicesEnabled] && [CLLocationManager authorizationStatus] == kCLAuthorizationStatusAuthorizedWhenInUse;
}

- (void)startRetrieving {
    if (!self.retrieving) {
        __weak typeof(self) weakSelf = self;
        
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            if ([weakSelf locationEnabled]) {
                [weakSelf.locationManager startUpdatingLocation];
            } else {
                if ([weakSelf.locationManager respondsToSelector:@selector(requestWhenInUseAuthorization)]) {
                    [weakSelf.locationManager requestWhenInUseAuthorization];
                }
            }
        }];
        self.retrieving = YES;
    }
}

- (void)stopRetrieving {
    [self.locationManager stopUpdatingLocation];
    self.retrieving = NO;
}

@end
