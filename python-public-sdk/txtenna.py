""" txtenna.py - 
Send a Bitcoin transactions using the txTenna json format with the broadcast_tx RAW_HEX TX_HASH NETWORK(m|t)
Receive and confirm a transaction in the txTEnna json format using a remote (or local) txTenna-server. 

This is a modified version of sample.py from the goTenna SDK.

Usage: python txtenna.py SDK_TOKEN GEO_REGION

txTenna> broadcast_tx 01000000000101bf6c3ed233e8700b42c1369993c2078780015bab7067b9751b7f49f799efbffd0000000017160014f25dbf0eab0ba7e3482287ebb41a7f6d361de6efffffffff02204e00000000000017a91439cdb4242013e108337df383b1bf063561eb582687abb93b000000000017a9148b963056eedd4a02c91747ea667fc34548cab0848702483045022100e92ce9b5c91dbf1c976d10b2c5ed70d140318f3bf2123091d9071ada27a4a543022030c289d43298ca4ca9d52a4c85f95786c5e27de5881366d9154f6fe13a717f3701210204b40eff96588033722f487a52d39a345dc91413281b31909a4018efb330ba2600000000 94406beb94761fa728a2cde836ca636ecd3c51cbc0febc87a968cb8522ce7cc1 m

"""
from __future__ import print_function
import cmd # for the command line application
import sys # To quit
import os
import traceback
import logging
import requests
import json
from threading import Thread
from time import sleep
from zmq.utils import z85
import md5
import random
import string
import goTenna # The goTenna API

# For SPI connection only, set SPI_CONNECTION to true with proper SPI settings
SPI_CONNECTION = False
SPI_BUS_NO = 0
SPI_CHIP_NO = 0
SPI_REQUEST = 22
SPI_READY = 27

# Configure the Python logging module to print to stderr. In your application,
# you may want to route the logging elsewhere.
logging.basicConfig()

# Import readline if the system has it
try:
    import readline
    assert readline # silence pyflakes
except ImportError:
    pass

# Import support for bitcoind RPC interface
import bitcoin
import bitcoin.rpc
from bitcoin.core import b2x, b2lx, CMutableTxOut, CMutableTransaction
from bitcoin.wallet import CBitcoinAddress
bitcoin.SelectParams('testnet')


class goTennaCLI(cmd.Cmd):
    """ CLI handler function
    """
    def __init__(self):
        self.api_thread = None
        self.status = {}
        cmd.Cmd.__init__(self)
        self.prompt = 'txTenna>'
        self.in_flight_events = {}
        self._set_frequencies = False
        self._set_tx_power = False
        self._set_bandwidth = False
        self._set_geo_region = False
        self._settings = goTenna.settings.GoTennaSettings(
            rf_settings=goTenna.settings.RFSettings(), 
            geo_settings=goTenna.settings.GeoSettings())
        self._do_encryption = True
        self._awaiting_disconnect_after_fw_update = [False]
        self.messageIdx = 0

    def precmd(self, line):
        if not self.api_thread\
           and not line.startswith('sdk_token')\
           and not line.startswith('quit'):
            print("An SDK token must be entered to begin.")
            return ''
        return line

    def do_sdk_token(self, rst):
        """ Enter an SDK token to begin usage of the driver. Usage: sdk_token TOKEN"""
        if self.api_thread:
            print("To change SDK tokens, restart the sample app.")
            return
        try:
            if not SPI_CONNECTION:
                self.api_thread = goTenna.driver.Driver(sdk_token=rst, gid=None, 
                                                    settings=None, 
                                                    event_callback=self.event_callback)
            else:
                self.api_thread = goTenna.driver.SpiDriver(
                                    SPI_BUS_NO, SPI_CHIP_NO, 22, 27,
                                    rst, None, None, self.event_callback)
            self.api_thread.start()
        except ValueError:
            print("SDK token {} is not valid. Please enter a valid SDK token."
                  .format(rst))

    def emptyline(self):
        pass

    def event_callback(self, evt):
        """ The event callback that will print messages from the API.

        See the documentation for ``goTenna.driver``.

        This will be invoked from the API's thread when events are received.
        """
        if evt.event_type == goTenna.driver.Event.MESSAGE:
            try:
                print(str(evt))
                self.handle_message(evt.message)
            except Exception:
                traceback.print_exc()
        elif evt.event_type == goTenna.driver.Event.DEVICE_PRESENT:
            print(str(evt))
            if self._awaiting_disconnect_after_fw_update[0]:
                print("Device physically connected")
            else:
                print("Device physically connected, configure to continue")
        elif evt.event_type == goTenna.driver.Event.CONNECT:
            if self._awaiting_disconnect_after_fw_update[0]:
                print("Device reconnected! Firmware update complete!")
                self._awaiting_disconnect_after_fw_update[0] = False
            else:
                print("Connected!")
                print(str(evt))
        elif evt.event_type == goTenna.driver.Event.DISCONNECT:
            if self._awaiting_disconnect_after_fw_update[0]:
                # Do not reset configuration so that the device will reconnect on its own
                print("Firmware update: Device disconnected, awaiting reconnect")
            else:
                print("Disconnected! {}".format(evt))
                # We reset the configuration here so that if the user plugs in a different
                # device it is not immediately reconfigured with new and incorrect data
                self.api_thread.set_gid(None)
                self.api_thread.set_rf_settings(None)
                self._set_frequencies = False
                self._set_tx_power = False
                self._set_bandwidth = False
        elif evt.event_type == goTenna.driver.Event.STATUS:
            self.status = evt.status
        elif evt.event_type == goTenna.driver.Event.GROUP_CREATE:
            index = -1
            for idx, member in enumerate(evt.group.members):
                if member.gid_val == self.api_thread.gid.gid_val:
                    index = idx
                    break
            print("Added to group {}: You are member {}"
                  .format(evt.group.gid.gid_val,
                          index))

    def build_callback(self, error_handler=None):
        """ Build a callback for sending to the API thread. May speciy a callable
        error_handler(details) taking the error details from the callback. The handler should return a string.
        """
        def default_error_handler(details):
            """ Easy error handler if no special behavior is needed. Just builds a string with the error.
            """
            if details['code'] in [goTenna.constants.ErrorCodes.TIMEOUT,
                                   goTenna.constants.ErrorCodes.OSERROR,
                                   goTenna.constants.ErrorCodes.EXCEPTION]:
                return "USB connection disrupted"
            return "Error: {}: {}".format(details['code'], details['msg'])
        # Define a second function here so it implicitly captures self
        captured_error_handler = [error_handler]
        def callback(correlation_id, success=None, results=None,
                     error=None, details=None):
            """ The default callback to pass to the API.

            See the documentation for ``goTenna.driver``.

            Does nothing but print whether the method succeeded or failed.
            """
            method = self.in_flight_events.pop(correlation_id.bytes,
                                               'Method call')
            if success:
                if results:
                    print("{} succeeded: {}".format(method, results))
                else:
                    print("{} succeeded!".format(method))
            elif error:
                if not captured_error_handler[0]:
                    captured_error_handler[0] = default_error_handler
                print("{} failed: {}".format(method,
                                             captured_error_handler[0](details)))
        return callback

    def do_set_gid(self, rem):
        """ Create a new profile (if it does not already exist) with default settings.

        Usage: make_profile GID

        GID should be a 15-digit numerical GID.
        """
        if self.api_thread.connected:
            print("Must not be connected when setting GID")
            return
        (gid, _) = self._parse_gid(rem, goTenna.settings.GID.PRIVATE)
        if not gid:
            return
        self.api_thread.set_gid(gid)

    def do_create_group(self, rem):
        """ Create a new group and send invitations to other members.

        Usage create_group GIDs...

        GIDs should be a list of the private GIDs of the other members of the group. The group will be created and stored on the connected goTenna and invitations will be sent to the other members.
        """
        if not self.api_thread.connected:
            print("Must be connected when creating a group")
            return
        gids = [self.api_thread.gid]
        while True:
            (this_gid, rem) = self._parse_gid(rem,
                                              goTenna.settings.GID.PRIVATE,
                                              False)
            if not this_gid:
                break
            gids.append(this_gid)
        if len(gids) < 2:
            print("The group must have at least one other member.")
            return
        group = goTenna.settings.Group.create_new(gids)
        def _invite_callback(correlation_id, member_index,
                             success=None, error=None, details=None):
            if success:
                msg = 'succeeded'
                to_print = ''
            elif error:
                msg = 'failed'
                to_print = ': ' + str(details)
            print("Invitation of {} to {} {}{}".format(gids[member_index],
                                                       group.gid.gid_val,
                                                       msg, to_print))
        def method_callback(correlation_id, success=None, results=None,
                            error=None, details=None):
            """ Custom callback for group creation
            """
            # pylint: disable=unused-argument
            if success:
                print("Group {} created!".format(group.gid.gid_val))
            elif error:
                print("Group {} could not be created: {}: {}"
                      .format(group.gid.gid_val,
                              details['code'], details['msg']))
        print("Creating group {}".format(group.gid.gid_val))
        corr_id = self.api_thread.add_group(group,
                                            method_callback,
                                            True,
                                            _invite_callback)
        self.in_flight_events[corr_id.bytes] = 'Group creation of {}'\
            .format(group.gid.gid_val)

    def do_resend_invite(self, rem):
        """ Resend an invitation to a group to a specific member.

        Usage resend_invite GROUP_GID MEMBER_GID

        The GROUP_GID must be a previously-created group.
        The MEMBER_GID must be a previously-specified member of the group.
        """
        if not self.api_thread.connected:
            print("Must be connected when resending a group invite")
            return
        group_gid, rem = self._parse_gid(rem, goTenna.settings.GID.GROUP)
        member_gid, rem = self._parse_gid(rem, goTenna.settings.GID.PRIVATE)
        if not group_gid or not member_gid:
            print("Must specify group GID and member GID to invite")
            return
        group_to_invite = None
        for group in self.api_thread.groups:
            if group.gid.gid_val == group_gid.gid_val:
                group_to_invite = group
                break
        else:
            print("No group found matching GID {}".format(group_gid.gid_val))
            return
        member_idx = None
        for idx, member in enumerate(group_to_invite.members):
            if member.gid_val == member_gid.gid_val:
                member_idx = idx
                break
        else:
            print("Group {} has no member {}".format(group_gid.gid_val,
                                                     member_gid.gid_val))
            return
        def ack_callback(correlation_id, success):
            if success:
                print("Invitation of {} to {}: delivery confirmed"
                      .format(member_gid.gid_val, group_gid.gid_val))
            else:
                print("Invitation of {} to {}: delivery unconfirmed, recipient may be offline or out of range"
                      .format(member_gid.gid_val, group_gid.gid_val))
        corr_id = self.api_thread.invite_to_group(group_to_invite, member_idx,
                                                  self.build_callback(),
                                                  ack_callback=ack_callback)
        self.in_flight_events[corr_id.bytes] = 'Invitation of {} to {}'\
            .format(group_gid.gid_val, member_gid.gid_val)

    def do_remove_group(self, rem):
        """ Remove a group.

        Usage remove_group GROUP_GID

        GROUP_GID should be a group GID.
        """
        if not self.api_thread.connected:
            print("Must be connected when resending a group invite")
            return
        group_gid, rem = self._parse_gid(rem, goTenna.settings.GID.GROUP)

        if not group_gid:
            print("Must specify group GID to remove it")
            return

        group_to_remove = None
        for group in self.api_thread.groups:
            if group.gid.gid_val == group_gid.gid_val:
                group_to_remove = group
                break
        else:
            print("No group found matching GID {}".format(group_gid.gid_val))
            return

        def method_callback(correlation_id, success=None, results=None,
                            error=None, details=None):
            # logger.debug(" ")
            """ Custom callback for group removal
            """
            # pylint: disable=unused-argument
            if success:
                print("Group {} removed!".format(group_to_remove.gid.gid_val))
            elif error:
                print("Group {} could not be removed: {}: {}"
                      .format(group_gid.gid_val,
                              details['code'], details['msg']))

        corr_id = self.api_thread.remove_group(group, method_callback)
        self.in_flight_events[corr_id.bytes] = 'Group removing of {}' \
            .format(group_gid.gid_val)

    def do_quit(self, arg):
        """ Safely quit.

        Usage: quit
        """
        # pylint: disable=unused-argument
        if self.api_thread:
            self.api_thread.join()
        sys.exit()

    def do_echo(self, rem):
        """ Send an echo command

        Usage: echo
        """
        if not self.api_thread.connected:
            print("No device connected")
        else:
            def error_handler(details):
                """ A special error handler for formatting message failures
                """
                if details['code'] in [goTenna.constants.ErrorCodes.TIMEOUT,
                                       goTenna.constants.ErrorCodes.OSERROR]:
                    return "Echo command may not have been sent: USB connection disrupted"
                return "Error sending echo command: {}".format(details)

            try:
                method_callback = self.build_callback(error_handler)
                corr_id = self.api_thread.echo(method_callback)
            except ValueError:
                print("Echo failed!")
                return
            self.in_flight_events[corr_id.bytes] = 'Echo Send'

    def do_send_broadcast(self, message):
        """ Send a broadcast message

        Usage: send_broadcast MESSAGE
        """
        if not self.api_thread.connected:
            print("No device connected")
        else:
            def error_handler(details):
                """ A special error handler for formatting message failures
                """
                if details['code'] in [goTenna.constants.ErrorCodes.TIMEOUT,
                                       goTenna.constants.ErrorCodes.OSERROR]:
                    return "Message may not have been sent: USB connection disrupted"
                return "Error sending message: {}".format(details)
            try:
                method_callback = self.build_callback(error_handler)
                payload = goTenna.payload.TextPayload(message)
                corr_id = self.api_thread.send_broadcast(payload,
                                                         method_callback)
            except ValueError:
                print("Message too long!")
                return
            self.in_flight_events[corr_id.bytes] = 'Broadcast message: {}'.format(message)

    def do_send_emergency(self, message):
        """ Send an emergency message

        Usage: send_emergency MESSAGE
        """
        if not self.api_thread.connected:
            print("No device connected")
        else:
            def error_handler(details):
                """ A special error handler for formatting message failures
                """
                if details['code'] in [goTenna.constants.ErrorCodes.TIMEOUT,
                                       goTenna.constants.ErrorCodes.OSERROR]:
                    return "Message may not have been sent: USB connection disrupted"
                return "Error sending message: {}".format(details)

            try:
                method_callback = self.build_callback(error_handler)
                payload = goTenna.payload.TextPayload(message)
                corr_id = self.api_thread.send_emergency(payload,
                                                         method_callback)
            except ValueError:
                print("Message too long!")
                return
            self.in_flight_events[corr_id.bytes] = 'Emergency message: {}'.format(message)

    def do_set_emergency_message(self, message):
        """ Set an emergency message. This message will be used when enabling the emergency beacon.

        Usage: set_emergency MESSAGE

        """
        if not self.api_thread.connected:
            print("No device connected")
        else:
            def error_handler(details):
                """ A special error handler for formatting message failures
                """
                if details['code'] in [goTenna.constants.ErrorCodes.TIMEOUT,
                                       goTenna.constants.ErrorCodes.OSERROR]:
                    return "Message may not have been sent: USB connection disrupted"
                return "Error sending message: {}".format(details)

            try:
                method_callback = self.build_callback(error_handler)
                payload = goTenna.payload.TextPayload(message)
                corr_id = self.api_thread.set_emergency_message(payload,
                                                                method_callback)
            except ValueError:
                print("Message too long!")
                return
            self.in_flight_events[corr_id.bytes] = 'Set emergency message: {}'.format(message)

    def do_set_emergency_beacon(self, enabled):
        """ Enable or disable an emergency beacon

        Usage: 
            enable emergency beacon: set_emergency_beacon 1
            disable emergency beacon: set_emergency_beacon 0
        """
        if not self.api_thread.connected:
            print("No device connected")
        else:
            def error_handler(details):
                """ A special error handler for formatting message failures
                """
                if details['code'] in [goTenna.constants.ErrorCodes.TIMEOUT,
                                       goTenna.constants.ErrorCodes.OSERROR]:
                    return "Message may not have been sent: USB connection disrupted"
                return "Error sending message: {}".format(details)

            try:
                method_callback = self.build_callback(error_handler)
                corr_id = self.api_thread.set_emergency_beacon(enabled,
                                                               method_callback)
            except:
                print("Error settting emrgency beacon!")
                return
            self.in_flight_events[corr_id.bytes] = 'Emergency beacon: {}'.format(enabled)

    @staticmethod
    def _parse_gid(line, gid_type, print_message=True):
        parts = line.split(' ')
        remainder = ' '.join(parts[1:])
        gidpart = parts[0]
        try:
            gid = int(gidpart)
            if gid > goTenna.constants.GID_MAX:
                print('{} is not a valid GID. The maximum GID is {}'
                      .format(str(gid), str(goTenna.constants.GID_MAX)))
                return (None, line)
            gidobj = goTenna.settings.GID(gid, gid_type)
            return (gidobj, remainder)
        except ValueError:
            if print_message:
                print('{} is not a valid GID.'.format(line))
            return (None, remainder)

    def do_send_private(self, rem):
        """ Send a private message to a contact

        Usage: send_private GID MESSAGE

        GID is the GID to send the private message to.

        MESSAGE is the message.
        """
        if not self.api_thread.connected:
            print("Must connect first")
            return
        (gid, rest) = self._parse_gid(rem, goTenna.settings.GID.PRIVATE)
        if not gid:
            return
        message = rest
        def error_handler(details):
            """ Special error handler for sending private messages to format errors
            """
            return "Error sending message: {}".format(details)

        try:
            method_callback = self.build_callback(error_handler)
            payload = goTenna.payload.TextPayload(message)
            def ack_callback(correlation_id, success):
                if success:
                    print("Private message to {}: delivery confirmed"
                          .format(gid.gid_val))
                else:
                    print("Private message to {}: delivery not confirmed, recipient may be offline or out of range"
                          .format(gid.gid_val))
            corr_id = self.api_thread.send_private(gid, payload,
                                                   method_callback,
                                                   ack_callback=ack_callback,
                                                   encrypt=self._do_encryption)
        except ValueError:
            print("Message too long!")
            return
        self.in_flight_events[corr_id.bytes]\
            = 'Private message to {}: {}'.format(gid.gid_val, message)

    def do_send_group(self, rem):
        """ Send a message to a group.

        Usage: send_group GROUP_GID MESSAGE

        GROUP_GID is the GID of the group to send the message to. This must have been previously loaded into the API, whether by receiving an invitation, using add_group, or using create_group.
        """
        if not self.api_thread.connected:
            print("Must connect first.")
            return
        (gid, rest) = self._parse_gid(rem, goTenna.settings.GID.GROUP)
        if not gid:
            return
        message = rest
        group = None
        for group in self.api_thread.groups:
            if gid.gid_val == group.gid.gid_val:
                group = group
                break
        else:
            print("Group {} is not known".format(gid.gid_val))
            return
        try:
            payload = goTenna.payload.TextPayload(message)
            corr_id = self.api_thread.send_group(group, payload,
                                                 self.build_callback(),
                                                 encrypt=self._do_encryption)
        except ValueError:
            print("message too long!")
            return
        self.in_flight_events[corr_id.bytes] = 'Group message to {}: {}'\
            .format(group.gid.gid_val, message)

    def get_device_type(self):
        return self.api_thread.device_type

    def do_set_transmit_power(self, rem):
        """ Set the transmit power of the device.

        Usage: set_transmit_power POWER

        POWER should be a string, one of 'HALF_W', 'ONE_W', 'TWO_W' or 'FIVE_W'
        """
        if self.get_device_type() == "900":
             print("This configuration cannot be done for Mesh devices.")
             return
        ok_args = [attr
                   for attr in dir(goTenna.constants.POWERLEVELS)
                   if attr.endswith('W')]
        if rem.strip() not in ok_args:
            print("Invalid power setting {}".format(rem))
            return
        power = getattr(goTenna.constants.POWERLEVELS, rem.strip())
        self._set_tx_power = True
        self._settings.rf_settings.power_enum = power
        self._maybe_update_rf_settings()

    def do_list_bandwidth(self, rem):
        """ List the available bandwidth.

        Usage: list_bandwidth
        """
        print("Allowed bandwidth in kHz: {}"
                .format(str(goTenna.constants.BANDWIDTH_KHZ[0].allowed_bandwidth)))

    def do_set_bandwidth(self, rem):
        """ Set the bandwidth for the device.

        Usage: set_bandwidth BANDWIDTH

        BANDWIDTH should be a bandwidth in kHz.

        Allowed bandwidth can be displayed with list_bandwidth.
        """
        if self.get_device_type() == "900":
            print("This configuration cannot be done for Mesh devices.")
            return
        bw_val = float(rem.strip())
        for bw in goTenna.constants.BANDWIDTH_KHZ:
            if bw.bandwidth == bw_val:
                bandwidth = bw
                break
        else:
            print("{} is not a valid bandwidth".format(bw_val))
            return
        self._settings.rf_settings.bandwidth = bandwidth
        self._set_bandwidth = True
        self._maybe_update_rf_settings()

    def _maybe_update_rf_settings(self):
        if self._set_tx_power\
           and self._set_frequencies\
           and self._set_bandwidth:
            self.api_thread.set_rf_settings(self._settings.rf_settings)

    def do_set_frequencies(self, rem):
        """ Configure the frequencies the device will use.

        Usage: set_frequencies CONTROL_FREQ DATA_FREQS....

        All arguments should be frequencies in Hz. The first argument will be used as the control frequency. Subsequent arguments will be data frequencies.
        """
        freqs = rem.split(' ')
        if len(freqs) < 2:
            print("At least one control frequency and one data frequency are required")
            return
        def _check_bands(freq):
            bad = True
            for band in goTenna.constants.BANDS:
                if freq >= band[0] and freq <= band[1]:
                    bad = False
            return bad

        if self.get_device_type() == "900":
            print("This configuration cannot be done for Mesh devices.")
            return
        try:
            control_freq = int(freqs[0])
        except ValueError:
            print("Bad control freq {}".format(freqs[0]))
            return
        if _check_bands(control_freq):
            print("Control freq out of range")
            return
        data_freqs = []
        for idx, freq in enumerate(freqs[1:]):
            try:
                converted_freq = int(freq)
            except ValueError:
                print("Data frequency {}: {} is bad".format(idx, freq))
                return
            if _check_bands(converted_freq):
                print("Data frequency {}: {} is out of range".format(idx, freq))
                return
            data_freqs.append(converted_freq)
        self._settings.rf_settings.control_freqs = [control_freq]
        self._settings.rf_settings.data_freqs = data_freqs
        self._set_frequencies = True
        self._maybe_update_rf_settings()

    def do_list_geo_region(self, rem):
        """ List the available region.

        Usage: list_geo_region
        """
        print("Allowed region:")
        for region in goTenna.constants.GEO_REGION.DICT:
            print("region {} : {}"
                  .format(region, goTenna.constants.GEO_REGION.DICT[region]))

    def do_set_geo_region(self, rem):
        """ Configure the frequencies the device will use.

        Usage: set_geo_region REGION

        Allowed region displayed with list_geo_region.
        """
        if self.get_device_type() == "pro":
            print("This configuration cannot be done for Pro devices.")
            return
        region = int(rem.strip())
        print('region={}'.format(region))
        if not goTenna.constants.GEO_REGION.valid(region):
            print("Invalid region setting {}".format(rem))
            return
        self._set_geo_region = True
        self._settings.geo_settings.region = region
        self.api_thread.set_geo_settings(self._settings.geo_settings)

    def do_can_connect(self, rem):
        """ Return whether a goTenna can connect. For a goTenna to connect, a GID and RF settings must be configured.
        """
        # pylint: disable=unused-argument
        if self.api_thread.gid:
            print("GID: OK")
        else:
            print("GID: Not Set")
        if self._set_tx_power:
            print("PRO - TX Power: OK")
        else:
            print("PRO - TX Power: Not Set")
        if self._set_frequencies:
            print("PRO - Frequencies: OK")
        else:
            print("PRO - Frequencies: Not Set")
        if self._set_bandwidth:
            print("PRO - Bandwidth: OK")
        else:
            print("PRO - Bandwidth: Not Set")
        if self._set_geo_region:
            print("MESH - Geo region: OK")
        else:
            print("MESH - Geo region: Not Set")


    def do_list_groups(self, arg):
        """ List the known groups """
        if not self.api_thread:
            print("The SDK must be configured first.")
            return
        if not self.api_thread.groups:
            print("No known groups.")
            return
        for group in self.api_thread.groups:
            print("Group GID {}: Other members {}"
                  .format(group.gid.gid_val,
                          ', '.join([str(m.gid_val)
                                     for m in group.members
                                     if m != self.api_thread.gid])))

    @staticmethod
    def _version_from_path(path):
        name = os.path.basename(path)
        parts = name.split('.')
        if len(parts) < 3:
            return None
        return (int(parts[0]),
                int(parts[1]),
                int(parts[2]))

    @staticmethod
    def _parse_version(args):
        version_part = args.split('.')
        if len(version_part) < 3:
            return None, args
        return (int(version_part[0]),
                int(version_part[1]),
                int(version_part[2])),\
                '.'.join(version_part[3:])

    @staticmethod
    def _parse_file(args):
        remainder = ''
        if '"' in args:
            parts = args.split('"')
            firmware_file = parts[1]
            remainder = '"'.join(parts[2:])
        else:
            parts = args.split(' ')
            firmware_file = parts[0]
            remainder = ' '.join(parts[1:])
        if not os.path.exists(firmware_file):
            return None, args
        return firmware_file, remainder

    def do_firmware_update(self, args):
        """ Update the device firmware.

        Usage: firmware_update FIRMWARE_FILE [VERSION]
        FIRMWARE_FILE should be the path to a binary firmware. Files or paths containing spaces should be specified in quotes.
        VERSION is an optional dotted version string. The first three dotted segments will determine the version stored in the firmware. If this argument is not passed, the command will try to deduce the version from the filename. If this deduction fails, the command aborts.
        """
        if not self.api_thread.connected:
            print("Device must be connected.")
            return
        firmware_file, rem = self._parse_file(args)
        if not firmware_file:
            print("Cannot find file {}".format(args))
            return
        try:
            version = self._version_from_path(firmware_file)
        except ValueError:
            version = None
        if not version:
            try:
                version, _ = self._parse_version(rem)
            except ValueError:
                print("Version must be 3 numbers separated by '.'")
                return
            if not version:
                print("Version must be specified when not in the filename")
                return
        try:
            open(firmware_file, 'rb').close()
        except (IOError, OSError) as caught_exc:
            print("Cannot open file {}: {}: {}"
                  .format(firmware_file, caught_exc.errno, caught_exc.strerror))
            return
        else:
            print("File {} OK".format(firmware_file))
            print("Beginning firmware update")

        def _callback(correlation_id,
                      success=None, error=None, details=None, results=None):
            # pylint: disable=unused-argument
            if success:
                print("Firmware updated!")
            elif error:
                print("Error updating firmware: {}: {}"
                      .format(details.get('code', 'unknown'),
                              details.get('msg', 'unknown')))
            self.prompt = "txTenna>"

        last_progress = [0]
        print("")
        def _progress_callback(progress, **kwargs):
            percentage = int(progress*100)
            if percentage/10 != last_progress[0]/10:
                last_progress[0] = percentage
                print("FW Update Progress: {: 3}%.".format(percentage))
                if last_progress[0] >= 90:
                    self._awaiting_disconnect_after_fw_update[0] = True
                if last_progress[0] >= 100:
                    print("Device will disconnect and reconnect when update complete.")

        self.prompt = "(updating firmware)"
        self.api_thread.update_firmware(firmware_file, _callback,
                                        _progress_callback, version)

    def do_get_system_info(self, args):
        """ Get system information.

        Usage: get_system_info
        """
        if not self.api_thread.connected:
            print("Device must be connected")
        print(self.api_thread.system_info)

    def confirm_bitcoin_tx(self, hash, sender_gid):
        """ handle an incoming message

        Usage: confirm_bitcoin_tx json gid
        """
        url = "http://127.0.0.1:8091/tx" + hash ## local txtenna-server
        ##url = "https://api.samourai.io/v2/tx/" + hash ## default txtenna-server
        
        try:
            r = requests.get(url)
            print(r.text)

            while r.status_code != 200:
                sleep(60) # sleep for a minute
                r = requests.get(url)

            ## send zero-conf message back to tx sender
            rObj = json.dumps({'b': 0, 'h': hash})
            print(str(rObj))
            arg = str(sender_gid) + ' ' + str(rObj)
            self.do_send_private(arg)                

            r_text = "".join(r.text.split()) # remove whitespace
            obj = json.loads(r_text)
            while not 'block' in obj.keys():
                sleep(60) # sleep for a minute
                r = requests.get(url)
                r_text = "".join(r.text.split())
                obj = json.loads(r_text)

            ## send block height message back to tx sender
            bObj = obj['block']
            rObj = json.dumps({'b': bObj['height'], 'h': hash})
            print(str(rObj))
            arg = str(sender_gid) + ' ' + str(rObj)
            self.do_send_private(arg)
        except:
            traceback.print_exc()

    def handle_message(self, message):
        """ handle an incoming message

        Usage: handle_message
        """
        payload = str(message.payload.message)
        print("received transaction payload: " + payload)

        obj = json.loads(payload)
        if 'b' in obj.keys() :
            ## process incoming transaction confirmation from another server
            if (obj['b'] > 0) :
                print("Transaction " + obj['h'] + " confirmed in block " + str(obj['b']))
            else :
                print("Transaction " + obj['h'] + " added to the the mem pool")

        else :
            ## process incoming segment
            headers = {u'content-type': u'application/json'}
            url = "http://127.0.0.1:8091/segments" ## local txtenna-server
            ## url = "https://api.samouraiwallet.com/v2/txtenna/segments" ## default txtenna-server
            r = requests.post(url, headers= headers, data=payload)
            print(r.text)

            if 'i' in obj.keys() and not 'c' in obj.keys() :
                print(obj['h'])
                sender_gid = message.sender.gid_val

                ## check for confirmed transaction in a new thread
                ## self.confirm_bitcoin_tx(obj['h'], sender_gid)
                t = Thread(target=self.confirm_bitcoin_tx, args=(obj['h'], sender_gid,))
                t.start()

    def do_broadcast_tx(self, rem):

        (strHexTx, strHexTxHash, network) = rem.split(" ")
        messages = self.tx_to_json(strHexTx, strHexTxHash, str(self.messageIdx), network, False)
        for msg in messages :
            _msg = "".join(msg.split()) ## strip whitespace
            self.do_send_broadcast(_msg)
            sleep(10)
        self.messageIdx = (self.messageIdx+1) % 9999

    def tx_to_json(self, strHexTx, strHexTxHash, messageIdx=0, network='m', isZ85=False):
        ##
        ## if Z85 encoding, use 24 extra characters for tx in segment0. Hash encoded on 40 characters instead of 64
        ##
        ## translated to python from txTenna app PayloadFactory.java : toJSON method
        ##
        ## JSON Parameters
        ##    * **s** - `integer` - Number of segments for the transaction. Only used in the first segment for a given transaction.
        ##    * **h** - `string` - Hash of the transaction. Only used in the first segment for a given transaction. May be Z85-encoded.
        ##    * **n** - `char` (optional) - Network to use. 't' for TestNet3, otherwise assume MainNet. Only used in the first segment for a given transaction.
        ##    * **i** - `string` - TxTenna unid identifying the transaction (8 bytes).
        ##    * **c** - `integer` - Sequence number for this segment. May be omitted in first segment for a given transaction (assumed to be 0).
        ##    * **t** - `string` - Hex transaction data for this segment. May be Z85-encoded.
        ##    * **b** - `integer` - Block height of corresponding transaction hash. Will be 0 for mempool transactions.

        segment0Len = 100  ## 110?
        segment1Len = 180  ## 190?

        tx_network = network

        if isZ85 : 
            segment0Len += 24

        print("tx_to_json, hex tx:" + strHexTx)

        strRaw = strHexTx
        if isZ85 :
            strRaw = z85.encode(strHexTx)
            print("tx_to_json, hex tx Z85:" + strRaw)

        seg_count = 0
        if len(strRaw) <= segment0Len :
            seg_count = 1
        else :
            length = len(strRaw)
            length -= segment0Len
            seg_count = 1
            seg_count += (length / segment1Len)
            if length % segment1Len > 0 :
                seg_count += 1

        tx_id = messageIdx

        # a unique identifier for set of segments from a particular node
        _id = str(self.api_thread.gid.gid_val) + "|" + str(messageIdx)

        try :
            buf = _id.decode("UTF-8")
            md5_hash = md5.new(buf).digest()
            idBytes = md5_hash[:8] ## first 8 bytes of md5 digest
            if isZ85 :
                tx_id = z85.encode(idBytes.encode("hex"))
            else :
                tx_id = idBytes.encode("hex")
        except Exception: # pylint: disable=broad-except
            traceback.print_exc()

        ret = []
        for seg_num in range(0, seg_count) :

            ## Gson gson = new GsonBuilder().disableHtmlEscaping().create();

            if seg_num == 0 :
                if isZ85 :
                    tx_hash = z85.encode(strHexTxHash.decode("hex"))
                else :
                    tx_hash = strHexTxHash

                seg_len = len(strRaw)
                tx_seg = strRaw
                if len(strRaw) > segment0Len :
                    seg_len = segment0Len
                    tx_seg = strRaw[:seg_len]
                    strRaw = strRaw[seg_len:]
                
                rObj = json.dumps({'s': seg_count,'i': tx_id,'n': tx_network,'h': tx_hash,'t': tx_seg})
                ret.append(rObj)

            else :
                seg_len = len(strRaw)
                tx_seg = strRaw
                if len(strRaw) > segment1Len :
                    seg_len = segment1Len
                    tx_seg = strRaw[:seg_len]
                    strRaw = strRaw[seg_len:]

                rObj = json.dumps({'c': seg_num,'i': tx_id,'t': tx_seg})
                ret.append(rObj)

        return ret

    def do_getbalance(self, rem) :
        try :
            proxy = bitcoin.rpc.Proxy()
            balance = proxy.getbalance()
            print("getbalance: " + str(balance))
        except Exception: # pylint: disable=broad-except
            traceback.print_exc()

    def do_getrawtransaction(self, txid) :
        try :
            proxy = bitcoin.rpc.Proxy()
            r = proxy.getrawtransaction(txid)
            print("getrawtransaction(: " + str(r))
        except Exception: # pylint: disable=broad-except
            traceback.print_exc()        

    def do_sendrawtransaction(self, hex) :
        try :
            proxy = bitcoin.rpc.Proxy()
            r = proxy.sendrawtransaction(hex)
            print("sendrawtransaction: " + str(r))
        except Exception: # pylint: disable=broad-except
            traceback.print_exc()

    def do_sendtoaddress(self, rem) :
        try:
            proxy = bitcoin.rpc.Proxy()
            (addr, amount) = rem.split()
            r = proxy.sendtoaddress(addr, amount)
            print("sendtoaddress, transaction id: " + str(r["hex"]))
        except Exception: # pylint: disable=broad-except
            traceback.print_exc() 

    def do_sendtoaddress_mesh(self, rem) :
        try:
            proxy = bitcoin.rpc.Proxy()
            (addr, sats) = rem.split()

            # Create the txout. This time we create the scriptPubKey from a Bitcoin
            # address.
            txout = CMutableTxOut(sats, CBitcoinAddress(addr).to_scriptPubKey())

            # Create the unsigned transaction.
            unfunded_transaction = CMutableTransaction([], [txout])
            funded_transaction = proxy.fundrawtransaction(unfunded_transaction)
            signed_transaction = proxy.signrawtransaction(funded_transaction["tx"])
            txhex = b2x(signed_transaction["tx"].serialize())
            txid = b2lx(signed_transaction["tx"].GetTxid())
            print("sendtoaddress_mesh (tx, txid): " + txhex + ", " + txid)

            # broadcast over mesh
            self.do_broadcast_tx( txhex + " " + txid + " t")

        except Exception: # pylint: disable=broad-except
            traceback.print_exc()

        try :
            # lock UTXOs used to fund the tx if broadcast successful
            vin_outpoints = set()
            for txin in funded_transaction["tx"].vin:
                vin_outpoints.add(txin.prevout)
            ## json_outpoints = [{'txid':b2lx(outpoint.hash), 'vout':outpoint.n}
            ##              for outpoint in vin_outpoints]
            ## print(str(json_outpoints))
            proxy.lockunspent(False, vin_outpoints)
            
        except Exception: # pylint: disable=broad-except
            ## TODO: figure out why this is happening
            print("RPC timeout after calling lockunspent")

def run_cli():
    """ The main function of the sample app.

    Instantiates a CLI object and runs it.
    """
    cli_obj = goTennaCLI()

    import argparse
    import six
    import code
    parser = argparse.ArgumentParser('Run a txTenna transaction gateway')
    parser.add_argument('SDK_TOKEN', type=six.b,
                        help='The token for the goTenna SDK')
    parser.add_argument('GEO_REGION', type=six.b,
                        help='The geo region number you are in')
    args = parser.parse_args()  

    cli_obj.do_sdk_token(args.SDK_TOKEN)
    _gid = ''.join(random.SystemRandom().choice(string.digits) for _ in range(12))
    cli_obj.do_set_gid(_gid)
    cli_obj.do_set_geo_region(args.GEO_REGION)

    ## broadcast_tx 01000000000101bf6c3ed233e8700b42c1369993c2078780015bab7067b9751b7f49f799efbffd0000000017160014f25dbf0eab0ba7e3482287ebb41a7f6d361de6efffffffff02204e00000000000017a91439cdb4242013e108337df383b1bf063561eb582687abb93b000000000017a9148b963056eedd4a02c91747ea667fc34548cab0848702483045022100e92ce9b5c91dbf1c976d10b2c5ed70d140318f3bf2123091d9071ada27a4a543022030c289d43298ca4ca9d52a4c85f95786c5e27de5881366d9154f6fe13a717f3701210204b40eff96588033722f487a52d39a345dc91413281b31909a4018efb330ba2600000000 94406beb94761fa728a2cde836ca636ecd3c51cbc0febc87a968cb8522ce7cc1 0 m

    try:
        cli_obj.cmdloop("Welcome to the goTenna API sample! "
                        "Press ? for a command list.\n"
                        "You must begin by entering an SDK token with the "
                        "sdk_token command.")
    except Exception: # pylint: disable=broad-except
        traceback.print_exc()
        cli_obj.do_quit('')

if __name__ == '__main__':
    run_cli()
