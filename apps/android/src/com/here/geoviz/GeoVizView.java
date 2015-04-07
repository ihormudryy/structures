package com.here.geoviz;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

class GeoVizView extends GLSurfaceView {
    public static native void nativeInit(Context context, GLSurfaceView view);
    public static native void nativeResize(int width, int height);
    public static native void nativeStep();

    private static final String TAG = "GeoVizView";
    private static final boolean DEBUG = true;

    public GeoVizView(Context context) {
        super(context);
        // ### FIX: choose the proper configuration
        setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        setEGLContextClientVersion(2);
        setRenderer(new Renderer(this));
    }

    private static class Renderer implements GLSurfaceView.Renderer {
        private GeoVizView mView;

        public Renderer(GeoVizView view) {
            mView = view;
        }

        public void onDrawFrame(GL10 gl) {
            GeoVizView.nativeStep();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            GeoVizView.nativeResize(width, height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            GeoVizView.nativeInit(mView.getContext(), mView);
        }
    }
}
