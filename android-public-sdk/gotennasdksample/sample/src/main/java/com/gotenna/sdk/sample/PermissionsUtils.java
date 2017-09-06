package com.gotenna.sdk.sample;

import android.Manifest;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Build;
import android.support.v4.content.ContextCompat;

/**
 * Utils class for checking and requesting app permissions.
 * <p>
 * Created on 07/18/2017
 *
 * @author Thomas Colligan
 */
public class PermissionsUtils
{
    //==============================================================================================
    // Constructor
    //==============================================================================================

    private PermissionsUtils()
    {
        // Do nothing here
    }

    //==============================================================================================
    // Permission Checking Methods
    //==============================================================================================

    public static boolean hasLocationPermission()
    {
        Context context = MyApplication.getAppContext();

        return ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_COARSE_LOCATION) == PackageManager.PERMISSION_GRANTED &&
                ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED;
    }

    //==============================================================================================
    // Permission Requesting Methods
    //==============================================================================================

    @TargetApi(Build.VERSION_CODES.M)
    public static void requestLocationPermission(Activity activity, final int REQUEST_PERMISSION_CODE)
    {
        String[] permissionsToRequest = {
                Manifest.permission.ACCESS_COARSE_LOCATION,
                Manifest.permission.ACCESS_FINE_LOCATION

        };
        activity.requestPermissions(permissionsToRequest, REQUEST_PERMISSION_CODE);
    }

}
