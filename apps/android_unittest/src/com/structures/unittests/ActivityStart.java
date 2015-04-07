package com.structures.unittests;

import android.app.NativeActivity;
import android.os.Bundle;
import android.util.Log;

import com.structures.unittests.test.NativeTester;

public class ActivityStart extends NativeActivity
{
    static
    {
        System.loadLibrary("gnustl_shared");
    }

    private Bundle createParams = null;

    @Override
    public void onCreate(Bundle createParams)
    {
        this.createParams = createParams;
        super.onCreate(createParams);
        //NativeTester.setParams(createParams);
        //NativeTester.runTests("app", "log");
    }
}