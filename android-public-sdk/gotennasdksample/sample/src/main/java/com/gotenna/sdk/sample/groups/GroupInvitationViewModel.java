package com.gotenna.sdk.sample.groups;

import com.gotenna.sdk.sample.models.Contact;

/**
 * Created on 2/19/16
 *
 * @author ThomasColligan
 */
class GroupInvitationViewModel
{
    //==============================================================================================
    // Class Properties
    //==============================================================================================

    private Contact contact;
    private GroupInvitationState groupInvitationState;

    enum GroupInvitationState
    {
        SENDING,
        RECEIVED,
        NOT_RECEIVED
    }

    //==============================================================================================
    // Constructor
    //==============================================================================================

    GroupInvitationViewModel(Contact contact, GroupInvitationState groupInvitationState)
    {
        this.contact = contact;
        this.groupInvitationState = groupInvitationState;
    }

    //==============================================================================================
    // Class Instance Methods
    //==============================================================================================

    Contact getContact()
    {
        return contact;
    }

    String getContactName()
    {
        return contact.getName();
    }

    void setGroupInvitationState(GroupInvitationState groupInvitationState)
    {
        this.groupInvitationState = groupInvitationState;
    }

    GroupInvitationState getGroupInvitationState()
    {
        return groupInvitationState;
    }
}
