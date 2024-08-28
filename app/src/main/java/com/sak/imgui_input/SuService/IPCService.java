package com.sak.imgui_input.SuService;


import com.sak.imgui_input.SakSu;

public class IPCService {
    private static SakSu ipc;

    public static boolean isConnect() {
        return ipc != null;
    }

    public static void InItIPC(SakSu ipc) {
        IPCService.ipc = ipc;
    }

    public static SakSu GetIPC() {
        return ipc;
    }
}
