package com.here.geoviz.${target}.test;

import android.test.AndroidTestCase;
import android.util.Log;
import android.os.Bundle;

import java.util.List;
import java.util.ArrayList;
import java.io.*;

public class TestRunner extends AndroidTestCase
{
    static
    {
        System.loadLibrary("gnustl_shared");
        System.loadLibrary("${target}");
    }

    public static Bundle createParams = null;

    private native boolean runTests(String appPath, String logFile, String[] args);

    static public void setParams(Bundle params)
    {
        createParams = params;
    }

    public void testNative()
    {
        long ts = System.currentTimeMillis();
        File f = getContext().getFilesDir();
        String appName = "${target}";
        String outArg = "--gtest_output=xml:" + f.getAbsolutePath() + "/out.xml";

        List<String> argList = new ArrayList<String>();
        argList.add("${target}");
        argList.add(outArg);

        if (createParams != null) {
            for (String key : createParams.keySet()) {
                argList.add(key);
                Object value = createParams.get(key);
                if (value != null)
                    argList.add(value.toString());
            }
        }

        String[] args = argList.toArray(new String[argList.size()]);

        String logFile = f.getAbsolutePath() + "/output";

        boolean success = runTests(f.getAbsolutePath(), logFile, args);

        Log.d("${target}", "Testing done, output in " + f.getAbsolutePath() + "/out.xml");

        try {
            Log.i("${target}", "---BEGIN NATIVE TEST LOG " + ts + " ---");
            BufferedReader br = new BufferedReader(new FileReader(new File(logFile)));
            String line;
            while ((line = br.readLine()) != null) {
                Log.i("${target}", line);
            }
            br.close();
            Log.i("${target}", "---END NATIVE TEST LOG " + ts + " ---");
        } catch (Exception e) {
            Log.e("${target}", "Failed to read logfile: " + e.getMessage());
        }

        assertTrue(success);
    }
}