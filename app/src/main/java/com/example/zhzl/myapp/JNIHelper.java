package com.example.zhzl.myapp;

import android.app.Activity;
import android.os.Environment;

import java.io.File;
import java.io.FilenameFilter;

public class JNIHelper {

    private static Activity sActivety = null;
    private static boolean sInited = false;
    private static String sAssetsPath = "";
    private static String sPackageName = "";

    public static void init(final Activity activity) {
        JNIHelper.sActivety = activity;
        if (!sInited) {
            JNIHelper.sPackageName = activity.getApplicationInfo().packageName;
            JNIHelper.nativeSetApkPath(JNIHelper.getAssetsPath());
            sInited = true;
        }
    }

    private static String getAssetsPath() {
        if (JNIHelper.sAssetsPath.equals("")) {
            String pathToOBB = Environment.getExternalStorageDirectory().getAbsolutePath() + "/Android/obb/" + JNIHelper.sPackageName;
            String[] fileNames = new File(pathToOBB).list(new FilenameFilter() {
                @Override
                public boolean accept(File dir, String name) {
                    return name.startsWith("main.") && name.endsWith(".obb");
                }
            });
            String fullPathToOBB = "";
            if (fileNames != null && fileNames.length > 0)
                fullPathToOBB = pathToOBB + "/" + fileNames[0];
            File obbFile = new File(fullPathToOBB);
            if (obbFile.exists())
                JNIHelper.sAssetsPath = fullPathToOBB;
            else
                JNIHelper.sAssetsPath = JNIHelper.sActivety.getApplicationInfo().sourceDir;
        }
        return JNIHelper.sAssetsPath;
    }

    private static native void nativeSetApkPath(final String pApkPath);
}
