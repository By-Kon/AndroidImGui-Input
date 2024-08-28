package com.sak.imgui_input.SuService;

import android.annotation.SuppressLint;
import android.content.ComponentName;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.util.Log;

import com.sak.imgui_input.SakSu;


public class AIDLConnection implements ServiceConnection {
    private static String TGA = "Sak-AIDLConnection";
    public static SakSu iTestService;
    private final boolean isDaemon;

    public AIDLConnection(boolean b) {
         isDaemon = b;
    }

    @SuppressLint("SuspiciousIndentation")
    @Override
    public void onServiceConnected(ComponentName name, IBinder service) {
        Log.d(TGA,String.valueOf(service));
        iTestService = SakSu.Stub.asInterface(service);
	    IPCService.InItIPC(iTestService);
        Log.d("Shocker", "Connected");
    }

    @Override
    public void onServiceDisconnected(ComponentName componentName) {
        Log.d("Shocker", "Disconnected");
    }  
	
}
