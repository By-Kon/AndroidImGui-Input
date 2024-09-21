package com.sak.imgui_input.FloatingWindow;

import android.graphics.PixelFormat;
import android.os.Build;
import android.view.Gravity;
import android.view.WindowManager;




public class WindowLayoutParas {

    /**
     * 获取悬浮窗的属性参数
     *
     * @param isWindow 是否为可操作的悬浮窗
     * @return 悬浮窗的属性参数
     */
    public static WindowManager.LayoutParams getAttributes(boolean isWindow) {
        WindowManager.LayoutParams params = new WindowManager.LayoutParams();

        // 设置悬浮窗的类型
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            params.type = WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
        } else {
            params.type = WindowManager.LayoutParams.TYPE_PHONE;
        }

        // 设置悬浮窗的标志
        params.flags = WindowManager.LayoutParams.FLAG_FULLSCREEN
                | WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS
                | WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION
                | WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE
                | WindowManager.LayoutParams.FLAG_WATCH_OUTSIDE_TOUCH
                | WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN;

        // 如果是可操作的悬浮窗，添加额外的标志
        if (isWindow) {
            params.flags |= WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL | WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE;
        }

        // 设置悬浮窗的图片格式
        params.format = PixelFormat.RGBA_8888;  // 设置图片格式，效果为背景透明

        // 设置悬浮窗的显示位置
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            params.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
        }
        params.gravity = Gravity.LEFT | Gravity.TOP;  // 调整悬浮窗显示的停靠位置为左侧置顶
        params.x = params.y = 0;
        params.width = params.height = isWindow ? WindowManager.LayoutParams.MATCH_PARENT : 0;

        return params;
    }

    /**
     * 获取悬浮窗的参数
     *
     * @param width  悬浮窗宽度
     * @param height 悬浮窗高度
     * @return 悬浮窗的参数
     */
    public static WindowManager.LayoutParams getParams(int width, int height) {
        // 设置窗口类型
        WindowManager.LayoutParams wmParams = new WindowManager.LayoutParams();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            wmParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;

            // 设置刘海屏适应模式
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
                wmParams.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            }
        } else {
            wmParams.type = WindowManager.LayoutParams.TYPE_PHONE;
        }

        // 设置图片格式
        wmParams.format = PixelFormat.RGBA_8888;  // 设置图片格式，效果为背景透明

        // 设置窗口标志
        wmParams.flags = WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE
                | WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE
                | WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL
                | WindowManager.LayoutParams.FLAG_HARDWARE_ACCELERATED
                | WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN
                | WindowManager.LayoutParams.FLAG_FULLSCREEN;  // 设置浮动窗口不可聚焦，实现操作除浮动窗口外的其他可见窗口的操作

        // 设置悬浮窗显示位置
        wmParams.gravity = Gravity.LEFT | Gravity.TOP;  // 调整悬浮窗显示的停靠位置为左侧置顶
        wmParams.x = 0;
        wmParams.y = 0;

        // 设置悬浮窗大小
        wmParams.width = width;
        wmParams.height = height;

        return wmParams;
    }

}
