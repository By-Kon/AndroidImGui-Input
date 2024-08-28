package com.sak.imgui_input;

import android.view.Surface;

public class NativeUtils {
    public static native void Start();
    public static native void surfaceCreate(Surface surface);
    public static native ImGuiWindowData[] GetImGuiWinSize();
    public static native void MotionEventClick(int Event_getAction, float PosX, float PosY);
    public static native void UpdateInputText(String text);
    public static native void SetUUID(String UUID);
    public static native void SetPassword(String password);
    public static native void StartImGui( int width, int height);
}
