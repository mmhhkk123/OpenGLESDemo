package com.example.zhzl.myapp;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.KeyEvent;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class GLES3JNIView extends GLSurfaceView {

    private GLES3JNIRenderer mRenderer;

    public GLES3JNIView(Context context) {
        super(context);

        setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        setEGLContextClientVersion(2);
        this.setFocusableInTouchMode(true);

        mRenderer = new GLES3JNIRenderer();
        setRenderer(mRenderer);
    }

    @Override
    public void onResume() {
        super.onResume();
        this.setRenderMode(RENDERMODE_CONTINUOUSLY);
        // 和渲染线程通信
        this.queueEvent(new Runnable() {
            @Override
            public void run() {
                GLES3JNIView.this.mRenderer.handleOnResume();
            }
        });
    }

    @Override
    public void onPause() {
        this.queueEvent(new Runnable() {
            @Override
            public void run() {
                GLES3JNIView.this.mRenderer.handleOnPause();
            }
        });
        this.setRenderMode(RENDERMODE_WHEN_DIRTY);
    }

    @Override
    public boolean onTouchEvent(final MotionEvent event) {
        // final修饰参数，表示不可变，起常量作用
        final int pointerNumber = event.getPointerCount();
        final int[] ids = new int[pointerNumber];
        final float[] xs = new float[pointerNumber];
        final float[] ys = new float[pointerNumber];

        for (int i = 0; i < pointerNumber; i++) {
            ids[i] = event.getPointerId(i);
            xs[i] = event.getX(i);
            ys[i] = event.getY(i);
        }

        switch (event.getAction() & MotionEvent.ACTION_MASK) {
            case MotionEvent.ACTION_POINTER_DOWN:
                final int indexPointerDown = event.getAction() >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        GLES3JNIView.this.mRenderer.handleActionDown(ids[indexPointerDown], xs[indexPointerDown], ys[indexPointerDown]);
                    }
                });
                break;
            case MotionEvent.ACTION_DOWN:
                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        GLES3JNIView.this.mRenderer.handleActionDown(ids[0], xs[0], ys[0]);
                    }
                });
                break;
            case MotionEvent.ACTION_MOVE:
                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        GLES3JNIView.this.mRenderer.handleActionMove(ids, xs, ys);
                    }
                });
                break;
            case MotionEvent.ACTION_POINTER_UP:
                final int indexPointerUp = event.getAction() >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        GLES3JNIView.this.mRenderer.handleActionUp(ids[indexPointerUp], xs[indexPointerUp], ys[indexPointerUp]);
                    }
                });
                break;
            case MotionEvent.ACTION_UP:
                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        GLES3JNIView.this.mRenderer.handleActionUp(ids[0], xs[0], ys[0]);
                    }
                });
                break;
            case MotionEvent.ACTION_CANCEL:
                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        GLES3JNIView.this.mRenderer.handleActionCancel(ids, xs, ys);
                    }
                });
                break;
        }

        return true;
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
    }

    @Override
    public boolean onKeyDown(final int keyCode, KeyEvent event) {
        switch (keyCode) {
            case KeyEvent.KEYCODE_BACK:
            case KeyEvent.KEYCODE_MENU:
            case KeyEvent.KEYCODE_DPAD_LEFT:
            case KeyEvent.KEYCODE_DPAD_RIGHT:
            case KeyEvent.KEYCODE_DPAD_UP:
            case KeyEvent.KEYCODE_DPAD_DOWN:
            case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE:
            case KeyEvent.KEYCODE_DPAD_CENTER:
                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        GLES3JNIView.this.mRenderer.handleKeyDown(keyCode);
                    }
                });
                return true;
            default:
                return super.onKeyDown(keyCode, event);
        }
    }

    @Override
    public boolean onKeyUp(final int keyCode, KeyEvent event) {
        switch (keyCode) {
            case KeyEvent.KEYCODE_BACK:
            case KeyEvent.KEYCODE_MENU:
            case KeyEvent.KEYCODE_DPAD_LEFT:
            case KeyEvent.KEYCODE_DPAD_RIGHT:
            case KeyEvent.KEYCODE_DPAD_UP:
            case KeyEvent.KEYCODE_DPAD_DOWN:
            case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE:
            case KeyEvent.KEYCODE_DPAD_CENTER:
                this.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        GLES3JNIView.this.mRenderer.handleKeyUp(keyCode);
                    }
                });
                return true;
            default:
                return super.onKeyUp(keyCode, event);
        }
    }
}
