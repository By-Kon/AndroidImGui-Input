package com.sak.imgui_input.FloatingWindow;

import android.content.Context;
import android.graphics.SurfaceTexture;
import android.os.RemoteException;
import android.util.Log;
import android.view.Surface;
import android.view.TextureView;

import com.sak.imgui_input.NativeUtils;


/**
 * TextureViewFloat 是一个自定义的 TextureView，用于在浮动窗口中显示内容。
 * 该类实现了 TextureView.SurfaceTextureListener 接口，以便在 SurfaceTexture 可用、大小改变、销毁或更新时执行相应的操作。
 */
public class TextureViewFloat extends TextureView implements TextureView.SurfaceTextureListener {

    private TouchView touchView;

    /**
     * 构造方法，初始化 TextureViewFloat。
     *
     * @param context 上下文对象
     */
    public TextureViewFloat(Context context) {
        super(context);
        this.setOpaque(true);
        setSurfaceTextureListener(this);
        touchView = new TouchView(context);
        touchView.initView();
        EventClass.Init(context);
    }

    /**
     * 当 SurfaceTexture 可用时调用此方法。
     *
     * @param surface SurfaceTexture 对象
     * @param width   SurfaceTexture 的宽度
     * @param height  SurfaceTexture 的高度
     */
    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {

            NativeUtils.SurfaceCreate(new Surface(surface),width,height);
            NativeUtils.SurfaceChanged(width, height);

    }

    /**
     * 当 SurfaceTexture 的大小改变时调用此方法。
     *
     * @param surface SurfaceTexture 对象
     * @param width   SurfaceTexture 的新宽度
     * @param height  SurfaceTexture 的新高度
     */
    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
        // 可选：处理 SurfaceTexture 大小改变的逻辑
        NativeUtils.SurfaceChanged(width, height);

    }

    /**
     * 当 SurfaceTexture 被销毁时调用此方法。
     *
     * @param surface SurfaceTexture 对象
     * @return 返回 true 表示系统会自动销毁 SurfaceTexture
     */
    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        Log.e("NDK-java", "onSurfaceTextureDestroyed");
        return true;
    }

    /**
     * 当 SurfaceTexture 更新时调用此方法。
     *
     * @param surface SurfaceTexture 对象
     */
    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {

    }
}
