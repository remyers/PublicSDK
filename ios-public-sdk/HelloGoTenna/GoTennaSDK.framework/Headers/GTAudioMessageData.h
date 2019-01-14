//
//  GTAudioMessageData.h
//  GoTennaSDK
//
//  Created by Edmund Trujillo on 10/26/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import "GTMessageDataProtocol.h"
#import "GTBaseMessageData.h"

@interface GTAudioMessageData : GTBaseMessageData <GTMessageDataProtocol>
- (instancetype)initWithAudioData:(GTAudioData *)audioData;
@end

