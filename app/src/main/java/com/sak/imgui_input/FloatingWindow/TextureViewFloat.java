package com.sak.imgui_input.FloatingWindow;

import android.content.Context;
import android.graphics.SurfaceTexture;
import android.view.Surface;
import android.view.TextureView;

import com.sak.imgui_input.NativeUtils;



public class TextureViewFloat extends TextureView implements TextureView.SurfaceTextureListener {

    private TouchView touchView;


    public TextureViewFloat(Context context) {
        super(context);
        this.setOpaque(true);
        setSurfaceTextureListener(this);
        touchView = new TouchView(context);
        touchView.initView();

    }

    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
        NativeUtils.SurfaceCreate(new Surface(surface),width,height);
        NativeUtils.SurfaceChanged(width, height);
    }

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
        NativeUtils.SurfaceChanged(width, height);
    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        return true;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {

    }
}
