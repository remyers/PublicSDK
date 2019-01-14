//
//  GTMeshGeofence.h
//  GoTenna
//
//  Created by JOSHUA M MAKINDA on 11/14/16.
//  Copyright © 2016 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <GoTennaSDK/GoTennaSDK.h>

/// The mesh geofencing tool
@interface GTMeshGeofence : NSObject

/**
 Last Saved Region ID
 
 Get the last saved region id, default is NORTH_AMERICA
 
 */
+ (RegionID)lastSavedRegionID;

/**
 Last Saved ITU Region ID

 Get the last saved itu region id, default is ITU_2.
 */
+ (RegionID)lastSavedITURegionID;

/**
 Get System Info Medium Priority
 
 @param location    The current location to check the region id of.
 @param regionBlock Called when region id is found or not.
 */
- (void)regionIDForLocation:(CLLocationCoordinate2D)location regionIDResponse:(void(^)(RegionID regionID, BOOL regionFound))regionBlock;

@end
