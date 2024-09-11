package com.sak.imgui_input.FloatingWindow;

import android.content.Context;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;

public class MyCustomView extends View {

    public MyCustomView(Context context) {
        super(context);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        Log.d("CustomView", "按键代码: " + keyCode);
        return super.onKeyDown(keyCode, event);
    }
}
