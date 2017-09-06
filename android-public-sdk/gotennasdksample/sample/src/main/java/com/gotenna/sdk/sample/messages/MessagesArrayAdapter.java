package com.gotenna.sdk.sample.messages;

import android.app.Activity;
import android.content.Context;
import android.graphics.drawable.AnimationDrawable;
import android.support.annotation.NonNull;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.gotenna.sdk.sample.R;

import java.util.List;

/**
 * An adapter to display messages in a List.
 *
 * Created on 2/10/16
 *
 * @author ThomasColligan
 */
public class MessagesArrayAdapter extends ArrayAdapter<MessageViewModel>
{
    //==============================================================================================
    // Class Properties
    //==============================================================================================

    private static final int CHAT_MINE_TYPE = 0;
    private static final int CHAT_OTHER_TYPE = 1;
    private static final int TYPE_MAX_COUNT = CHAT_OTHER_TYPE  + 1;

    private boolean willDisplayAckConfirmation;

    //==============================================================================================
    // Constructor
    //==============================================================================================

    public MessagesArrayAdapter(Context context, List<MessageViewModel> viewModelList)
    {
        super(context, R.layout.cell_chat_mine, viewModelList);
    }

    //==============================================================================================
    // Overridden ArrayAdapter Methods
    //==============================================================================================

    @NonNull
    @Override
    public View getView(int position, View convertView, @NonNull ViewGroup parent)
    {
        View row = convertView;
        ChatCell cell;

        int type = getItemViewType(position);

        if (row == null)
        {
            LayoutInflater inflater = ((Activity) getContext()).getLayoutInflater();
            row = inflater.inflate(getLayoutForViewType(type), parent, false);

            cell = new ChatCell();
            cell.cellMessageTextView = (TextView) row.findViewById(R.id.cellMessageTextView);
            cell.cellInfoTextView = (TextView) row.findViewById(R.id.cellInfoTextView);
            cell.messageStatusImageView = (ImageView) row.findViewById(R.id.messageStatusImageView);

            row.setTag(cell);
        }
        else
        {
            cell = (ChatCell) row.getTag();
        }

        final MessageViewModel viewModel = getItem(position);

        if (viewModel != null)
        {
            cell.cellMessageTextView.setText(viewModel.getMessageText());
            cell.cellInfoTextView.setText(viewModel.getCellInfoText());

            if (viewModel.currentUserIsSender())
            {
                switch (viewModel.getMessageStatus())
                {
                    case SENDING:
                        cell.messageStatusImageView.setImageResource(R.drawable.sending_animation);
                        AnimationDrawable animationDrawable = (AnimationDrawable) cell.messageStatusImageView.getDrawable();
                        animationDrawable.start();
                        break;
                    case SENT_SUCCESSFULLY:
                    {
                        if (willDisplayAckConfirmation)
                        {
                            cell.messageStatusImageView.setImageResource(R.drawable.ic_success);
                        }
                        else
                        {
                            cell.messageStatusImageView.setImageResource(R.drawable.ic_clear_square);
                        }
                    }
                        break;
                    case ERROR_SENDING:
                        cell.messageStatusImageView.setImageResource(R.drawable.ic_failed);
                        break;
                }
            }
            else
            {
                cell.messageStatusImageView.setVisibility(View.GONE);
            }
        }

        return row;
    }

    @Override
    public int getViewTypeCount()
    {
        return TYPE_MAX_COUNT;
    }

    @Override
    public int getItemViewType(int position)
    {
        MessageViewModel viewModel = getItem(position);
        return viewModel.messageIsMine() ? CHAT_MINE_TYPE : CHAT_OTHER_TYPE;
    }

    //==============================================================================================
    // Class Instance Methods
    //==============================================================================================

    public void setWillDisplayAckConfirmation(boolean willDisplayAckConfirmation)
    {
        this.willDisplayAckConfirmation = willDisplayAckConfirmation;
    }

    //==============================================================================================
    // Class Helper Methods
    //==============================================================================================

    private static int getLayoutForViewType(int type)
    {
        switch (type)
        {
            case CHAT_MINE_TYPE:
                return R.layout.cell_chat_mine;
            case CHAT_OTHER_TYPE:
                return R.layout.cell_chat_other;
        }

        return -1;
    }

    //==============================================================================================
    // ChatCell Class
    //==============================================================================================

    private static class ChatCell
    {
        TextView cellMessageTextView;
        TextView cellInfoTextView;
        ImageView messageStatusImageView;
    }
}
