#include <jni.h>
#include <string>
#include "ImGui_Init.h"
#include "imgui_impl_android.h"

// 声明全局变量
static JavaVM *javaVM = nullptr;
static ImGui_Init* gEGLInstance = new ImGui_Init;
JniTool jniTool = nullptr;

// JNI_OnLoad 函数
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    javaVM = vm;
    jniTool = JniTool(vm);
    return JNI_VERSION_1_6;
}

// JString 转换为 CString
char* ConvertJStringToCString(JNIEnv* env, jstring jstr) {
    if (jstr == nullptr) {
        return nullptr;
    }

    const char* strChars = env->GetStringUTFChars(jstr, nullptr);
    char* result = strdup(strChars); // 使用 strdup 复制字符串
    env->ReleaseStringUTFChars(jstr, strChars);
    return result;
}

// 创建 ImGuiWindowData 的 Java 对象
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

// 创建 Surface
extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_SurfaceCreate(JNIEnv* env, jobject /*thiz*/, jobject surface, jint width, jint height) {
    if (gEGLInstance) {
        gEGLInstance->init(env, surface);
        gEGLInstance->UpDisplaySize(width, height);
        jniTool.SetFloatWinServiceClass();
    }
}

// Surface 变化
extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_SurfaceChanged(JNIEnv *env, jclass clazz, jint width, jint height) {
    if (gEGLInstance) {
        gEGLInstance->UpDisplaySize(width, height);
    }
}

// 处理点击事件
extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_MotionEventClick(JNIEnv* env, jobject /*thiz*/, jint action, jfloat posX, jfloat posY) {
    if (gEGLInstance && gEGLInstance->g_Initialized) {
        gEGLInstance->InputTouchEvent(action, posX, posY);
    }
}

// 获取 ImGui 窗口大小
extern "C" JNIEXPORT jobjectArray JNICALL
Java_com_sak_imgui_1input_NativeUtils_GetImGuiWinSize(JNIEnv* env, jclass /*clazz*/) {
    jclass windowDataClass = env->FindClass("com/sak/imgui_input/FloatingWindow/ImGuiWindowData");
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

// 启动 ImGui
extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_Start(JNIEnv* env, jclass /*clazz*/) {
    if (gEGLInstance) {
        gEGLInstance->Start();
    }
}

// 更新输入文本
extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_UpdateInputText(JNIEnv *env, jclass clazz, jstring text) {
    const char* ctext = ConvertJStringToCString(env, text);
    if (gEGLInstance) {
        gEGLInstance->imGuiIo->AddInputCharactersUTF8(ctext);
    }
}

// 删除输入文本
extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_DeleteInputText(JNIEnv *env, jclass clazz) {
    if (gEGLInstance) {
        gEGLInstance->imGuiIo->AddKeyEvent(ImGuiKey_Backspace, true);
        usleep(10000);
        gEGLInstance->imGuiIo->AddKeyEvent(ImGuiKey_Backspace, false);
    }
}

// 加载字体
extern "C" JNIEXPORT void JNICALL
Java_com_sak_imgui_1input_NativeUtils_InitAssetManager(JNIEnv *env, jclass clazz, jobject asset_manager) {
    if (gEGLInstance) {
        AAssetManager* mgr = AAssetManager_fromJava(env, asset_manager);
        if (mgr != nullptr) {
            gEGLInstance->SetAAssetManager(mgr);
        }
    }
}
