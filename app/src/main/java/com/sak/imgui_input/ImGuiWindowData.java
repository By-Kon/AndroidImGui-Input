package com.sak.imgui_input;

import android.os.Parcel;
import android.os.Parcelable;

// 自定义类 ImGuiWindowData，实现 Parcelable 接口
public class ImGuiWindowData implements Parcelable {
    // 窗口id
    public int WinID;
    // 窗口名
    public String WinName;
    // 窗口坐标宽高数据
    public float Pos_X;
    public float Pos_Y;
    public float Size_X;
    public float Size_Y;
    // 是否处于活动状态
    public boolean Action;

    // 默认构造函数
    public ImGuiWindowData() {
        WinID = 0;
        WinName = "";
        Pos_X = 0;
        Pos_Y = 0;
        Size_X = 0;
        Size_Y = 0;
        Action = false;
    }

    // Parcelable 接口实现
    protected ImGuiWindowData(Parcel in) {
        WinID = in.readInt();
        WinName = in.readString();
        Pos_X = in.readFloat();
        Pos_Y = in.readFloat();
        Size_X = in.readFloat();
        Size_Y = in.readFloat();
        Action = in.readByte() != 0;
    }

    public static final Creator<ImGuiWindowData> CREATOR = new Creator<ImGuiWindowData>() {
        @Override
        public ImGuiWindowData createFromParcel(Parcel in) {
            return new ImGuiWindowData(in);
        }

        @Override
        public ImGuiWindowData[] newArray(int size) {
            return new ImGuiWindowData[size];
        }
    };

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeInt(WinID);
        dest.writeString(WinName);
        dest.writeFloat(Pos_X);
        dest.writeFloat(Pos_Y);
        dest.writeFloat(Size_X);
        dest.writeFloat(Size_Y);
        dest.writeByte((byte) (Action ? 1 : 0));
    }

    @Override
    public int describeContents() {
        return 0;
    }
}
