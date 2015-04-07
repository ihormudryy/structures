package com.structures.unittests;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import com.structures.unittests.R;
import android.test.AndroidTestCase;
import android.test.InstrumentationTestRunner;
import android.util.Log;
import java.util.List;
import java.util.ArrayList;
import java.io.*;

public class RunUnittests extends Activity {
    static
    {
        System.loadLibrary("gnustl_shared");
        System.loadLibrary("unittests");
    }

    private native boolean runTests(String appPath, String logFile, String[] args);
    private native String stringFromJNI(String appPath, String logFile, String[] args);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_run_unittests);
        
        File f = getBaseContext().getFilesDir();
        String abs_path = f.getAbsolutePath();
        String appName = "unittests";
        String outArg = "--gtest_output=xml:"+abs_path+"/out.xml";
        List<String> argList = new ArrayList<String>();
        argList.add("unittests");
        argList.add(outArg);
        String[] args = argList.toArray(new String[argList.size()]);
        String logFile = "/out.xml";
        long ts = System.currentTimeMillis();
        
        boolean success = runTests(abs_path, logFile, args);

        Log.d("structures UnitTests", "Testing done, output in "+abs_path+"/out.xml"); 
        TextView textview = new TextView(this);
        
        if (!success) textview.append("FUCKED UP\n");

        textview.append(appName + " ---BEGIN NATIVE TEST LOG " + ts + " ---\n");
        setContentView(textview);        
        try {
            Log.i("unittests", "---BEGIN NATIVE TEST LOG " + ts + " ---");
            BufferedReader br = new BufferedReader(new FileReader(new File("/data/user/10/com.structures.unittests/files/example.txt")));
            String line;
            while ((line = br.readLine()) != null) {
                Log.i("unittests", line);
                textview.append(line + "\n");
            }
            br.close();
            Log.i("unittests", "---END NATIVE TEST LOG " + ts + " ---");
        } catch (Exception e) {
            Log.e("unittests", "Failed to read logfile: " + e.getMessage());
            textview.append("Failed to read logfile: " + e.getMessage() + "\n");
        } 
        
        textview.append(abs_path + " ---END NATIVE TEST LOG " + ts + " ---" + "\n");
        setContentView(textview);  
    }
}