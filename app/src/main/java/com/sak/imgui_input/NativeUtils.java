package com.sak.imgui_input;

import android.content.res.AssetManager;
import android.view.Surface;

public class NativeUtils {
    public static native void Start();
    public static native void SurfaceCreate(Surface surface,int width, int height);
    public static native void SurfaceChanged( int width, int height);
    public static native ImGuiWindowData[] GetImGuiWinSize();
    public static native void MotionEventClick(int Event_getAction, float PosX, float PosY);
    public static native void UpdateInputText(String text);
    public static native void DeleteInputText();
    public static native void LoadFontFrom(AssetManager assetManager);
}
