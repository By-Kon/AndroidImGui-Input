package com.sak.imgui_input;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.RemoteException;
import android.widget.Toast;

import com.sak.imgui_input.FloatingWindow.FloatWinService;
import com.sak.imgui_input.SuService.AIDLConnection;
import com.sak.imgui_input.SuService.IPCService;
import com.sak.imgui_input.SuService.SuperMain;
import com.sak.imgui_input.databinding.ActivityMainBinding;
import com.topjohnwu.superuser.ipc.RootService;

import java.io.OutputStream;

public class MainActivity extends AppCompatActivity {

    private static MainActivity instance;

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        if (isRoot())
        {
            RootService.bind(new Intent(MainActivity.this, SuperMain.class), new AIDLConnection(false));
        }

        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true) {
                    boolean b = IPCService.isConnect();

                    if (b) {
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Toast.makeText(MainActivity.this,String.valueOf("Su环境初始化完成"),Toast.LENGTH_LONG).show();
                                FloatWinService.showFloat(MainActivity.this);
                                RunFloat();
                            }
                        });
                        break;
                    }
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
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

                try {
                    IPCService.GetIPC().Start();
                } catch (RemoteException e) {
                    throw new RuntimeException(e);
                }
            }
        }).start();

    }

    public static MainActivity getInstance() {
        if (instance != null)
            return instance;
        return null;
    }

    public static boolean isRoot() {
        try {
            Process process = Runtime.getRuntime().exec("su");
            OutputStream os = process.getOutputStream();
            os.write("\n".getBytes());
            os.flush();
            os.write("exit".getBytes());
            os.flush();
            os.write("\n".getBytes());
            os.flush();
            int exitValue = process.waitFor();
            os.close();
            return exitValue == 0;
        } catch (Exception e) {
            return false;
        }
    }
}