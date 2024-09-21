package com.sak.imgui_input.FloatingWindow;

import android.content.Context;
import android.graphics.PixelFormat;
import android.os.RemoteException;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.annotation.NonNull;

import com.sak.imgui_input.NativeUtils;



public class SurfaceViewFloat extends SurfaceView implements SurfaceHolder.Callback {
    private TouchView touchView;


    public SurfaceViewFloat(Context context) {
        this(context, null);
    }


    public SurfaceViewFloat(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }


    public SurfaceViewFloat(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);

        this.setZOrderOnTop(true);
        this.getHolder().setFormat(PixelFormat.RGBA_8888);
        this.getHolder().addCallback(this);
        touchView = new TouchView(context);
        touchView.initView();
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder holder) {
        NativeUtils.SurfaceCreate(holder.getSurface(),this.getWidth(),this.getHeight());
    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder holder, int format, int Width, int Height) {
        NativeUtils.SurfaceChanged(Width, Height);
    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder holder) {}
}
