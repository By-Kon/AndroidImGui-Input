//
// Created by Administrator on 2024/9/11.
//

#ifndef IMGUI_INPUT_JNITOOL_H
#define IMGUI_INPUT_JNITOOL_H
#include <jni.h>
#include "log.h"
class JniTool {
public:
    static JavaVM *g_VM;
    static jclass FloatWinServiceClass;
    JniTool(JavaVM *JVM);
    JniTool();
    JNIEnv* AttachThread();
    void DetachThread();
    void NativeMethod();

private:

};


#endif //IMGUI_INPUT_JNITOOL_H
