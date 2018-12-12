package com.gotenna.sdk.sample.groups;

import com.gotenna.sdk.data.GTCommandCenter;
import com.gotenna.sdk.data.GTCommandCenter.GTGroupInviteErrorListener;
import com.gotenna.sdk.data.GTCommandCenter.GTGroupInviteResponseListener;
import com.gotenna.sdk.data.GTError;
import com.gotenna.sdk.data.GTResponse;
import com.gotenna.sdk.data.GTResponse.GTCommandResponseCode;
import com.gotenna.sdk.data.user.User;
import com.gotenna.sdk.data.user.UserDataStore;
import com.gotenna.sdk.exceptions.GTDataMissingException;
import com.gotenna.sdk.sample.groups.GroupInvitationViewModel.GroupInvitationState;
import com.gotenna.sdk.sample.managers.ContactsManager;
import com.gotenna.sdk.sample.models.Contact;

import java.util.ArrayList;
import java.util.List;

/**
 * A presenter for {@link CreateGroupActivity}.
 * <p>
 * Created on: 7/12/17.
 *
 * @author Thomas Colligan
 */

class CreateGroupPresenter implements GTGroupInviteResponseListener, GTGroupInviteErrorListener
{
    //==============================================================================================
    // Class Properties
    //==============================================================================================

    private CreateGroupView view;
    private GroupCreationState groupCreationState;
    private final List<Long> groupMembersGidList;
    private final List<GroupInvitationViewModel> groupInvitationViewModelList;
    private long selectedGroupGID;

    private final ContactsManager contactsManager;
    private final UserDataStore userDataStore;
    private final GTCommandCenter gtCommandCenter;

    enum GroupCreationState
    {
        NO_GROUPS_DETECTED,
        GROUPS_DETECTED,
        GROUP_SELECTED
    }

    //==============================================================================================
    // Constructor
    //==============================================================================================

    CreateGroupPresenter()
    {
        contactsManager = ContactsManager.getInstance();
        userDataStore = UserDataStore.getInstance();
        gtCommandCenter = GTCommandCenter.getInstance();

        groupInvitationViewModelList = new ArrayList<>();
        groupMembersGidList = new ArrayList<>();
        groupMembersGidList.addAll(createGroupMemberList());
    }

    //==============================================================================================
    // Class Instance Methods
    //==============================================================================================

    void attachView(CreateGroupView view)
    {
        this.view = view;
    }

    void detachView()
    {
        this.view = null;
    }

    private List<Long> createGroupMemberList()
    {
        // Everyone, including the current user, is a group member.
        List<Long> gidList = new ArrayList<>();
        List<Contact> allContactsList = contactsManager.getAllDemoContacts();

        for (Contact contact : allContactsList)
        {
            gidList.add(contact.getGid());
        }

        return gidList;
    }

    private GroupCreationState determineGroupCreationState()
    {
        GroupCreationState groupCreationState = GroupCreationState.NO_GROUPS_DETECTED;
        User currentUser = userDataStore.getCurrentUser();

        if (currentUser != null)
        {
            List<Long> groupGIDs = currentUser.getGroupGIDs();

            if (groupGIDs.size() > 0)
            {
                groupCreationState = GroupCreationState.GROUPS_DETECTED;
            }
        }

        if (selectedGroupGID != 0)
        {
            groupCreationState = GroupCreationState.GROUP_SELECTED;
        }

        return groupCreationState;
    }

    private List<GroupInvitationViewModel> createGroupInvitationViewModels()
    {
        List<GroupInvitationViewModel> viewModels = new ArrayList<>();
        User currentUser = userDataStore.getCurrentUser();
        List<Contact> allContactsList = contactsManager.getAllDemoContacts();

        for (Contact contact : allContactsList)
        {
            long contactGID = contact.getGid();

            if (contactGID != currentUser.getGID())
            {
                viewModels.add(new GroupInvitationViewModel(contact,
                        GroupInvitationState.SENDING));
            }
        }

        return viewModels;
    }

    private void updateGroupMemberInvitationState(long memberGID, GroupInvitationState groupInvitationState)
    {
        for (GroupInvitationViewModel groupInvitation : groupInvitationViewModelList)
        {
            if (groupInvitation.getContact().getGid() == memberGID)
            {
                groupInvitation.setGroupInvitationState(groupInvitationState);
                break;
            }
        }
    }

    //==============================================================================================
    // Presenter Action Methods
    //==============================================================================================

    void onCreate()
    {
        groupCreationState = determineGroupCreationState();
        view.showGroupStateUi(groupCreationState, selectedGroupGID);
    }

    void onCreateGroup()
    {
        User currentUser = userDataStore.getCurrentUser();

        if (currentUser == null)
        {
            view.showMustSelectUserFirstErrorMessage();
            view.showSelectGidScreen();
            return;
        }

        groupInvitationViewModelList.clear();
        groupInvitationViewModelList.addAll(createGroupInvitationViewModels());

        try
        {
            // Send out all of the group invites via the goTenna
            selectedGroupGID = gtCommandCenter.createGroupWithGIDs(groupMembersGidList, this, this);

            groupCreationState = determineGroupCreationState();
            view.showGroupStateUi(groupCreationState, selectedGroupGID);
            view.showGroupInvitations(groupInvitationViewModelList);
        }
        catch (GTDataMissingException e)
        {
            view.showErrorCreatingGroupMessage(e.toString());
        }
    }

    void onSelectGroup()
    {
        User currentUser = userDataStore.getCurrentUser();

        if (currentUser == null)
        {
            view.showMustSelectUserFirstErrorMessage();
            view.showSelectGidScreen();
            return;
        }

        List<Long> groupGIDs = currentUser.getGroupGIDs();
        view.showGroupSelectionDialog(groupGIDs);
    }

    void onGroupSelectionConfirmed(long selectedGroupGID)
    {
        this.selectedGroupGID = selectedGroupGID;
        User currentUser = userDataStore.getCurrentUser();

        // Setup the invites, pretending everyone was already invited
        // We do this because, if we aren't the group creator we have no actual way of knowing
        // who was successfully invited to the group or not.
        List<Contact> allContactsList = contactsManager.getAllDemoContacts();
        groupInvitationViewModelList.clear();

        for (Contact contact : allContactsList)
        {
            if (contact.getGid() != currentUser.getGID())
            {
                groupInvitationViewModelList.add(new GroupInvitationViewModel(contact, GroupInvitationState.RECEIVED));
            }
        }

        groupCreationState = determineGroupCreationState();
        view.showGroupStateUi(groupCreationState, selectedGroupGID);
        view.showGroupInvitations(groupInvitationViewModelList);
    }

    void onResendIndividualGroupInvite(GroupInvitationViewModel groupInvitationViewModel)
    {
        long memberGID = groupInvitationViewModel.getContact().getGid();
        updateGroupMemberInvitationState(memberGID, GroupInvitationState.SENDING);
        view.showGroupInvitations(groupInvitationViewModelList);

        try
        {

            gtCommandCenter.sendIndividualGroupInvite(selectedGroupGID,
                    groupMembersGidList,
                    memberGID,
                    this,
                    this);
        }
        catch (GTDataMissingException e)
        {
            view.showErrorInvitingMemberMessage(memberGID);
        }
    }

    // ================================================================================
    // GTGroupInviteResponseListener Implementation
    // ================================================================================

    @Override
    public void onMemberResponse(GTResponse response, long memberGID)
    {
        if (response.getResponseCode() == GTCommandResponseCode.POSITIVE)
        {
            updateGroupMemberInvitationState(memberGID, GroupInvitationState.RECEIVED);
        }
        else
        {
            updateGroupMemberInvitationState(memberGID, GroupInvitationState.NOT_RECEIVED);
        }

        if (view == null)
            return;

        view.showGroupInvitations(groupInvitationViewModelList);
    }

    // ================================================================================
    // GTGroupInviteErrorListener Implementation
    // ================================================================================

    @Override
    public void onError(GTError error, long memberGID)
    {
        updateGroupMemberInvitationState(memberGID, GroupInvitationState.NOT_RECEIVED);

        if (view == null)
            return;

        view.showGroupInvitations(groupInvitationViewModelList);
        view.showErrorInvitingMemberMessage(memberGID);
    }

    //==============================================================================================
    // CreateGroupView Interface
    //==============================================================================================

    interface CreateGroupView
    {
        void showGroupStateUi(GroupCreationState groupCreationState, long selectedGroupGID);

        void showGroupInvitations(List<GroupInvitationViewModel> groupInvitationViewModels);

        void showMustSelectUserFirstErrorMessage();

        void showSelectGidScreen();

        void showErrorCreatingGroupMessage(String errorMessage);

        void showErrorInvitingMemberMessage(long memberGID);

        void showGroupSelectionDialog(final List<Long> groupGIDs);
    }
}
