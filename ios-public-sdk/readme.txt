Public SDK Software release

Contents
- commercialdemoproject/ - source code for sample application for using the SDK
- GoTennaSDK.framework - compiled goTenna SDK that can be imported into any iOS app codebase.
- GoTennaSDKDocs/html/index.html  - start point for viewing the SDK documentation

Requires iOS 8.4+

KNOWN ISSUES
This is a beta release, your feedback matters! We expect to make updates based on feedback before the SDK is released to the public.

1. We plan to add a notification that there is a firmware update available for the goTenna. The feature already exists to perform the firmware update, but the additional feature will notify when its available and if its a critical update. 

INSTALLATION OF iOS SDK
 
To install, you must import the .framework file into your Xcode project.
You can do this by dragging the .framework file into General tab of your target, drag it into the ‘Embedded Binaries’ section so it appears in both ‘Embedded Binaries’ and ‘Linked Frameworks and Libraries’.
You must also make sure Enable Bitcode in the build settings is set to NO. The .framework should warn you if you forget to do this.
This can only be run for a device, not for a simulator.

See CommercialDemoProject for an example of this.
 
CONNECTING/DISCONNECTING
 
You application pairs with a goTenna over BTLE. Confirm your hardware has BTLE capabilities before beginning.
 
GIDs
 
A goTenna ID is the unique identifier that your goTenna will use to identify itself  and others will use to send you messages. Before you can start sending/receiving messages, a goTenna needs to have this value set. The example app can be referenced for this. You need to call GTCommandCenter.getInstance().setGotennaGID(long gid). GIDs are managed completely through CommandCenter class. See class documentation and the example app for reference.
 
BASICS/FAQs
 
The goTenna sdk allows an app developer to easily get up and running using a network of goTennas. At it's core, you'll be able to:
- Send messages to every other goTenna in range (broadcasting).
- Send messagea to another single goTenna.
- Create a group of specific users and message everyone in this group.
 
Messages may be optionally encrypted using default functionality provided by the SDK.
 
MESSAGES
- Outgoing messages are limited in size to 236 bytes
- There is currently a limit of sending only 5 messages per minute. This is to prevent developers from flooding the radio channels with their own app's content, potnetially blocking other apps from communicating.
 
Message Types
 * One-to-one
    - sending a message to one other user only
    - you will receive acknowledgement of receipt
 * Broadcast
    - sending a message to all users within ranges
    - this uses the reserved GID '1111111111'
    - on receiving this type of message you can recognize it as a broadcast based on the GID '1111111111'
    - sender does not receive any acknowledgements of receipt by receivers
 * Group
    - sending a message to group created with a finite number of members (< 10)
    - see example app for creating a group and being notified of being added to a group
    - sender does not receive any acknowledgements of receipt by receivers
