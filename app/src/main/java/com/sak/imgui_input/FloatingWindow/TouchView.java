package com.sak.imgui_input.FloatingWindow;

import static android.content.Context.WINDOW_SERVICE;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Handler;
import android.os.RemoteException;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import com.sak.imgui_input.ImGuiWindowData;
import com.sak.imgui_input.NativeUtils;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

/**
 * TouchView 是一个自定义的 View，用于处理触摸事件并定期更新浮动窗口的视图布局。
 * 该类管理视图的添加、更新、移除，并通过 IPC 与后台服务进行通信。
 */
public class TouchView extends View {
    private static final String TAG = "Sak-TouchView";
    private static final int UPDATE_INTERVAL_MS = 800;

    private static WindowManager manager;
    private static View mtouch_View;
    public static WindowManager.LayoutParams mtouch_Params;
    private final Handler handler;
    private static Context con;
    private ImGuiWindowData[] lastWindowData; // 用于缓存上一次的窗口数据

    public TouchView(Context context) {
        super(context);
        mtouch_View = this;
        con = context;
        manager = (WindowManager) getContext().getSystemService(WINDOW_SERVICE);
        handler = new Handler();
    }

    public void initView() {
        mtouch_Params = WindowLayoutParas.getAttributes(false);
        mtouch_Params.token = mtouch_View.getApplicationWindowToken();
        manager.addView(mtouch_View, mtouch_Params);
        startPeriodicUpdates();
    }

    @SuppressLint("ClickableViewAccessibility")
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        // 如果事件没有被处理，直接返回 false
        if (event == null) return false;
        Log.d("触摸事件：", "" + event.getAction());
        NativeUtils.MotionEventClick(event.getAction(), event.getRawX(), event.getRawY());
        return false;
    }

    private void startPeriodicUpdates() {
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                updateWindowData();
                handler.postDelayed(this, UPDATE_INTERVAL_MS);
            }
        }, UPDATE_INTERVAL_MS);
    }

    private void updateWindowData() {
        ImGuiWindowData[] windowData = NativeUtils.GetImGuiWinSize();
        if (windowData != null && !isSameWindowData(windowData)) { // 只有数据不同时才更新
            updateViews(windowData);
            cleanUpViews(windowData);
            lastWindowData = windowData; // 保存当前数据以备下次比较
        }
    }

    private boolean isSameWindowData(ImGuiWindowData[] windowData) {
        if (lastWindowData == null || lastWindowData.length != windowData.length) {
            return false;
        }
        for (int i = 0; i < windowData.length; i++) {
            // 先检查是否为空
            if (windowData[i] == null || lastWindowData[i] == null) {
                return false;
            }
            // 比较具体字段
            if (windowData[i].WinID != lastWindowData[i].WinID ||
                    windowData[i].Pos_X != lastWindowData[i].Pos_X ||
                    windowData[i].Pos_Y != lastWindowData[i].Pos_Y ||
                    windowData[i].Size_X != lastWindowData[i].Size_X ||
                    windowData[i].Size_Y != lastWindowData[i].Size_Y) {
                return false;
            }
        }
        return true;
    }


    private void updateViews(ImGuiWindowData[] windowData) {
        for (ImGuiWindowData data : windowData) {
            if (data != null) {
                mtouch_Params.x = (int) data.Pos_X;
                mtouch_Params.y = (int) data.Pos_Y;
                mtouch_Params.width = (int) data.Size_X;
                mtouch_Params.height = (int) data.Size_Y;

                if (EventClass.ViewList.containsKey(data.WinID)) {
                    if (!data.Action) {
                        mtouch_Params.width = 0;
                        mtouch_Params.height = 0;
                    }
                    updateOrRemoveView(data.WinID);
                } else if (data.WinName != null) {
                    addNewView(data);
                }
            }
        }
    }

    private void addNewView(ImGuiWindowData data) {
        TouchView newTouchView = new TouchView(con);
        EventClass.ViewList.put(data.WinID, newTouchView);
        if (FloatWinService.manager != null) {
            FloatWinService.manager.addView(newTouchView, mtouch_Params);
        }
    }

    private void updateOrRemoveView(int winID) {
        View view = EventClass.ViewList.get(winID);
        if (view != null && FloatWinService.manager != null) {
            FloatWinService.manager.updateViewLayout(view, mtouch_Params);
        }
    }

    private void cleanUpViews(ImGuiWindowData[] windowData) {
        Set<Integer> activeKeys = new HashSet<>();
        for (ImGuiWindowData data : windowData) {
            if (data != null) {
                activeKeys.add(data.WinID);
            }
        }

        Iterator<Map.Entry<Integer, View>> iterator = EventClass.ViewList.entrySet().iterator();
        while (iterator.hasNext()) {
            Map.Entry<Integer, View> entry = iterator.next();
            if (!activeKeys.contains(entry.getKey())) {
                removeView(entry.getValue());
                iterator.remove();
            }
        }
    }

    private void removeView(View view) {
        if (FloatWinService.manager != null) {
            FloatWinService.manager.removeView(view);
        }
        Log.e("TouchView", "Removed view");
    }

    public void destroy() {
        if (handler != null) {
            handler.removeCallbacksAndMessages(null);
        }
        if (manager != null && mtouch_View != null) {
            try {
                manager.removeView(mtouch_View);
            } catch (Exception e) {
                Log.e("TouchView", "Failed to remove view", e);
            }
        }
        mtouch_View = null;
        manager = null;
    }
}

