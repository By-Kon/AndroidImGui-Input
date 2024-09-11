package com.sak.imgui_input;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;

import com.sak.imgui_input.FloatingWindow.FloatWinService;
import com.sak.imgui_input.databinding.ActivityMainBinding;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("ImGui");
    }

    private static MainActivity instance;

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        FloatWinService.showFloat(MainActivity.this);
        RunFloat();
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        if (event.getAction() == KeyEvent.ACTION_DOWN) {
            // 打印键盘事件的 Unicode 字符
            Log.d("字符：", String.valueOf(event.getUnicodeChar(event.getMetaState())));
        }
        // 返回父类方法的结果，确保事件继续分发
        return super.dispatchKeyEvent(event);
    }

    private void RunFloat()
    {
        new Thread(new Runnable() {
            @Override
            public void run() {

                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }


                    NativeUtils.Start();

            }
        }).start();

    }

    public static MainActivity getInstance() {
        if (instance != null)
            return instance;
        return null;
    }



}