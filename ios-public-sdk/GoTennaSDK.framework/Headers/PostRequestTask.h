//
//  PostRequestTask.h
//  Test
//
//  Created by Thomas Colligan on 6/16/16.
//  Copyright © 2016 Thomas Colligan. All rights reserved.
//

#import <Foundation/Foundation.h>

/// A simplified URL Request tool used for performing request tasks
@interface PostRequestTask : NSObject

typedef NS_ENUM(NSInteger, HTTPMethod_Type)
{
    HTTPMethod_GET,
    HTTPMethod_POST,
    HTTPMethod_PUT,
    HTTPMethod_DELETE
};

typedef void (^NetworkCallbackHandler)(NSDictionary* responseDict, NSURLResponse *urlResponse, NSError *error);

/// HTTP constants type
@property (nonatomic, assign) HTTPMethod_Type httpMethodType;

/**
 ###Init with URL timeout
 
 Initialize with a URL and timeout.
 
 @param urlString   The URL string for the request.
 @param timeOut     Time out for the URL request.
 @return instanceType
 */
- (id)initWithUrl:(NSString *)urlString timeOut:(double)timeOut;

/**
 ###Init with URL
 
 Initialize with a URL.
 
 @param urlString   The URL string for the request.
 @return instanceType
 */
- (id)initWithUrl:(NSString *)urlString;

/**
 ###Execute request with post dictionary
 
 Does a post request using the dictionary passed in.
 
 @param postDictionary          The key value pairs that are being posted.
 @param networkCallbackHandler  On response network callback.
 */
- (void)executeWithPostDictionary:(NSDictionary *)postDictionary andCallback:(NetworkCallbackHandler)networkCallbackHandler;

/**
 ###Execute request with headers dictionary
 
 Does a post request used only for headers that are in the dictionary passed in.
 
 @param postHeader              The key value pairs that are being posted.
 @param networkCallbackHandler  On response network callback.
 */
- (void)executeWithPostHeaderOnly:(NSDictionary *)postHeader andCallback:(NetworkCallbackHandler)networkCallbackHandler;

@end
