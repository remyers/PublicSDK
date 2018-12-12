package com.gotenna.sdk.sample.scan;

import android.location.Location;
import android.support.annotation.NonNull;

import com.gotenna.sdk.GoTenna;
import com.gotenna.sdk.connection.BluetoothAdapterManager;
import com.gotenna.sdk.connection.BluetoothAdapterManager.BluetoothStatus;
import com.gotenna.sdk.connection.GTConnectionError;
import com.gotenna.sdk.connection.GTConnectionManager;
import com.gotenna.sdk.connection.GTConnectionState;
import com.gotenna.sdk.data.GTCommand;
import com.gotenna.sdk.data.GTCommandCenter;
import com.gotenna.sdk.data.GTDeviceType;
import com.gotenna.sdk.data.GTError;
import com.gotenna.sdk.data.GTErrorListener;
import com.gotenna.sdk.data.GTResponse;
import com.gotenna.sdk.data.Place;
import com.gotenna.sdk.data.frequencies.FrequencySlot;
import com.gotenna.sdk.data.frequencies.FrequencySlot.Bandwidth;
import com.gotenna.sdk.data.frequencies.GTFrequencyChannel;
import com.gotenna.sdk.data.user.UserDataStore;
import com.gotenna.sdk.exceptions.GTInvalidFrequencyChannelException;
import com.gotenna.sdk.frequency.PowerLevel;
import com.gotenna.sdk.frequency.SetFrequencySlotInfoInteractor;
import com.gotenna.sdk.georegion.PlaceFinderTask;
import com.gotenna.sdk.sample.PermissionsUtils;

import java.util.ArrayList;
import java.util.List;

/**
 * A presenter for {@link ScanActivity}.
 * <p>
 * Created on: 7/10/17.
 *
 * @author Thomas Colligan
 */

class ScanPresenter implements GTConnectionManager.GTConnectionListener
{
    //==============================================================================================
    // Class Properties
    //==============================================================================================

    private ScanView view;
    private final UserDataStore userDataStore;
    private final BluetoothAdapterManager bluetoothAdapterManager;
    private final GTConnectionManager gtConnectionManager;
    private final GTCommandCenter gtCommandCenter;
    private final SetFrequencySlotInfoInteractor setFrequencySlotInfoInteractor;

    //==============================================================================================
    // Constructor
    //==============================================================================================

    ScanPresenter()
    {
        userDataStore = UserDataStore.getInstance();
        bluetoothAdapterManager = BluetoothAdapterManager.getInstance();
        gtConnectionManager = GTConnectionManager.getInstance();
        gtCommandCenter = GTCommandCenter.getInstance();
        setFrequencySlotInfoInteractor = new SetFrequencySlotInfoInteractor();
    }

    //==============================================================================================
    // Class Instance Methods
    //==============================================================================================

    void attachView(ScanView view)
    {
        this.view = view;
        gtConnectionManager.addGtConnectionListener(this);
    }

    void detachView()
    {
        this.view = null;
        gtConnectionManager.removeGtConnectionListener(this);
    }

    private void checkBluetoothStatus()
    {
        BluetoothStatus bluetoothStatus = bluetoothAdapterManager.getBluetoothStatus();

        switch (bluetoothStatus)
        {
            case SUPPORTED_AND_ENABLED:
                view.showGotennaDeviceTypeSelectionDialog();
                break;
            case SUPPORTED_NOT_ENABLED:
                view.requestEnableBluetooth();
                break;
            case NOT_SUPPORTED:
                view.showBluetoothNotSupportedMessage();
                break;
        }
    }

    private void scanForGotenna(GTDeviceType deviceType)
    {
        try
        {
            gtConnectionManager.scanAndConnect(deviceType);
            view.showScanningInProgressDialog();
            view.startTimeoutCountdown();
        }
        catch (UnsupportedOperationException e)
        {
            view.showUnsupportedDeviceWarning(e.getLocalizedMessage());
        }
    }

    //==============================================================================================
    // Presenter Action Methods
    //==============================================================================================

    void onCreate()
    {
        if (!GoTenna.tokenIsVerified())
        {
            view.showInvalidTokenAlert();
            return;
        }

        if (!PermissionsUtils.hasLocationPermission())
        {
            view.requestLocationPermission();
        }

        if (userDataStore.hasValidUser())
        {
            view.enableScanPreviousButton();
        }
        else
        {
            view.disableScanPreviousButton();
        }
    }

    void onRequestPermissionsResult()
    {
        if (!PermissionsUtils.hasLocationPermission())
        {
            view.requestLocationPermission();
        }
    }

    void onBluetoothEnabled()
    {
        checkBluetoothStatus();
    }

    void onScanForNewGotenna()
    {
        if (!PermissionsUtils.hasLocationPermission())
        {
            view.requestLocationPermission();
            return;
        }

        // Clear old connected Bluetooth MAC address of previous goTenna we were connected to
        gtConnectionManager.clearConnectedGotennaAddress();

        checkBluetoothStatus();
    }

    void onScanForPreviousGotenna()
    {
        if (!PermissionsUtils.hasLocationPermission())
        {
            view.requestLocationPermission();
            return;
        }

        checkBluetoothStatus();
    }

    void onScanForMesh()
    {
        scanForGotenna(GTDeviceType.MESH);
    }

    void onScanForPro()
    {
        scanForGotenna(GTDeviceType.PRO);
    }

    void onScanTimeoutOccurred()
    {
        gtConnectionManager.disconnect();
        view.dismissScanningProgressDialog();
        view.showScanningTimeoutDialog();
    }

    void onErrorConfirmed()
    {
        gtConnectionManager.disconnect();
    }

    //==============================================================================================
    // GTConnectionListener Implementation
    //==============================================================================================

    @Override
    public void onConnectionStateUpdated(@NonNull GTConnectionState connectionState)
    {
        switch (connectionState)
        {
            case CONNECTED:
                onGotennaConnected();
                break;
        }
    }

    @Override
    public void onConnectionError(@NonNull GTConnectionState connectionState, @NonNull GTConnectionError error)
    {
        view.stopTimeoutCountdown();
        view.dismissScanningProgressDialog();

        switch (error.getErrorState())
        {
            case X_UPGRADE_CHECK_FAILED:
                /*
                    This error gets passed when we failed to check if the device is goTenna X. This
                    could happen due to connectivity issues with the device or error checking if the
                    device has been remotely upgraded.
                 */
                view.showXCheckError();
                break;
            case NOT_X_DEVICE_ERROR:
                /*
                    This device is confirmed not to be a goTenna X device. Using error.getDetailString()
                    you can pull the serial number of the connected device.
                 */
                view.showNotXDeviceWarning(error.getDetailString());
                break;
        }
    }

    //==============================================================================================
    // Private Class Instance Methods
    //==============================================================================================

    private void onGotennaConnected()
    {
        view.stopTimeoutCountdown();
        view.dismissScanningProgressDialog();

        GTDeviceType deviceType = GTConnectionManager.getInstance().getDeviceType();

        switch (deviceType)
        {
            case V1:
                view.showSdkOptionsScreen();
                break;
            case MESH:
                findAndSetMeshLocation();
                break;
            case PRO:
                setProFrequencies();
                break;
        }
    }

    private void findAndSetMeshLocation()
    {
        // TODO: Use Android GPS to determine user's current location instead of hardcoding lat lng
        // TODO: Must use location to correctly set goTenna Mesh Device Frequency for the user's current location as per FCC rules
        Location location = new Location("Custom");
        location.setLatitude(40.619373);
        location.setLongitude(-74.102977);

        new PlaceFinderTask(location, new PlaceFinderTask.PlaceFinderListener()
        {
            @Override
            public void onPlaceFound(@NonNull Place place)
            {
                if (place == Place.UNKNOWN)
                {
                    // Default to North America if we can't find the actual location
                    place = Place.NORTH_AMERICA;

                    if (view != null)
                    {
                        view.showPlaceUnknownWarning();
                    }
                }

                gtCommandCenter.sendSetGeoRegion(place, new GTCommand.GTCommandResponseListener()
                {
                    @Override
                    public void onResponse(GTResponse response)
                    {
                        if (view == null)
                            return;

                        if (response.getResponseCode() == GTResponse.GTCommandResponseCode.POSITIVE)
                        {
                            view.showSdkOptionsScreen();
                        }
                        else
                        {
                            view.showErrorSettingFrequenciesWarning();
                        }
                    }
                }, new GTErrorListener()
                {
                    @Override
                    public void onError(GTError error)
                    {
                        if (view == null)
                            return;

                        view.showErrorSettingFrequenciesWarning();
                    }
                });
            }
        }).execute();
    }

    private void setProFrequencies()
    {
        // Example of how to set frequencies on the goTenna Pro
        FrequencySlot frequencySlot = createExampleFrequencySlot();

        setFrequencySlotInfoInteractor.setFrequencySlotInfoOnGotenna(frequencySlot, new SetFrequencySlotInfoInteractor.SetFrequencySlotInfoListener()
        {
            @Override
            public void onInfoStateChanged(@NonNull SetFrequencySlotInfoInteractor.SetInfoState setInfoState)
            {
                if (view == null)
                    return;

                switch (setInfoState)
                {
                    case NON_IDLE_STATE_ERROR:
                    case NOT_CONNECTED_ERROR:
                    case SET_POWER_LEVEL_ERROR:
                    case SET_BANDWIDTH_BITRATE_ERROR:
                    case SET_FREQUENCIES_ERROR:
                        view.showErrorSettingFrequenciesWarning();
                        break;
                    case SET_ALL_SUCCESS:
                        view.showSdkOptionsScreen();
                        break;
                }
            }
        });
    }

    private FrequencySlot createExampleFrequencySlot()
    {
        FrequencySlot frequencySlot = new FrequencySlot();
        frequencySlot.setPowerLevel(PowerLevel.ONE_HALF);
        frequencySlot.setBandwidth(Bandwidth._11_80_kHZ);
        try
        {
            // There is a default set of frequencies that a slot get populated with if you do not know what to use
            List<GTFrequencyChannel> frequencyChannels = new ArrayList<>();
            frequencyChannels.add(new GTFrequencyChannel(150000000, true));
            frequencyChannels.add(new GTFrequencyChannel(151000000, false));
            frequencySlot.setFrequencyChannels(frequencyChannels);
        }
        catch (GTInvalidFrequencyChannelException e)
        {
            e.printStackTrace();
        }

        return frequencySlot;
    }

    //==============================================================================================
    // ScanView Interface
    //==============================================================================================

    interface ScanView
    {
        void showInvalidTokenAlert();

        void showUnsupportedDeviceWarning(String message);

        void enableScanPreviousButton();

        void disableScanPreviousButton();

        void requestLocationPermission();

        void requestEnableBluetooth();

        void showBluetoothNotSupportedMessage();

        void showGotennaDeviceTypeSelectionDialog();

        void showScanningInProgressDialog();

        void startTimeoutCountdown();

        void stopTimeoutCountdown();

        void dismissScanningProgressDialog();

        void showScanningTimeoutDialog();

        void showSdkOptionsScreen();

        void showPlaceUnknownWarning();

        void showErrorSettingFrequenciesWarning();

        void showXCheckError();

        void showNotXDeviceWarning(String serialNumber);
    }
}
