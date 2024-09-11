//
// Created by Administrator on 2024/9/11.
//

#include "JniTool.h"
JavaVM* JniTool::g_VM = nullptr;
jclass JniTool::FloatWinServiceClass = nullptr;
JniTool::JniTool() {

}
JniTool::JniTool(JavaVM *JVM) {
    JniTool::g_VM = JVM;

}


JNIEnv* JniTool::AttachThread() {
    JNIEnv *env = nullptr;
    jint result = g_VM->AttachCurrentThread(&env, nullptr);
    if (result != JNI_OK) {
        LOGD("Failed to attach thread: %d", result); // Log error code
        return nullptr;
    }
    return env;
}




void JniTool::DetachThread() {
    g_VM->DetachCurrentThread();
}

void JniTool::NativeMethod() {
    JNIEnv *env = nullptr;
    JniTool::g_VM->AttachCurrentThread(&env, nullptr);
    jclass clazz = env->FindClass("com/sak/imgui_input/FloatingWindow/FloatWinService");
    JniTool::FloatWinServiceClass = (jclass) env->NewGlobalRef(clazz);
    LOGD("FloatWinServiceClass %p",JniTool::FloatWinServiceClass);
}