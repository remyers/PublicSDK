Commercial SDK Software release

Contents
goTenna-public-sdk.aar - compiled goTenna SDK that can be imported into any android app codebase
gotennasdksample/ - source code for sample application for using the SDK
javadocs/index.html  - start point for viewing the SDK documentation


Requires Android OS 4.3+

INSTALLATION
 
To install, you must import the .aar file into your AndroidStudio/Eclipse project.
In AndroidStudio you can do this by going to File > New > Module > Import .JAR/.AAR Package

See GoTennaSDKSample as an example on how to do this.
 
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

MESH SDK UPDATE NOTES

What is going to break by updating to this new SDK?
- The SDK Method User.getGroupGIDs() now returns a List instead of an ArrayList, you will need to update your code to reflect that minor SDK change.
- Firmware Updates will still work, but before you do an update make sure you specify which determine which device you are using Mesh vs. V1, and supply the correct param to GTFirmwareAmazonDownloader.setAmazonFirmwareBucket. If no param is specified, it will default to the V1 goTenna.

How do I connect to a goTenna Mesh vs. V1 goTenna?
- Previously, to start the goTenna pairing proces, you would call GTConnectionManager.getInstance().scanAndConnect();
Now there is an additiona function scanAndConnect(GTDeviceType deviceType), and in this function you can specify GTDeviceType.V1 or GTDeviceType.MESH.
The old function will automatically use V1 by default.

IMPORTANT DETAILS ON OPERATING REGIONS

The goTenna Mesh was created to operate according to FCC Regulations on a per region basis. This means that inorder to use the goTenna Mesh properly, you must determine which region you are in and tell the goTenna so that it can use the proper transmit frequencies designated for that region.

Currently supported regions are: 
    NORTH_AMERICA,
    EUROPE,
    AUSTRALIA,
    NEW_ZEALAND,
    SINGAPORE.

After determining which region you are in, simply call the function GTCommandCenter.getInstance.sendSetGeoRegion(Place.NORTH_AMERICA); This will tell the goTenna mesh which region it is in, and it will alter its transmit frequencies accordingly.
