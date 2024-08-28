#include <jni.h>
#include <string>
#include "ImGui_Init.h"

// 声明全局变量
static ImGui_Init* gEGLInstance = new ImGui_Init;

// 辅助函数：将jstring转换为C字符串
char* ConvertJStringToCString(JNIEnv* env, jstring jstr) {
    if (jstr == nullptr) {
        return nullptr;
    }

    const char* strChars = env->GetStringUTFChars(jstr, nullptr);
    char* result = strdup(strChars); // 使用strdup复制字符串
    env->ReleaseStringUTFChars(jstr, strChars);
    return result;
}

// 创建ImGuiWindowData的Java对象
jobject CreateImGuiWindowData(JNIEnv* env, jclass windowDataClass, int winId, const char* winName, float positions[4], bool isActive) {
    jfieldID idField = env->GetFieldID(windowDataClass, "WinID", "I");
    jfieldID nameField = env->GetFieldID(windowDataClass, "WinName", "Ljava/lang/String;");
    jfieldID posXField = env->GetFieldID(windowDataClass, "Pos_X", "F");
    jfieldID posYField = env->GetFieldID(windowDataClass, "Pos_Y", "F");
    jfieldID sizeXField = env->GetFieldID(windowDataClass, "Size_X", "F");
    jfieldID sizeYField = env->GetFieldID(windowDataClass, "Size_Y", "F");
    jfieldID actionField = env->GetFieldID(windowDataClass, "Action", "Z");

    jobject windowDataObject = env->AllocObject(windowDataClass);
    env->SetIntField(windowDataObject, idField, winId);
    env->SetObjectField(windowDataObject, nameField, env->NewStringUTF(winName));
    env->SetFloatField(windowDataObject, posXField, positions[0]);
    env->SetFloatField(windowDataObject, posYField, positions[1]);
    env->SetFloatField(windowDataObject, sizeXField, positions[2]);
    env->SetFloatField(windowDataObject, sizeYField, positions[3]);
    env->SetBooleanField(windowDataObject, actionField, isActive);

    return windowDataObject;
}

extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_surfaceCreate(JNIEnv* env, jobject /*thiz*/, jobject surface) {
    if (gEGLInstance) {
        gEGLInstance->init(env, surface);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_MotionEventClick(JNIEnv* env, jobject /*thiz*/, jint action, jfloat posX, jfloat posY) {
    if (gEGLInstance && gEGLInstance->g_Initialized) {
        gEGLInstance->InputTouchEvent(action, posX, posY);
    }
}

extern "C" JNIEXPORT jobjectArray JNICALL
Java_com_sak_imgui_1input_NativeUtils_GetImGuiWinSize(JNIEnv* env, jclass /*clazz*/) {
    jclass windowDataClass = env->FindClass("com/sak/imgui_input/ImGuiWindowData");
    if (windowDataClass == nullptr || gEGLInstance == nullptr || gEGLInstance->WinList.Size == 0) {
        return nullptr;
    }

    jobjectArray windowDataArray = env->NewObjectArray(gEGLInstance->WinList.Size, windowDataClass, nullptr);

    int index = 0;
    for (const auto& win : gEGLInstance->WinList) {
        if (std::string(win->Name) != "Debug##Default" && win->Active) {
            float positions[] = {win->Pos.x, win->Pos.y, win->Size.x, win->Size.y};
            jobject windowData = CreateImGuiWindowData(env, windowDataClass, win->ID, win->Name, positions, win->Active);
            env->SetObjectArrayElement(windowDataArray, index++, windowData);
        }
    }

    return windowDataArray;
}

extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_SetUUID(JNIEnv* env, jclass /*clazz*/, jstring uuid) {
    char* uuidCStr = ConvertJStringToCString(env, uuid);
    if (gEGLInstance) {
        gEGLInstance->SetUUID(uuidCStr);
    }
    free(uuidCStr); // 释放内存
}

extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_SetPassword(JNIEnv* env, jclass /*clazz*/, jstring password) {
    char* passwordCStr = ConvertJStringToCString(env, password);
    if (gEGLInstance) {
        gEGLInstance->SetPassword(passwordCStr);
    }
    free(passwordCStr); // 释放内存
}

extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_StartImGui(JNIEnv* env, jclass /*clazz*/, jint width, jint height) {
    if (gEGLInstance) {
        gEGLInstance->StartImGui(width, height);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_Start(JNIEnv* env, jclass /*clazz*/) {
    if (gEGLInstance) {
        gEGLInstance->Start();
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_UpdateInputText(JNIEnv *env, jclass clazz, jstring text) {
    // TODO: implement UpdateInputText()
    LOGD("SAK-STRING");
    const char* ctext = ConvertJStringToCString(env,text);
    if (gEGLInstance) {
        gEGLInstance->imGuiIo->AddInputCharactersUTF8(ctext);
    }
}