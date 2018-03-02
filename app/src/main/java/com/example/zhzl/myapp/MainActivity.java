package com.example.zhzl.myapp;

import android.app.Activity;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;

public class MainActivity extends Activity {

    private final static String TAG = MainActivity.class.getSimpleName();

    private GLES3JNIView mView;

    protected void onLoadNativeLibraries() {
        try {
            ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
            Bundle bundle = ai.metaData;
            String libName = bundle.getString("android.app.lib_name");
            System.loadLibrary(libName);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);

        if (!isTaskRoot())
        {
            finish();
            Log.w(TAG, "[Workaround] Ignore the activity started from icon!");
        }

        onLoadNativeLibraries();

        JNIHelper.init(this);

        mView = new GLES3JNIView(getApplication());
        setContentView(mView);

        Window window = this.getWindow();
        window.setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_ADJUST_PAN);
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
