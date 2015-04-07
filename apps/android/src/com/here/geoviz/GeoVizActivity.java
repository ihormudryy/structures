package com.here.geoviz;

import android.app.NativeActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

import java.io.File;

public class GeoVizActivity extends NativeActivity {

    static {
        System.loadLibrary("GeoVizJNI");
    }

    GeoVizView mView;

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        mView = new GeoVizView(this); //getApplication());
        setContentView(mView);
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
}
