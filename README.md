# PublicSDK
Public Android and iOS SDK's for the goTenna

First read [goTennaSDKIntro.pdf](goTennaSDKIntro.pdf)

### Contents
- [android-public-sdk](android-public-sdk) - SDK for Android
- [iOS-Public-SDK](ios-public-sdk) - SDK for iOS
- [python-public-sdk](python-public-sdk) - SDK for Python
- [goTenna Android SDK JavaDocs](https://gotenna.github.io/PublicSDK/android-public-sdk/javadocs/)
- [goTenna iOS SDK Docs](https://gotenna.github.io/PublicSDK/ios-public-sdk/GoTennaSDKDocs/html/)

Each subdirectory has a readme.txt file that explains how to install and use the SDK.

#### App Token
goTenna uses an App Token to differentiate between different apps on the network. Apps can only communicate with other apps that use the same App Token. This allows an app to coexist with the goTenna app, but not intermix the messages being received.

Before you can use the sdk, you must setup your application token. This must be done before you use any methods from the SDK. You must set your application token before attempting to pair with a goTenna. See specific platform documentation and the sample apps for details on how to pair.

All developers are required to request a unique App Token from [http://www.gotenna.com/pages/sdk](http://www.gotenna.com/pages/sdk)
