# Commercial SDK Software release

## Contents

goTenna-public-sdk.aar - compiled goTenna SDK that can be imported into any android app codebase

gotennasdksample/ - source code for sample application for using the SDK

javadocs/index.html  - start point for viewing the SDK documentation

Requires Android OS 4.3+

## INSTALLATION



To install, you must import the .aar file into your AndroidStudio/Eclipse project.

In AndroidStudio you can do this by going to File > New > Module > Import .JAR/.AAR Package

See GoTennaSDKSample as an example on how to do this.



## CONNECTING/DISCONNECTING



You application pairs with a goTenna over BTLE. Confirm your hardware has BTLE capabilities before beginning.

When you use the goTenna SDK to scan for and connect to a goTenna for the first time, it will connect with the very first goTenna it can find.

A goTenna can be paired when its LED light is flashing on/ off in 1 second intervals. This mode can be activated by power cycling the goTenna.

After the goTenna SDK successfully connects to a goTenna for the first time, it records the goTenna's MAC address. It uses this MAC address to determine which goTenna it should connect to in the future.

This cached MAC address can be cleared via the SDK if you wish to connect with a different goTenna after the initial connection and pairing process.

We recommend that you give users additional UI that allows them to disconnect and unpair with their current goTenna. The goTenna mobile application has accomplished this by including a "Forget This goTenna" button inside the mobile application.

This is helpful for when users wish to pair their mobile application with a different goTenna, or if they pair with the incorrect goTenna during the initial pairing process.



## GIDs



A goTenna ID is the unique identifier that your goTenna will use to identify itself  and others will use to send you messages. Before you can start sending/receiving messages, a goTenna needs to have this value set. The example app can be referenced for this. You need to call GTCommandCenter.getInstance().setGotennaGID(long gid). GIDs are managed completely through GTCommandCenter class. See class documentation and the example app for reference.



## BASICS/FAQs



The goTenna sdk allows an app developer to easily get up and running using a network of goTennas. At its core, you'll be able to:

* Send messages to every other goTenna in range (broadcasting).

* Send messages to another single goTenna.

* Create a group of specific users and message everyone in this group.



Messages may be optionally encrypted using default functionality provided by the SDK.



Message Types

* One-to-one

    * sending a message to one other user only

    * you will receive acknowledgement of receipt

* Broadcast

    * sending a message to all users within ranges

    * this uses the reserved GID '1111111111'

    * on receiving this type of message you can recognize it as a broadcast based on the GID '1111111111'

    * sender does not receive any acknowledgements of receipt by receivers

* Group

    * sending a message to group created with a finite number of members (< 10)

    * see example app for creating a group and being notified of being added to a group

    * sender does not receive any acknowledgements of receipt by receivers

## Battery Level

Battery level can be obtained by calling GTCommandCenter.sendGetSystemInfo(). The SystemInfoResponseData that is returned has a method called getBatteryLevelAsPercentage(). Polling the device on an interval using this command will allow you to get the system info periodically and present it to the user if needed.

## MESH SDK UPDATE NOTES

This update has significant changes that requires existing SDK users to fix package imports and replace class usage. Please view [Android Upgrade Guide](https://gotenna.github.io/PublicSDK/android-public-sdk/goTenna Pro SDK Upgrade Guide Android/) for a detailed upgrade guide.

How do I connect to a goTenna?

Previously, to start the goTenna pairing process, you would call GTConnectionManager.getInstance().scanAndConnect();

Now there is an additional function scanAndConnect(GTDeviceType deviceType), and in this function you can specify GTDeviceType.MESH.

V1 or the original goTenna is now deprecated. The SDK will not allow connection to V1.

## IMPORTANT DETAILS ON OPERATING REGIONS

### Mesh

The goTenna Mesh was created to operate according to FCC Regulations on a per region basis. This means that in order to use the goTenna Mesh properly, you must determine which region you are in and tell the goTenna so that it can use the proper transmit frequencies designated for that region.

Currently supported regions are:

    NORTH_AMERICA,

    EUROPE,

    AUSTRALIA,

    NEW_ZEALAND,

    SINGAPORE.

We have added utils that will help you figure out the GeoRegion. Please visit the sample app for an example. After determining which region you are in, simply call the function GTCommandCenter.getInstance.sendSetGeoRegion(Place.NORTH_AMERICA); This will tell the goTenna mesh which region it is in, and it will alter its transmit frequencies accordingly.
