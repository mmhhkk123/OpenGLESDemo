package com.example.zhzl.myapp;

public class GLES3JNILib {
     public static native void init();
     public static native void resize(int width, int height);
     public static native void step();
     public static native void nativeOnPause();
     public static native void nativeOnResume();
     public static native void nativeTouchesBegin(final int id, final float x, final float y);
     public static native void nativeTouchesEnd(final int id, final float x, final float y);
     public static native void nativeTouchesMove(final int[] ids, final float[] xs, final float[] ys);
     public static native void nativeTouchesCancel(final int[] ids, final float[] xs, final float[] ys);
     public static native boolean nativeKeyEvent(final int keyCode,boolean isPressed);
}
