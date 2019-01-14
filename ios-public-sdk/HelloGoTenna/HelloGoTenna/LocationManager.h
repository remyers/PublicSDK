//
//  LocationManager.h
//  HelloGoTenna
//
//  Created by JOSHUA M MAKINDA on 10/4/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
@class CLLocation;

typedef void(^RetrieveLocationBlock)(CLLocation*);

@interface LocationManager : NSObject

- (void)retrieveMyLocation:(RetrieveLocationBlock)block;
@end
