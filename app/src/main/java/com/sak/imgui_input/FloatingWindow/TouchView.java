package com.sak.imgui_input.FloatingWindow;

import static android.content.Context.WINDOW_SERVICE;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Handler;
import android.os.RemoteException;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;

import com.sak.imgui_input.ImGuiWindowData;
import com.sak.imgui_input.MainActivity;
import com.sak.imgui_input.SuService.IPCService;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
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

    /**
     * 构造方法，初始化 TouchView 并设置必要的参数。
     *
     * @param context 上下文对象
     */
    public TouchView(Context context) {
        super(context);
        mtouch_View = this;
        con = context;
        manager = (WindowManager) getContext().getSystemService(WINDOW_SERVICE);
        handler = new Handler();
    }

    /**
     * 初始化视图，设置布局参数并将视图添加到窗口管理器。
     */
    public void initView() {
        mtouch_Params = WindowLayoutParas.getAttributes(false);
        mtouch_Params.token = mtouch_View.getApplicationWindowToken();
        manager.addView(mtouch_View, mtouch_Params);

        // 启动定期更新任务
        startPeriodicUpdates();
    }

    /**
     * 处理触摸事件并将触摸信息发送到 IPC 服务。
     *
     * @param event 触摸事件对象
     * @return 如果事件被处理返回 true，否则返回 false
     */
    @SuppressLint("ClickableViewAccessibility")
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        try {
            IPCService.GetIPC().MotionEventClick(event.getAction(), event.getRawX(), event.getRawY());
        } catch (RemoteException e) {
            Log.e("TouchView", "Failed to send MotionEvent", e);
        }
        return false;
    }

    /**
     * 启动定期更新任务，用于获取和更新窗口数据。
     */
    private void startPeriodicUpdates() {
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                updateWindowData();
                handler.postDelayed(this, UPDATE_INTERVAL_MS);
            }
        }, UPDATE_INTERVAL_MS);
    }

    /**
     * 从 IPC 服务获取窗口数据并更新视图。
     */
    private void updateWindowData() {
        ImGuiWindowData[] windowData;
        try {
            windowData = IPCService.GetIPC().GetImGuiWindowData();
        } catch (RemoteException e) {
            Log.e("TouchView", "Failed to get window data", e);
            return;  // 如果数据获取失败，则退出
        }

        if (windowData != null) {
            updateViews(windowData);
            cleanUpViews(windowData);
        }
    }

    /**
     * 根据窗口数据更新视图。
     *
     * @param windowData 窗口数据数组
     */
    private void updateViews(ImGuiWindowData[] windowData) {
        Set<Integer> activeKeys = new HashSet<>();
        for (ImGuiWindowData data : windowData) {
            if (data != null) {
                Log.d(TAG, String.valueOf(data.WinID));
                Log.d(TAG, String.valueOf(data.WinName));
                activeKeys.add(data.WinID);
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

    /**
     * 根据窗口数据添加新的视图。
     *
     * @param data 窗口数据对象
     */
    private void addNewView(ImGuiWindowData data) {
        TouchView newTouchView = new TouchView(con);
        EventClass.ViewList.put(data.WinID, newTouchView);
        if (FloatWinService.manager != null) {
            FloatWinService.manager.addView(newTouchView, mtouch_Params);
        }
    }

    /**
     * 更新或移除已有的视图。
     *
     * @param winID 窗口 ID
     */
    private void updateOrRemoveView(int winID) {
        View view = EventClass.ViewList.get(winID);
        if (view != null && FloatWinService.manager != null) {
            FloatWinService.manager.updateViewLayout(view, mtouch_Params);
        }
    }

    /**
     * 清理不再使用的视图。
     *
     * @param windowData 窗口数据数组
     */
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

    /**
     * 移除视图并从窗口管理器中删除。
     *
     * @param view 要移除的视图
     */
    private void removeView(View view) {
        if (FloatWinService.manager != null) {
            FloatWinService.manager.removeView(view);
        }
        Log.e("TouchView", "Removed view");
    }

    /**
     * 销毁当前视图，并清理相关资源。
     */
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
