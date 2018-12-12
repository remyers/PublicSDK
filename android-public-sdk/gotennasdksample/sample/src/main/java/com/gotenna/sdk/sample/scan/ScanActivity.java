package com.gotenna.sdk.sample.scan;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.text.format.DateUtils;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.gotenna.sdk.connection.BluetoothAdapterManager;
import com.gotenna.sdk.sample.PermissionsUtils;
import com.gotenna.sdk.sample.R;
import com.gotenna.sdk.sample.options.SdkOptionsActivity;

/**
 * Screen which allows the user to choose which type of goTenna they would like to connect to.
 * <p>
 * Created on: 7/10/17.
 *
 * @author Thomas Colligan
 */

public class ScanActivity extends AppCompatActivity implements ScanPresenter.ScanView
{
    //==============================================================================================
    // Class Properties
    //==============================================================================================

    private static final int ENABLE_BLUETOOTH_PERMISSION_REQUEST_CODE = 1003;
    private static final int LOCATION_PERMISSION_REQUEST_CODE = 54321;
    private static final int SCAN_TIMEOUT_MILLISECONDS = 30000;

    private ScanPresenter presenter;
    private Handler handler;
    private ProgressDialog scanProgressDialog;
    private Button scanPreviousGotennaButton;

    //==============================================================================================
    // Static Class Methods
    //==============================================================================================

    public static void start(Context context)
    {
        Intent starter = new Intent(context, ScanActivity.class);
        context.startActivity(starter);
    }

    //==============================================================================================
    // Life-cycle Methods
    //==============================================================================================

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_scan);

        scanPreviousGotennaButton = findViewById(R.id.scanPreviousGotennaButton);

        handler = new Handler();

        presenter = new ScanPresenter();
        presenter.attachView(this);
        presenter.onCreate();
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        if (requestCode == ENABLE_BLUETOOTH_PERMISSION_REQUEST_CODE &&
                resultCode == Activity.RESULT_OK)
        {
            presenter.onBluetoothEnabled();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           @NonNull String permissions[],
                                           @NonNull int[] grantResults)
    {
        presenter.onRequestPermissionsResult();
    }

    @Override
    protected void onDestroy()
    {
        presenter.detachView();
        presenter = null;
        super.onDestroy();
    }

    //==============================================================================================
    // Button Click Methods
    //==============================================================================================

    public void onScanForNewGotennaClicked(View v)
    {
        presenter.onScanForNewGotenna();
    }

    public void onScanForPreviouslyUsedGotennaClicked(View v)
    {
        presenter.onScanForPreviousGotenna();
    }

    //==============================================================================================
    // Runnables
    //==============================================================================================

    private final Runnable scanTimeoutRunnable = new Runnable()
    {
        @Override
        public void run()
        {
            presenter.onScanTimeoutOccurred();
        }
    };

    //==============================================================================================
    // MainActivityView Implementation
    //==============================================================================================

    @Override
    public void showInvalidTokenAlert()
    {
        new AlertDialog.Builder(this)
                .setMessage(R.string.invalid_sdk_token)
                .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        finish();
                    }
                })
                .create()
                .show();
    }

    @Override
    public void showUnsupportedDeviceWarning(String message)
    {
        new AlertDialog.Builder(this)
                .setMessage(message)
                .setPositiveButton(android.R.string.ok, null)
                .create()
                .show();
    }

    @Override
    public void enableScanPreviousButton()
    {
        scanPreviousGotennaButton.setEnabled(true);
    }

    @Override
    public void disableScanPreviousButton()
    {
        scanPreviousGotennaButton.setEnabled(false);
    }

    @Override
    public void requestLocationPermission()
    {
        PermissionsUtils.requestLocationPermission(this, LOCATION_PERMISSION_REQUEST_CODE);
    }

    @Override
    public void requestEnableBluetooth()
    {
        BluetoothAdapterManager.showRequestBluetoothPermissionDialog(this,
                ENABLE_BLUETOOTH_PERMISSION_REQUEST_CODE);
    }

    @Override
    public void showBluetoothNotSupportedMessage()
    {
        Toast.makeText(this, R.string.bluetooth_not_supported, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void showGotennaDeviceTypeSelectionDialog()
    {
        new AlertDialog.Builder(this)
                .setTitle(R.string.choose_gotenna_type)
                .setPositiveButton(R.string.gotenna_mesh_choice, new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        presenter.onScanForMesh();
                    }
                })
                .setNeutralButton(R.string.gotenna_pro_choice, new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        presenter.onScanForPro();
                    }
                })
                .show();
    }

    @Override
    public void showScanningInProgressDialog()
    {
        scanProgressDialog = new ProgressDialog(this);
        scanProgressDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        scanProgressDialog.setMessage(getString(R.string.searching_for_gotenna));
        scanProgressDialog.setCancelable(false);
        scanProgressDialog.show();
    }

    @Override
    public void startTimeoutCountdown()
    {
        handler.removeCallbacks(scanTimeoutRunnable);
        handler.postDelayed(scanTimeoutRunnable, SCAN_TIMEOUT_MILLISECONDS);
    }

    @Override
    public void stopTimeoutCountdown()
    {
        handler.removeCallbacks(scanTimeoutRunnable);
    }

    @Override
    public void dismissScanningProgressDialog()
    {
        scanProgressDialog.dismiss();
        scanProgressDialog = null;
    }

    @Override
    public void showScanningTimeoutDialog()
    {
        new AlertDialog.Builder(this)
                .setMessage(getString(R.string.unable_to_find_gotenna_after_scanning,
                        SCAN_TIMEOUT_MILLISECONDS / DateUtils.SECOND_IN_MILLIS))
                .setPositiveButton(android.R.string.ok, null)
                .create()
                .show();
    }

    @Override
    public void showSdkOptionsScreen()
    {
        SdkOptionsActivity.start(this);
        finish();
    }

    @Override
    public void showPlaceUnknownWarning()
    {
        Toast.makeText(this, R.string.cannot_find_place, Toast.LENGTH_LONG).show();
    }

    @Override
    public void showErrorSettingFrequenciesWarning()
    {
        new AlertDialog.Builder(this)
                .setMessage(getString(R.string.error_setting_frequencies))
                .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        presenter.onErrorConfirmed();
                    }
                })
                .create()
                .show();
    }

    @Override
    public void showXCheckError()
    {
        new AlertDialog.Builder(this)
                .setMessage(R.string.x_check_error)
                .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        presenter.onErrorConfirmed();
                    }
                })
                .create()
                .show();
    }

    @Override
    public void showNotXDeviceWarning(String serialNumber)
    {
        new AlertDialog.Builder(this)
                .setMessage(getString(R.string.not_x_device, serialNumber))
                .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        presenter.onErrorConfirmed();
                    }
                })
                .create()
                .show();
    }
}
