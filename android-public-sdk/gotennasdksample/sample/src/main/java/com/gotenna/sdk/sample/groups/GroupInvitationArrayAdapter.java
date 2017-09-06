package com.gotenna.sdk.sample.groups;

import android.app.Activity;
import android.content.Context;
import android.support.annotation.NonNull;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.TextView;

import com.gotenna.sdk.sample.R;

import java.util.List;

/**
 * Adapter for displaying group invitations in {@link CreateGroupActivity}.
 *
 * Created on 2/19/16
 *
 * @author ThomasColligan
 */
class GroupInvitationArrayAdapter extends ArrayAdapter<GroupInvitationViewModel>
{
    //==============================================================================================
    // Class Properties
    //==============================================================================================

    private static final int layoutResourceId = R.layout.cell_group_invite;
    private List<GroupInvitationViewModel> dataList;
    private ResendInviteListener resendInviteListener;

    //==============================================================================================
    // Constructor
    //==============================================================================================

    GroupInvitationArrayAdapter(Context context, List<GroupInvitationViewModel> dataList,
                                ResendInviteListener resendInviteListener)
    {
        super(context, layoutResourceId, dataList);
        this.dataList = dataList;
        this.resendInviteListener = resendInviteListener;
    }

    //==============================================================================================
    // Overridden ArrayAdapter Methods
    //==============================================================================================

    @NonNull
    @Override
    public View getView(int position, View convertView, @NonNull ViewGroup parent)
    {
        View row = convertView;
        GroupInvitationCell cell = null;

        if (row == null)
        {
            LayoutInflater inflater = ((Activity) getContext()).getLayoutInflater();
            row = inflater.inflate(layoutResourceId, parent, false);

            cell = new GroupInvitationCell();
            cell.contactNameTextView = (TextView) row.findViewById(R.id.contactNameTextView);
            cell.inviteStatusTextView = (TextView) row.findViewById(R.id.inviteStatusTextView );
            cell.resendInviteButton = (Button) row.findViewById(R.id.resendInviteButton);

            row.setTag(cell);
        }
        else
        {
            cell = (GroupInvitationCell) row.getTag();
        }

        // Update the cell UI
        final GroupInvitationViewModel viewModel = dataList.get(position);

        cell.contactNameTextView.setText(viewModel.getContactName());

        switch (viewModel.getGroupInvitationState())
        {
            case SENDING:
            {
                cell.inviteStatusTextView.setText(getContext().getString(R.string.group_invite_state_sending));
                cell.resendInviteButton.setVisibility(View.GONE);
            }
                break;

            case RECEIVED:
            {
                cell.inviteStatusTextView.setText(getContext().getString(R.string.group_invite_state_received));
                cell.resendInviteButton.setVisibility(View.VISIBLE);
            }
                break;

            case NOT_RECEIVED:
            {
                cell.inviteStatusTextView.setText(getContext().getString(R.string.group_invite_state_not_received));
                cell.resendInviteButton.setVisibility(View.VISIBLE);
            }
                break;
        }

        cell.resendInviteButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if (resendInviteListener != null)
                {
                    resendInviteListener.onResendInviteButtonClicked(viewModel);
                }
            }
        });

        return row;
    }

    @Override
    public int getCount()
    {
        return dataList.size();
    }

    //==============================================================================================
    // GroupInvitationCell Class
    //==============================================================================================

    private static class GroupInvitationCell
    {
        TextView contactNameTextView;
        TextView inviteStatusTextView;
        Button resendInviteButton;
    }

    //==============================================================================================
    // ResendInviteListener Interface
    //==============================================================================================

    interface ResendInviteListener
    {
        void onResendInviteButtonClicked(GroupInvitationViewModel groupInvitationClicked);
    }
}
