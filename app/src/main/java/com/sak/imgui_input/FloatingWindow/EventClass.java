package com.sak.imgui_input.FloatingWindow;

import android.content.Context;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;

import java.util.HashMap;
import java.util.Map;

public class EventClass {

    public static WindowManager.LayoutParams mtouchParams;
    public static Map<Integer, View> ViewList;
    public static InputMethodManager manager;

    //初始化
    public static void Init(Context con) {
        Log.e("EventClass", "EventClass");
        ViewList = new HashMap<>();//创建view表
        mtouchParams = TouchView.mtouch_Params;

    }
}
