package com.structures.${target};

import android.os.Bundle;
import android.test.InstrumentationTestRunner;
import android.test.InstrumentationTestSuite;
import android.util.Log;

import junit.framework.TestSuite;

import java.util.List;
import java.util.ArrayList;
import java.io.*;

import com.structures.${target}.test.NativeTester;

public class TestRunner extends InstrumentationTestRunner
{
    static
    {
        System.loadLibrary("gnustl_shared");
    }

    private Bundle createParams = null;

    @Override
    public TestSuite getAllTests()
    {
        InstrumentationTestSuite suite = new InstrumentationTestSuite(this);
        NativeTester.setParams(createParams);
        suite.addTestSuite(NativeTester.class);
        return suite;
    }

    @Override
    public void onCreate(Bundle createParams)
    {
        this.createParams = createParams;
        super.onCreate(createParams);
    }
}