package com.gotenna.sdk.sample.groups;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.view.Gravity;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.gotenna.sdk.sample.R;
import com.gotenna.sdk.sample.gid.SetGidActivity;
import com.gotenna.sdk.sample.messages.MessageViewModel;
import com.gotenna.sdk.sample.messages.MessagesArrayAdapter;

import java.util.ArrayList;
import java.util.List;

/**
 * A screen that allows a user to send and receive group messages.
 * <p>
 * Created on: 7/14/17.
 *
 * @author Thomas Colligan
 */

public class GroupMessagesActivity extends AppCompatActivity implements GroupMessagesPresenter.GroupMessagesView
{
    //==============================================================================================
    // Class Properties
    //==============================================================================================

    private TextView selectedGroupTextView;
    private Button selectGroupButton;
    private ListView messagesListView;
    private EditText sendMessageEditText;
    private GroupMessagesPresenter presenter;
    private MessagesArrayAdapter messagesArrayAdapter;
    private List<MessageViewModel> messages;

    //==============================================================================================
    // Static Class Methods
    //==============================================================================================

    public static void start(Context context)
    {
        Intent starter = new Intent(context, GroupMessagesActivity.class);
        context.startActivity(starter);
    }

    //==============================================================================================
    // Life-Cycle Methods
    //==============================================================================================

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_group_messages);

        selectedGroupTextView = (TextView) findViewById(R.id.selectedGroupTextView);
        selectGroupButton = (Button) findViewById(R.id.selectGroupButton);
        messagesListView = (ListView) findViewById(R.id.messagesListView);
        sendMessageEditText = (EditText) findViewById(R.id.sendMessageEditText);

        presenter = new GroupMessagesPresenter();
        presenter.attachView(this);
        presenter.onCreate();

        ActionBar actionBar = getSupportActionBar();

        if (actionBar != null)
        {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        switch (item.getItemId())
        {
            case android.R.id.home:
                finish();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
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

    public void onSelectGroupButtonClicked(View v)
    {
        presenter.onSelectGroup();
    }

    public void onSendMessageButtonClicked(View v)
    {
        String messageText = sendMessageEditText.getText().toString();
        presenter.onSendMessage(messageText);
    }

    //==============================================================================================
    // GroupMessagesView Implementation
    //==============================================================================================

    @Override
    public void showSelectGroupUi()
    {
        selectedGroupTextView.setVisibility(View.GONE);
        selectGroupButton.setVisibility(View.VISIBLE);
    }

    @Override
    public void showSelectedGroupUi(long selectedGroupGID)
    {
        selectedGroupTextView.setText(getString(R.string.selected_group_text, selectedGroupGID));
        selectedGroupTextView.setVisibility(View.VISIBLE);
        selectGroupButton.setVisibility(View.GONE);
    }

    @Override
    public void showMustSelectUserFirstErrorMessage()
    {
        Toast toast = Toast.makeText(getApplicationContext(), R.string.must_choose_user_toast_text,
                Toast.LENGTH_SHORT);
        toast.setGravity(Gravity.CENTER, 0, 0);
        toast.show();
    }

    @Override
    public void showSelectGidScreen()
    {
        SetGidActivity.start(this);
    }

    @Override
    public void showNoGroupsErrorMessage()
    {
        Toast toast = Toast.makeText(getApplicationContext(), R.string.no_groups_toast_text,
                Toast.LENGTH_LONG);
        toast.setGravity(Gravity.CENTER, 0, 0);
        toast.show();
    }

    @Override
    public void showCreateGroupScreen()
    {
        CreateGroupActivity.start(this);
    }

    @Override
    public void showSelectGroupDialog(final List<Long> groupGIDs)
    {
        CharSequence[] alertChoices = new CharSequence[groupGIDs.size()];

        for (int i = 0; i < groupGIDs.size(); i++)
        {
            Long groupGID = groupGIDs.get(i);
            alertChoices[i] = groupGID.toString();
        }

        new AlertDialog.Builder(this)
                .setTitle(R.string.select_group_dialog_title)
                .setSingleChoiceItems(alertChoices, -1, new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialog, int which)
                    {
                        long selectedGroupGID = groupGIDs.get(which);
                        presenter.onGroupSelected(selectedGroupGID);

                        dialog.cancel();
                    }
                })
                .show();
    }

    @Override
    public void showGroupNotSelectedErrorMessage()
    {
        Toast toast = Toast.makeText(getApplicationContext(), R.string.invalid_group_toast_text,
                Toast.LENGTH_LONG);
        toast.setGravity(Gravity.CENTER, 0, 0);
        toast.show();
    }

    @Override
    public void showEmptyMessageError()
    {
        Toast toast = Toast.makeText(getApplicationContext(), R.string.empty_message,
                Toast.LENGTH_LONG);
        toast.setGravity(Gravity.CENTER, 0, 0);
        toast.show();
    }

    @Override
    public void clearSendMessageText()
    {
        sendMessageEditText.setText("");
    }

    @Override
    public void showGotennaDisconnectedErrorMessage()
    {
        Toast toast = Toast.makeText(getApplicationContext(), R.string.gotenna_disconnected,
                Toast.LENGTH_LONG);
        toast.setGravity(Gravity.CENTER, 0, 0);
        toast.show();
    }

    @Override
    public void showMessages(List<MessageViewModel> messages)
    {
        if (messagesArrayAdapter == null)
        {
            this.messages = new ArrayList<>();
            this.messages.addAll(messages);

            messagesArrayAdapter = new MessagesArrayAdapter(this, this.messages);
            messagesArrayAdapter.setWillDisplayAckConfirmation(false);
            messagesListView.setAdapter(messagesArrayAdapter);
        }
        else
        {
            this.messages.clear();
            this.messages.addAll(messages);
            messagesArrayAdapter.notifyDataSetChanged();
        }
    }
}
