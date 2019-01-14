//
//
//  GTCommandValidator.h
//  GoTennaSDKExample
//
//  Created by Julietta Yaunches on 4/1/15.
//  Copyright (c) 2015 gotenna. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GTCommand;

/// Used for validating commands (primarily the send messages)
@interface GTCommandValidator : NSObject

/**
 ### Validate Send Message
 
 This method is used to verify the send message command.
 
 @param command     The command to be validated (as an appropriate send message command)
 @param GID         The GID to be validated
 @param onError     Called when an error occurs (See error code for details)
 */
- (BOOL)validateSendMessageCommand:(GTCommand *)command destinationGID:(NSNumber *)GID onError:(void (^)(NSError *))error;

/**
 ### Validate Broadcast
 
 This method is used to verify the broadcast message command.
 
 @param command     The command to be validated (as an appropriate send message command)
 @param onError     Called when an error occurs (See error code for details)
 */
- (BOOL)validateBroadcastCommand:(GTCommand *)command onError:(void (^)(NSError *))error;

/**
 ### Validate Set GoTenna GID
 
 This method is used to verify the set goTenna GID command.
 
 @param number      The GID to be validated.
 @param onError     Called when an error occurs (See error code for details)
 */
- (BOOL)validateSetGoTennaGID:(NSNumber *)number onError:(void (^)(NSError *))error;

@end
