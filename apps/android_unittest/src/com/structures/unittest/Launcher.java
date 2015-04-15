package com.here.geoviz.${target};

import android.test.InstrumentationTestRunner;
import android.test.InstrumentationTestSuite;
import android.os.Bundle;
import android.util.Log;

import junit.framework.TestSuite;

import java.util.List;
import java.util.ArrayList;
import java.io.*;

import com.here.geoviz.${target}.test.TestRunner;

public class Launcher extends InstrumentationTestRunner
{
    private Bundle createParams = null;

    @Override
    public TestSuite getAllTests()
    {
        InstrumentationTestSuite suite = new InstrumentationTestSuite(this);
        TestRunner.setParams(createParams);
        suite.addTestSuite(TestRunner.class);
        return suite;
    }

    @Override
    public void onCreate(Bundle createParams)
    {
        this.createParams = createParams;
        super.onCreate(createParams);
    }
}
