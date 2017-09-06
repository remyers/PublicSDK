package com.gotenna.sdk.sample.options;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Toast;

import com.gotenna.sdk.responses.SystemInfoResponseData;
import com.gotenna.sdk.sample.R;
import com.gotenna.sdk.sample.messages.BroadcastMessagesActivity;
import com.gotenna.sdk.sample.groups.CreateGroupActivity;
import com.gotenna.sdk.sample.groups.GroupMessagesActivity;
import com.gotenna.sdk.sample.messages.PrivateMessagesActivity;
import com.gotenna.sdk.sample.gid.SetGidActivity;
import com.gotenna.sdk.sample.options.SdkOptionsPresenter.SdkOptionsView;
import com.gotenna.sdk.sample.scan.ScanActivity;

/**
 * The central screen of the app which contains examples of different pieces of goTenna SDK
 * functionality.
 * <p>
 * Created on: 7/12/17.
 *
 * @author Thomas Colligan
 */

public class SdkOptionsActivity extends AppCompatActivity implements SdkOptionsView
{
    //==============================================================================================
    // Class Properties
    //==============================================================================================

    private SdkOptionsPresenter presenter;

    //==============================================================================================
    // Static Methods
    //==============================================================================================

    public static void start(Context context)
    {
        Intent starter = new Intent(context, SdkOptionsActivity.class);
        context.startActivity(starter);
    }

    //==============================================================================================
    // Life-Cycle Methods
    //==============================================================================================

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sdk_options);

        presenter = new SdkOptionsPresenter();
        presenter.attach(this);
        presenter.onCreate(new FirmwareUpdateHelper(this));
    }

    @Override
    protected void onDestroy()
    {
        presenter.onDestroy();
        presenter.detach();
        presenter = null;

        super.onDestroy();
    }

    //==============================================================================================
    // Button Click Methods
    //==============================================================================================

    public void onSendEchoButtonClicked(View v)
    {
        presenter.onSendEcho();
    }

    public void onSendGetSystemInfoButtonClicked(View v)
    {
        presenter.onSendGetSystemInfo();
    }

    public void onSetGidButtonClicked(View v)
    {
        SetGidActivity.start(this);
    }

    public void onSendPrivateButtonMessageClicked(View v)
    {
        PrivateMessagesActivity.start(this);
    }

    public void onSendBroadcastMessageClicked(View v)
    {
        BroadcastMessagesActivity.start(this);
    }

    public void onCreateGroupButtonClicked(View v)
    {
        CreateGroupActivity.start(this);
    }

    public void onSendGroupMessageButtonClicked(View v)
    {
        GroupMessagesActivity.start(this);
    }

    public void onDisconnectButtonClicked(View v)
    {
        presenter.onDisconnect();
    }

    public void onUpdateFirmwareButtonClicked(View v)
    {
        presenter.onDoUpdateFirmwareCheck();
    }

    //==============================================================================================
    // SDKOptionView Implementation
    //==============================================================================================

    @Override
    public void showSetGidScreenWithDoneToolbar()
    {
        SetGidActivity.startWithDoneToolbar(this);
    }

    @Override
    public void showEchoSuccessMessage()
    {
        Toast.makeText(getApplicationContext(), R.string.echo_success_toast, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void showEchoNackMessage()
    {
        Toast.makeText(getApplicationContext(), R.string.echo_nack_toast, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void showEchoErrorMessage()
    {
        Toast.makeText(getApplicationContext(), R.string.echo_error_toast, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void showSystemInfo(SystemInfoResponseData systemInfoResponseData)
    {
        Toast.makeText(getApplicationContext(), systemInfoResponseData.toString(), Toast.LENGTH_SHORT).show();
    }

    @Override
    public void showSystemInfoErrorMessage()
    {
        Toast.makeText(getApplicationContext(), R.string.system_info_error, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void showScanScreenAndFinish()
    {
        ScanActivity.start(this);
        finish();
    }

    @Override
    public void showLatestFirmwareNotDownloadedMessage()
    {
        Toast.makeText(getApplicationContext(), R.string.firmware_not_downloaded_message,
                Toast.LENGTH_SHORT).show();
    }

    @Override
    public void showFirmwareVersionAlreadyUpToDateMessage()
    {
        Toast.makeText(getApplicationContext(), R.string.firmware_is_already_updated_toast_text,
                Toast.LENGTH_SHORT).show();
    }
}
