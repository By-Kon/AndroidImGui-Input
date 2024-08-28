package com.sak.imgui_input.SuService;

import android.content.Intent;
import android.os.IBinder;
import android.os.Process;
import android.os.RemoteException;
import android.util.Log;
import android.view.Surface;

import com.sak.imgui_input.ImGuiWindowData;
import com.sak.imgui_input.NativeUtils;
import com.sak.imgui_input.SakSu;
import androidx.annotation.NonNull;

import com.topjohnwu.superuser.ipc.RootService;


public class SuperMain extends RootService {
	static {
        Log.d("SuperMain","Sak");
		if (Process.myUid() == 0) {
			System.loadLibrary("ImGui");
	    }
	}

	
    @Override
	public IBinder onBind(@NonNull Intent intent) {
        return new SakSu.Stub() {
            @Override
            public int GetPID() throws RemoteException {
                return 0;
            }

            @Override
            public void Start() throws RemoteException {
                NativeUtils.Start();
            }

            @Override
            public void surfaceCreate(Surface surface) throws RemoteException {
                NativeUtils.surfaceCreate(surface);
            }

            @Override
            public void MotionEventClick(int Event_getAction, float PosX, float PosY) throws RemoteException {
                NativeUtils.MotionEventClick(Event_getAction,PosX,PosY);

            }

            @Override
            public ImGuiWindowData[] GetImGuiWindowData() throws RemoteException {
                return NativeUtils.GetImGuiWinSize();
            }

            @Override
            public void SetUUID(String UUID) throws RemoteException {
                NativeUtils.SetUUID(UUID);

            }

            @Override
            public void SetPassword(String Password) throws RemoteException {
                NativeUtils.SetPassword(Password);

            }

            @Override
            public void StartImGui(int width, int height) throws RemoteException {
                NativeUtils.StartImGui(width,height);
            }
        };
    }
}
