package com.gotenna.sdk.sample.options;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.util.Log;

import com.gotenna.sdk.bluetooth.GTConnectionManager;
import com.gotenna.sdk.firmware.GTFirmwareAmazonDownloader;
import com.gotenna.sdk.firmware.GTFirmwareUpdater;
import com.gotenna.sdk.firmware.GTFirmwareUpdater.FirmwareUpdateState;
import com.gotenna.sdk.firmware.GTFirmwareUpdater.GTFirmwareUpdaterListener;
import com.gotenna.sdk.firmware.GTFirmwareVersion;
import com.gotenna.sdk.responses.SystemInfoResponseData;
import com.gotenna.sdk.sample.R;

/**
 * A class that helps us display the appropriate UI while a firmware update occurs.
 * <p>
 * Created on 2/19/16
 *
 * @author ThomasColligan
 */
class FirmwareUpdateHelper implements GTFirmwareUpdaterListener
{
    //==============================================================================================
    // Class Properties
    //==============================================================================================

    private static final String LOG_TAG = "FirmwareUpdateHelper";
    private static final int MAX_PROGRESS = 100;

    private Activity activity;
    private ProgressDialog indeterminateProgressDialog;
    private ProgressDialog determinateProgressDialog;

    private GTFirmwareVersion latestFirmwareVersion;
    private GTFirmwareUpdater latestFirmwareFileUpdater;
    private GTFirmwareAmazonDownloader firmwareAmazonDownloader;

    //==============================================================================================
    // Constructor
    //==============================================================================================

    FirmwareUpdateHelper(Activity activity)
    {
        this.activity = activity;

        indeterminateProgressDialog = new ProgressDialog(activity);
        indeterminateProgressDialog.setIndeterminate(true);
        indeterminateProgressDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        indeterminateProgressDialog.setCancelable(false);
        indeterminateProgressDialog.setTitle(R.string.firmware_update_progress_dialog_title);

        determinateProgressDialog = new ProgressDialog(activity);
        determinateProgressDialog.setIndeterminate(false);
        determinateProgressDialog.setMax(MAX_PROGRESS);
        determinateProgressDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
        determinateProgressDialog.setCancelable(false);
        determinateProgressDialog.setTitle(R.string.firmware_update_progress_dialog_title);
    }

    //==============================================================================================
    // Class Instance Methods
    //==============================================================================================

    boolean hasLatestFirmwareVersion()
    {
        return latestFirmwareVersion != null;
    }

    boolean shouldDoFirmwareUpdate(SystemInfoResponseData systemInfoResponseData)
    {
        return latestFirmwareVersion != null &&
                systemInfoResponseData.getFirmwareVersion().isLessThan(latestFirmwareVersion);

    }

    void showFirmwareUpdateDialog(SystemInfoResponseData currentSystemInfo)
    {
        new AlertDialog.Builder(activity)
                .setTitle(R.string.firmware_update_dialog_title)
                .setMessage(activity.getString(R.string.firmware_update_dialog_message, currentSystemInfo.getFirmwareVersion().toString(), latestFirmwareVersion.toString()))
                .setCancelable(false)
                .setPositiveButton(R.string.firmware_update_dialog_begin_update, new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialog, int which)
                    {
                        dialog.cancel();

                        startFirmwareUpdateUsingLatest();
                    }
                })
                .setNegativeButton(R.string.firmware_update_dialog_no, new DialogInterface.OnClickListener()
                {
                    public void onClick(DialogInterface dialog, int id)
                    {
                        dialog.cancel();
                    }
                })
                .show();
    }

    void checkForNewFirmwareFile()
    {
        firmwareAmazonDownloader = new GTFirmwareAmazonDownloader();

        // Make sure we ask the correct Amazon Bucket for the correct firmware, dont want to update a V1 with Mesh firmware!
        GTConnectionManager.GTDeviceType gtDeviceType = GTConnectionManager.getInstance().getDeviceType();
        GTFirmwareAmazonDownloader.AmazonFirmwareBucket bucket = null;
        switch (gtDeviceType)
        {
            case V1:
                bucket = GTFirmwareAmazonDownloader.AmazonFirmwareBucket.V1_PRODUCTION;
                break;
            case MESH:
                bucket = GTFirmwareAmazonDownloader.AmazonFirmwareBucket.MESH_PRODUCTION;
                break;
        }

        firmwareAmazonDownloader.setAmazonFirmwareBucket(bucket);

        firmwareAmazonDownloader.checkForNewFirmware(new GTFirmwareAmazonDownloader.GTFirmwareAmazonDownloaderListener()
        {
            @Override
            public void onDownloadedNewFirmwareFile(GTFirmwareVersion firmwareVersion, GTFirmwareUpdater firmwareUpdater)
            {
                latestFirmwareVersion = firmwareVersion;
                latestFirmwareFileUpdater = firmwareUpdater;
            }

            @Override
            public void onFailedToDownloadNewFirmwareFile()
            {
                Log.w(LOG_TAG, "Failed to download latest firmware file");
            }
        });
    }

    private void startFirmwareUpdateUsingLatest()
    {
        if (latestFirmwareFileUpdater != null)
        {
            latestFirmwareFileUpdater.setFirmwareUpdaterListener(this);
            latestFirmwareFileUpdater.startFirmwareUpdate();
        }
    }

    private void showFirmwareUpdateCompletedDialog(boolean firmwareUpdateWasSuccessful)
    {
        new AlertDialog.Builder(activity)
                .setTitle(firmwareUpdateWasSuccessful ?
                        R.string.firmware_update_completed_success_title : R.string.firmware_update_completed_failure_title)
                .setMessage(firmwareUpdateWasSuccessful ?
                        R.string.firmware_update_completed_success_message : R.string.firmware_update_completed_failure_message)
                .setCancelable(false)
                .setPositiveButton(R.string.firmware_update_completed_ok_button_text, new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialog, int which)
                    {
                        dialog.cancel();
                    }
                }).show();
    }

    //==============================================================================================
    // GTFirmwareUpdaterListener Implementation
    //==============================================================================================

    @Override
    public void onFirmwareWritingStateUpdated(final FirmwareUpdateState firmwareUpdateState)
    {
        activity.runOnUiThread(new Runnable()
        {
            @Override
            public void run()
            {
                switch (firmwareUpdateState)
                {
                    case INACTIVE:
                        break;

                    case INITIALIZING:
                        indeterminateProgressDialog.setMessage(activity.getString(R.string.firmware_update_progress_dialog_initializing));
                        indeterminateProgressDialog.show();
                        break;

                    case WRITING:
                        indeterminateProgressDialog.dismiss();
                        determinateProgressDialog.setMessage(activity.getString(R.string.firmware_update_progress_dialog_writing));
                        determinateProgressDialog.show();
                        break;

                    case ABORT:
                        indeterminateProgressDialog.dismiss();
                        determinateProgressDialog.dismiss();
                        break;

                    case FINALIZING:
                        determinateProgressDialog.dismiss();
                        indeterminateProgressDialog.setMessage(activity.getString(R.string.firmware_update_progress_dialog_finalizing));
                        indeterminateProgressDialog.show();
                        break;

                    case WAITING_FOR_REBOOT:
                        indeterminateProgressDialog.setMessage(activity.getString(R.string.firmware_update_progress_dialog_waiting));
                        break;

                    case UPDATE_FAILED:
                        indeterminateProgressDialog.dismiss();
                        showFirmwareUpdateCompletedDialog(false);
                        break;

                    case UPDATE_SUCCEEDED:
                        indeterminateProgressDialog.dismiss();
                        showFirmwareUpdateCompletedDialog(true);
                        break;
                }
            }
        });
    }

    @Override
    public void onFirmwareWriteProgressUpdated(float firmwareUpdateProgress)
    {
        // The progress float is a value from 0.0 - 1.0, with 1.0 representing 100%
        int progressValue = (int) (firmwareUpdateProgress * MAX_PROGRESS);
        determinateProgressDialog.setProgress(progressValue);
    }
}