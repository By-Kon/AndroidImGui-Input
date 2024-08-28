// SakSu.aidl
package com.sak.imgui_input;

parcelable ImGuiWindowData;
interface SakSu {
     int  GetPID();
     void Start();
     void surfaceCreate(in Surface surface);
     void MotionEventClick(int Event_getAction, float PosX, float PosY);
     ImGuiWindowData[] GetImGuiWindowData();
     void SetUUID(String UUID);
     void SetPassword(String Password);
     void StartImGui(int width, int height);

}