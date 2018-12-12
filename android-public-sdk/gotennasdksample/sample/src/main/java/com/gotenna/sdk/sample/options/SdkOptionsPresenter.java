package com.gotenna.sdk.sample.options;

import com.gotenna.sdk.connection.GTConnectionManager;
import com.gotenna.sdk.data.GTCommand;
import com.gotenna.sdk.data.GTCommandCenter;
import com.gotenna.sdk.data.GTError;
import com.gotenna.sdk.data.GTErrorListener;
import com.gotenna.sdk.data.GTResponse;
import com.gotenna.sdk.data.user.UserDataStore;
import com.gotenna.sdk.responses.SystemInfoResponseData;

/**
 * A presenter for {@link SdkOptionsActivity}.
 * <p>
 * Created on: 7/12/17.
 *
 * @author Thomas Colligan
 */

class SdkOptionsPresenter
{
    //==============================================================================================
    // Class Properties
    //==============================================================================================

    private SdkOptionsView view;
    private FirmwareUpdateHelper firmwareUpdateHelper;
    private final UserDataStore userDataStore;
    private final GTCommandCenter gtCommandCenter;
    private final GTConnectionManager gtConnectionManager;

    //==============================================================================================
    // Constructor
    //==============================================================================================

    SdkOptionsPresenter()
    {
        userDataStore = UserDataStore.getInstance();
        gtCommandCenter = GTCommandCenter.getInstance();
        gtConnectionManager = GTConnectionManager.getInstance();
    }

    //==============================================================================================
    // Class Instance Methods
    //==============================================================================================

    void attach(SdkOptionsView sdkOptionsView)
    {
        this.view = sdkOptionsView;
    }

    void detach()
    {
        this.view = null;
    }

    //==============================================================================================
    // Presenter Action Methods
    //==============================================================================================

    void onCreate(FirmwareUpdateHelper firmwareUpdateHelper)
    {
        this.firmwareUpdateHelper = firmwareUpdateHelper;

        // This person has not selected their user or set their GID yet
        // Force them to the SetGidActivity screen so they can select a user
        if (userDataStore.getCurrentUser() == null)
        {
            view.showSetGidScreenWithDoneToolbar();
        }
    }

    void onSendEcho()
    {
        // Send an echo command to the goTenna to flash the LED light
        gtCommandCenter.sendEchoCommand(new GTCommand.GTCommandResponseListener()
        {
            @Override
            public void onResponse(GTResponse response)
            {
                if (view == null)
                    return;

                switch (response.getResponseCode())
                {
                    case POSITIVE:
                        view.showEchoSuccessMessage();
                        break;
                    case NEGATIVE:
                        view.showEchoNackMessage();
                        break;
                    case ERROR:
                        view.showEchoErrorMessage();
                        break;
                }
            }
        }, new GTErrorListener()
        {
            @Override
            public void onError(GTError error)
            {
                if (view == null)
                    return;

                view.showEchoErrorMessage();
            }
        });
    }

    void onSendGetSystemInfo()
    {
        GTCommandCenter.getInstance().sendGetSystemInfo(new GTCommandCenter.GTSystemInfoResponseListener()
        {
            @Override
            public void onResponse(SystemInfoResponseData systemInfoResponseData)
            {
                if (view == null)
                    return;

                // This is where you could retrieve info such at the goTenna's battery level and current firmware version
                view.showSystemInfo(systemInfoResponseData);
            }
        }, new GTErrorListener()
        {
            @Override
            public void onError(GTError error)
            {
                if (view == null)
                    return;

                view.showSystemInfoErrorMessage();
            }
        });
    }

    void onDisconnect()
    {
        // There is another method you can use, GTConnectionManager.getInstance().disconnectWithRetry();
        // That method will disconnect us from the current goTenna and immediately start scanning for another goTenna
        // Chances are we will re-connect to the goTenna we were just connected to, but it is helpful for clearing up
        // potential connection issues or performing other business logic.
        gtConnectionManager.disconnect();

        view.showScanScreenAndFinish();
    }

    void onDoUpdateFirmwareCheck()
    {
        // For a firmware update, first we ask the goTenna what its current firmware version is so we can check if an update is needed
        gtCommandCenter.sendGetSystemInfo(new GTCommandCenter.GTSystemInfoResponseListener()
        {
            @Override
            public void onResponse(final SystemInfoResponseData systemInfoResponseData)
            {
                // Now we check to see if their is a newer version of the firmware available from the Amazon Bucket
                firmwareUpdateHelper.checkForNewFirmwareFile(systemInfoResponseData.getFirmwareVersion(),
                        new FirmwareUpdateHelper.FirmwareFileDownloadListener()
                        {
                            @Override
                            public void onFirmwareFileDownloaded()
                            {
                                if (view == null)
                                    return;

                                if (firmwareUpdateHelper.shouldDoFirmwareUpdate(systemInfoResponseData))
                                {
                                    firmwareUpdateHelper.showFirmwareUpdateDialog(systemInfoResponseData);
                                }
                                else
                                {
                                    view.showFirmwareVersionAlreadyUpToDateMessage();
                                }
                            }

                            @Override
                            public void onFirmwareFileDownloadFailed()
                            {
                                if (view == null)
                                    return;

                                view.showLatestFirmwareNotDownloadedMessage();
                            }
                        });
            }
        }, new GTErrorListener()
        {
            @Override
            public void onError(GTError error)
            {
                if (view == null)
                    return;

                view.showSystemInfoErrorMessage();
            }
        });
    }

    void onDestroy()
    {
        this.firmwareUpdateHelper = null;
    }

    //==============================================================================================
    // SdkOptionView Interface
    //==============================================================================================

    interface SdkOptionsView
    {
        void showSetGidScreenWithDoneToolbar();

        void showEchoSuccessMessage();

        void showEchoNackMessage();

        void showEchoErrorMessage();

        void showSystemInfo(SystemInfoResponseData systemInfoResponseData);

        void showSystemInfoErrorMessage();

        void showScanScreenAndFinish();

        void showLatestFirmwareNotDownloadedMessage();

        void showFirmwareVersionAlreadyUpToDateMessage();
    }
}
