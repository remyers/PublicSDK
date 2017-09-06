package com.gotenna.sdk.sample.gid;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.gotenna.sdk.sample.ContactViewModel;
import com.gotenna.sdk.sample.R;

import java.util.List;

/**
 * A screen that allows the user to select which sample user they want to be, and set that user's
 * GID onto the goTenna.
 * <p>
 * Created on: 7/12/17.
 *
 * @author Thomas Colligan
 */

public class SetGidActivity extends AppCompatActivity implements SetGidPresenter.SetGidView
{
    //==============================================================================================
    // Class Properties
    //==============================================================================================

    private static final String KEY_HAS_DONE_TOOLBAR = "HAS_DONE_TOOLBAR";
    private SetGidPresenter presenter;
    private boolean hasDoneToolbar;
    private TextView usernameTextView;
    private TextView gidTextView;

    //==============================================================================================
    // Static Methods
    //==============================================================================================

    public static void start(Context context)
    {
        Intent starter = new Intent(context, SetGidActivity.class);
        context.startActivity(starter);
    }

    public static void startWithDoneToolbar(Context context)
    {
        Intent starter = new Intent(context, SetGidActivity.class);
        starter.putExtra(KEY_HAS_DONE_TOOLBAR, true);
        context.startActivity(starter);
    }

    //==============================================================================================
    // Life-Cycle Methods
    //==============================================================================================

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_set_gid);

        usernameTextView = (TextView) findViewById(R.id.usernameTextView);
        gidTextView = (TextView) findViewById(R.id.gidTextView);

        presenter = new SetGidPresenter();
        presenter.attachView(this);
        presenter.onCreate();

        hasDoneToolbar = getIntent().getBooleanExtra(KEY_HAS_DONE_TOOLBAR, false);

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null)
        {
            actionBar.setDisplayHomeAsUpEnabled(!hasDoneToolbar);
        }

        if (hasDoneToolbar)
        {
            findViewById(R.id.setGidButton).setVisibility(View.GONE);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        MenuInflater inflater = getMenuInflater();
        if (hasDoneToolbar)
        {
            inflater.inflate(R.menu.done_menu, menu);
        }
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        // Handle action bar actions click
        switch (item.getItemId())
        {
            case android.R.id.home:
                finish();
                return true;
            case R.id.done:
                presenter.onDoneClicked();
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

    public void onChangeUserButtonClicked(View v)
    {
        presenter.onChangeUser();
    }

    public void onSetGidButtonClicked(View v)
    {
        presenter.onSetGid();
    }

    //==============================================================================================
    // SetGidView Implementation
    //==============================================================================================

    @Override
    public void showEmptyUserInfo()
    {
        String noneText = getString(R.string.none);
        usernameTextView.setText(getString(R.string.current_username_text, noneText));
        gidTextView.setText(getString(R.string.current_gid_text, noneText));
    }

    @Override
    public void showUserInfo(String username, long gid)
    {
        usernameTextView.setText(getString(R.string.current_username_text, username));
        gidTextView.setText(getString(R.string.current_gid_text, Long.toString(gid)));
    }

    @Override
    public void showUserSelectionDialog(final List<ContactViewModel> contactViewModels)
    {
        final CharSequence[] choicesArray = new CharSequence[contactViewModels.size()];

        for (int i = 0; i < contactViewModels.size(); i++)
        {
            ContactViewModel viewModel = contactViewModels.get(i);
            choicesArray[i] = viewModel.getContactInfoText();
        }

        new AlertDialog.Builder(this)
                .setTitle(R.string.select_user_dialog_title)
                .setSingleChoiceItems(choicesArray, -1, new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialog, int which)
                    {
                        ContactViewModel selectedContactViewMoedl = contactViewModels.get(which);
                        presenter.onUserSelected(selectedContactViewMoedl);
                        dialog.cancel();
                    }
                })
                .show();
    }

    @Override
    public void showSetGidSuccessMessage()
    {
        Toast.makeText(getApplicationContext(), R.string.set_gid_success_toast_text, Toast.LENGTH_LONG).show();
    }

    @Override
    public void showSetGidFailureMessage()
    {
        Toast.makeText(getApplicationContext(), R.string.error_occurred, Toast.LENGTH_LONG).show();
    }

    @Override
    public void showMustSelectUserMessage()
    {
        Toast.makeText(getApplicationContext(), R.string.must_select_user_warning,
                Toast.LENGTH_LONG).show();
    }
}
