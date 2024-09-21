package com.sak.imgui_input;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.provider.Settings;
import android.widget.Toast;

import com.sak.imgui_input.FloatingWindow.FloatWinService;
import com.sak.imgui_input.databinding.ActivityMainBinding;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("ImGui");
    }

    private static MainActivity instance;
    private static Context context;
    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        instance = this;
        context = this;
        // 申请悬浮窗权限
        if (Settings.canDrawOverlays(this)) {
            FloatWinService.showFloat(this);
            runFloat();
        } else {
            requestOverlayPermission();
        }
    }

    private void runFloat() {
        new Thread(() -> {
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            NativeUtils.Start();
        }).start();

        NativeUtils.InitAssetManager(getAssets());
    }

    private void requestOverlayPermission() {
        Toast.makeText(this, "请允许悬浮窗权限", Toast.LENGTH_LONG).show();
        Intent intent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION);
        startActivity(intent);
    }

    public static MainActivity getInstance() {
        return instance;
    }
}
