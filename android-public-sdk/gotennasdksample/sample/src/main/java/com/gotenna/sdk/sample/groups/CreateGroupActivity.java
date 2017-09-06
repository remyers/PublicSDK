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
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.gotenna.sdk.sample.R;
import com.gotenna.sdk.sample.gid.SetGidActivity;
import com.gotenna.sdk.sample.groups.CreateGroupPresenter.CreateGroupView;
import com.gotenna.sdk.sample.groups.CreateGroupPresenter.GroupCreationState;
import com.gotenna.sdk.sample.groups.GroupInvitationArrayAdapter.ResendInviteListener;

import java.util.ArrayList;
import java.util.List;

/**
 * A screen that allows a user to create a group and send group invitations to those group members.
 * <p>
 * Created on: 7/12/17.
 *
 * @author Thomas Colligan
 */

public class CreateGroupActivity extends AppCompatActivity implements CreateGroupView, ResendInviteListener
{
    //==============================================================================================
    // Class Properties
    //==============================================================================================

    private LinearLayout noGroupDetectedLayout;
    private LinearLayout groupsDetectedLayout;
    private TextView yourGroupGidTextView;
    private ListView groupMembersListView;

    private CreateGroupPresenter presenter;
    private List<GroupInvitationViewModel> groupInvitationViewModels;
    private GroupInvitationArrayAdapter groupInvitationArrayAdapter;

    //==============================================================================================
    // Static Class Methods
    //==============================================================================================

    public static void start(Context context)
    {
        Intent starter = new Intent(context, CreateGroupActivity.class);
        context.startActivity(starter);
    }

    //==============================================================================================
    // Life-cycle Methods
    //==============================================================================================

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create_group);

        noGroupDetectedLayout = (LinearLayout) findViewById(R.id.noGroupDetectedLayout);
        groupsDetectedLayout = (LinearLayout) findViewById(R.id.groupsDetectedLayout);
        yourGroupGidTextView = (TextView) findViewById(R.id.yourGroupGidTextView);
        groupMembersListView = (ListView) findViewById(R.id.groupMembersListView);

        presenter = new CreateGroupPresenter();
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

    public void onCreateGroupButtonClicked(View v)
    {
        presenter.onCreateGroup();
    }

    public void onSelectGroupButtonClicked(View v)
    {
        presenter.onSelectGroup();
    }

    //==============================================================================================
    // ResendInviteListener Implementation
    //==============================================================================================

    @Override
    public void onResendInviteButtonClicked(GroupInvitationViewModel groupInvitationClicked)
    {
        presenter.onResendIndividualGroupInvite(groupInvitationClicked);
    }

    //==============================================================================================
    // CreateGroupView Implementation
    //==============================================================================================

    @Override
    public void showGroupStateUi(GroupCreationState groupCreationState,
                                 long selectedGroupGID)
    {
        switch (groupCreationState)
        {
            case NO_GROUPS_DETECTED:
                noGroupDetectedLayout.setVisibility(View.VISIBLE);
                groupsDetectedLayout.setVisibility(View.GONE);
                yourGroupGidTextView.setVisibility(View.GONE);
                break;
            case GROUPS_DETECTED:
                noGroupDetectedLayout.setVisibility(View.GONE);
                groupsDetectedLayout.setVisibility(View.VISIBLE);
                yourGroupGidTextView.setVisibility(View.GONE);
                break;
            case GROUP_SELECTED:
                noGroupDetectedLayout.setVisibility(View.GONE);
                groupsDetectedLayout.setVisibility(View.GONE);
                yourGroupGidTextView.setVisibility(View.VISIBLE);
                yourGroupGidTextView.setText(getString(R.string.your_group_gid, selectedGroupGID));
                break;
        }
    }

    @Override
    public void showGroupInvitations(List<GroupInvitationViewModel> viewModels)
    {
        if (groupInvitationArrayAdapter == null)
        {
            groupInvitationViewModels = new ArrayList<>();
            groupInvitationViewModels.addAll(viewModels);

            groupInvitationArrayAdapter = new GroupInvitationArrayAdapter(this, groupInvitationViewModels, this);
            groupMembersListView.setAdapter(groupInvitationArrayAdapter);
        }
        else
        {
            groupInvitationViewModels.clear();
            groupInvitationViewModels.addAll(viewModels);

            groupInvitationArrayAdapter.notifyDataSetChanged();
        }
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
    public void showErrorCreatingGroupMessage(String errorMessage)
    {
        Toast toast = Toast.makeText(this, getString(R.string.error_creating_group, errorMessage),
                Toast.LENGTH_SHORT);
        toast.setGravity(Gravity.CENTER, 0, 0);
        toast.show();
    }

    @Override
    public void showErrorInvitingMemberMessage(long memberGID)
    {
        Toast toast = Toast.makeText(this, getString(R.string.error_inviting_member, memberGID),
                Toast.LENGTH_SHORT);
        toast.setGravity(Gravity.CENTER, 0, 0);
        toast.show();
    }

    @Override
    public void showGroupSelectionDialog(final List<Long> groupGIDs)
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
                        presenter.onGroupSelectionConfirmed(selectedGroupGID);
                        dialog.cancel();
                    }
                })
                .show();
    }
}
