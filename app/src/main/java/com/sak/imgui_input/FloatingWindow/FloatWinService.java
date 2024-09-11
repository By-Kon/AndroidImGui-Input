package com.sak.imgui_input.FloatingWindow;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;

import java.util.Iterator;
import java.util.Map;

/**
 * FloatWinService.java: 安卓悬浮窗
 */
public class FloatWinService extends Service {

    private static final String TAG = "FloatWinService";

    private static FloatWinService instance;
    public static WindowManager manager;
    private static View containerView;
    private static WindowManager.LayoutParams containerViewParams;
    private static boolean isContainerViewAdded = false;

    private static DisplayMetrics displayMetrics = new DisplayMetrics();

    public static KeyboardView keyboardView;
    /**
     * 启动悬浮窗服务
     */
    public static void showFloat(Context context) {
        if (instance == null) {
            Intent intent = new Intent(context, FloatWinService.class);
            context.startService(intent);
            Log.d(TAG, "服务启动");
        }
    }

    /**
     * 关闭悬浮窗服务
     */
    public static void hideFloat(Context context) {
        Intent intent = new Intent(context, FloatWinService.class);
        context.stopService(intent);
        removeContainerView();
        if (instance != null) {
            instance.hide();
        }
    }

    @Override
    public void onCreate() {
        super.onCreate();
        instance = this;
        Log.d(TAG, "服务创建");
        initWindowManager();
        setupContainerView();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    /**
     * 隐藏并停止服务
     */
    private void hide() {
        instance = null;
        manager = null;
        stopSelf();
    }

    /**
     * 初始化 WindowManager
     */
    private void initWindowManager() {
        if (manager == null) {
            manager = (WindowManager) getSystemService(WINDOW_SERVICE);
            Log.d(TAG, "初始化 WindowManager");
        }
    }

    /**
     * 移除悬浮窗
     */
    private static void removeContainerView() {
        if (isContainerViewAdded && manager != null) {
            try {
                manager.removeView(containerView);
                Log.d(TAG, "悬浮窗移除成功");
                isContainerViewAdded = false;
            } catch (IllegalArgumentException e) {
                Log.e(TAG, "悬浮窗已被移除: " + e.getMessage());
            }
        }

        Iterator<Map.Entry<Integer, View>> iterator = EventClass.ViewList.entrySet().iterator();
        while (iterator.hasNext()) {
            Map.Entry<Integer, View> entry = iterator.next();
            View view = entry.getValue();
            try {
                if (manager != null) {
                    manager.removeView(view);
                }
                Log.d(TAG, "窗口移除成功");
            } catch (IllegalArgumentException e) {
                Log.e(TAG, "View 已经被移除: " + e.getMessage());
            } catch (NullPointerException e) {
                Log.e(TAG, "WindowManager 或 View 为 null: " + e.getMessage());
            }
            iterator.remove();
        }
        EventClass.ViewList.clear(); // 清空 view 表
    }

    /**
     * 设置悬浮窗
     */
    private static void setupContainerView() {
        manager.getDefaultDisplay().getRealMetrics(displayMetrics);
        if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.R) {
            containerView = new SurfaceViewFloat(instance);
        } else {
            containerView = new TextureViewFloat(instance);
        }

        containerViewParams = WindowLayoutParas.getParams(displayMetrics.widthPixels, displayMetrics.heightPixels);
        if (manager != null) {
            isContainerViewAdded = true;
            manager.addView(containerView, containerViewParams);
        }
    }

    public static void addKeyboardView() {
        Log.d(TAG, "addKeyboardView");
        if (keyboardView == null){
            new Handler(Looper.getMainLooper()).post(() -> keyboardView = new KeyboardView(instance));
        }else {
            new Handler(Looper.getMainLooper()).post(() -> keyboardView.removeView());
        }
    }


    /**
     * 监听屏幕旋转
     */
    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

        if (containerViewParams != null && containerView != null) {
            manager.getDefaultDisplay().getRealMetrics(displayMetrics);
            containerViewParams.width = displayMetrics.widthPixels;
            containerViewParams.height = displayMetrics.heightPixels;
            manager.updateViewLayout(containerView, containerViewParams);
        }

        Log.d(TAG, "屏幕旋转: width=" + displayMetrics.widthPixels + ", height=" + displayMetrics.heightPixels);
    }
}
