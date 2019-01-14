//
//  GTAudioData.h
//  GoTennaSDK
//
//  Created by Edmund Trujillo on 10/26/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTMessageDataProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface GTAudioData : NSObject <GTMessageDataProtocol>

@property(nonatomic, readonly) NSData *melpData;

- (instancetype)initWithMelpData:(NSData *)melpData;

@end

NS_ASSUME_NONNULL_END
