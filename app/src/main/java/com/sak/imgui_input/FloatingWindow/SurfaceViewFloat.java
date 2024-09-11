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


/**
 * SurfaceViewFloat 是一个自定义的 SurfaceView，用于在浮动窗口中显示内容。
 * 该类实现了 SurfaceHolder.Callback 接口，以便在 Surface 创建、改变或销毁时执行相应的操作。
 */
public class SurfaceViewFloat extends SurfaceView implements SurfaceHolder.Callback {
    private TouchView touchView;

    /**
     * 构造方法，使用默认属性初始化 SurfaceViewFloat。
     *
     * @param context 上下文对象
     */
    public SurfaceViewFloat(Context context) {
        this(context, null);
    }

    /**
     * 构造方法，使用指定的属性集初始化 SurfaceViewFloat。
     *
     * @param context 上下文对象
     * @param attrs   属性集
     */
    public SurfaceViewFloat(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    /**
     * 构造方法，使用指定的属性集和默认样式初始化 SurfaceViewFloat。
     *
     * @param context      上下文对象
     * @param attrs        属性集
     * @param defStyleAttr 默认样式
     */
    public SurfaceViewFloat(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);

        this.setZOrderOnTop(true);
        this.getHolder().setFormat(PixelFormat.RGBA_8888);
        this.getHolder().addCallback(this);
        touchView = new TouchView(context);
        touchView.initView();
        EventClass.Init(context);
    }

    /**
     * 当 Surface 被创建时调用此方法。
     *
     * @param holder SurfaceHolder 用于控制 Surface 的操作
     */
    @Override
    public void surfaceCreated(@NonNull SurfaceHolder holder) {
        NativeUtils.SurfaceCreate(holder.getSurface(),this.getWidth(),this.getHeight());
    }

    /**
     * 当 Surface 的大小或格式发生变化时调用此方法。
     *
     * @param holder SurfaceHolder 用于控制 Surface 的操作
     * @param format Surface 的像素格式
     * @param Width  Surface 的宽度
     * @param Height Surface 的高度
     */
    @Override
    public void surfaceChanged(@NonNull SurfaceHolder holder, int format, int Width, int Height) {
        NativeUtils.SurfaceChanged(Width, Height);
    }

    /**
     * 当 Surface 被销毁时调用此方法。
     *
     * @param holder SurfaceHolder 用于控制 Surface 的操作
     */
    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder holder) {}
}
