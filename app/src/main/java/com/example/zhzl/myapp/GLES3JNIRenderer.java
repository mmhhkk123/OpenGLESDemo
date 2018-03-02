package com.example.zhzl.myapp;

import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;

import java.util.Date;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLES3JNIRenderer implements Renderer {

    private final static long NANOSECONDSPERSECOND = 1000000000L;
    private final static long NANOSECONDSPERMICROSECOND = 1000000L;

    private static long sAnimationInterval = (long)(1.0 / 60 * GLES3JNIRenderer.NANOSECONDSPERSECOND);

    private long mLastTickInNanoSeconds;
    private boolean mNativeInitCompleted = false;

    // 设置帧率
    public static void setsAnimationInterval(float interval) {
        sAnimationInterval = (long)(interval * GLES3JNIRenderer.NANOSECONDSPERSECOND);
    }

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        GLES3JNILib.init();
        mNativeInitCompleted = true;
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        GLES3JNILib.resize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        // 限定最大帧率为60
        if (GLES3JNIRenderer.sAnimationInterval <= 1.0 / 60 * GLES3JNIRenderer.NANOSECONDSPERSECOND) {
            GLES3JNILib.step();
        } else {
            final long now = System.nanoTime();
            final long interval = now - this.mLastTickInNanoSeconds;
            if (interval < GLES3JNIRenderer.sAnimationInterval) {
                try {
                    Thread.sleep((GLES3JNIRenderer.sAnimationInterval - interval) / GLES3JNIRenderer.NANOSECONDSPERMICROSECOND);
                } catch (final Exception e) {
                }
            }
            // 渲染时间必须计算进去，否则比指定帧率慢
            this.mLastTickInNanoSeconds = System.nanoTime();
            GLES3JNILib.step();
        }
    }

    // ===========================================================
    // Methods
    // ===========================================================

    public void handleOnResume() {
        GLES3JNILib.nativeOnResume();
    }

    public void handleOnPause() {
        // 防止onSurfaceCreated之前调用
        if (!mNativeInitCompleted)
            return;
        GLES3JNILib.nativeOnPause();
    }

    public void handleActionDown(final int id, final float x, final float y) {
        GLES3JNILib.nativeTouchesBegin(id, x, y);
    }

    public void handleActionUp(final int id, final float x, final float y) {
        GLES3JNILib.nativeTouchesEnd(id, x, y);
    }

    public void handleActionCancel(final int[] ids, final float[] xs, final float[] ys) {
        GLES3JNILib.nativeTouchesCancel(ids, xs, ys);
    }

    public void handleActionMove(final int[] ids, final float[] xs, final float[] ys) {
        GLES3JNILib.nativeTouchesMove(ids, xs, ys);
    }

    public void handleKeyDown(final int keyCode) {
        GLES3JNILib.nativeKeyEvent(keyCode, true);
    }

    public void handleKeyUp(final int keyCode) {
        GLES3JNILib.nativeKeyEvent(keyCode, false);
    }
}
