//
// Created by Administrator on 2023/7/5.
//

#include "ImGui_Init.h"
//#include "Draw.h"
ImGui_Init::ImGui_Init() {
    g_EglDisplay = EGL_NO_DISPLAY;
    g_EglSurface = EGL_NO_SURFACE;
    mEglConfig  = nullptr;
    g_EglContext = EGL_NO_CONTEXT;
}

void ImGui_Init::test()
{
    jclass clazz = env->FindClass("com/sak/imgui_input/FloatingWindow/FloatWinService");
    if (clazz == nullptr) {
        return; // 类没找到，直接返回
    }

    // 查找静态方法ID
    jmethodID methodID = env->GetStaticMethodID(clazz, "addKeyboardView", "()V");
    if (methodID == nullptr) {
        return; // 方法没找到，直接返回
    }

    // 调用 Java 静态方法
    env->CallStaticVoidMethod(clazz, methodID);
    // 释放局部引用
    env->DeleteLocalRef(clazz);
}

void ImGui_Init::init(JNIEnv* env, jobject surface) {
    // 获取ANativeWindow并保存相关信息
    this->env = env;
    this->SurfaceWin = ANativeWindow_fromSurface(env, surface);
}

int ImGui_Init::InitEGL() {
    if (g_Initialized)
        return false;
    ANativeWindow_acquire(SurfaceWin);

    g_EglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (g_EglDisplay == EGL_NO_DISPLAY)
        LOGE(g_LogTag, "%s", "eglGetDisplay(EGL_DEFAULT_DISPLAY) returned EGL_NO_DISPLAY");

    if (eglInitialize(g_EglDisplay, 0, 0) != EGL_TRUE)
        LOGE( g_LogTag, "%s", "eglInitialize() returned with an error");

    const EGLint egl_attributes[] = {EGL_BUFFER_SIZE,
                                     32,
                                     EGL_RED_SIZE,
                                     8, EGL_GREEN_SIZE, 8,
                                     EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_DEPTH_SIZE, 8, EGL_STENCIL_SIZE, 8,
                                     EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_NONE
    };

        EGLint num_configs = 0;

        if (eglChooseConfig(g_EglDisplay, egl_attributes, nullptr, 0, &num_configs) != EGL_TRUE)
            LOGE( g_LogTag, "%s", "eglChooseConfig() returned with an error");

        if (num_configs == 0)
            LOGE( g_LogTag, "%s", "eglChooseConfig() returned 0 matching config");

        EGLConfig egl_config;
        eglChooseConfig(g_EglDisplay, egl_attributes, &egl_config, 1, &num_configs);
        EGLint egl_format;
        eglGetConfigAttrib(g_EglDisplay, egl_config, EGL_NATIVE_VISUAL_ID, &egl_format);
        ANativeWindow_setBuffersGeometry(SurfaceWin, 0, 0, egl_format);

        const EGLint egl_context_attributes[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
        g_EglContext = eglCreateContext(g_EglDisplay, egl_config, EGL_NO_CONTEXT, egl_context_attributes);

        if (g_EglContext == EGL_NO_CONTEXT)
            LOGE( g_LogTag, "%s", "eglCreateContext() returned EGL_NO_CONTEXT");

        g_EglSurface = eglCreateWindowSurface(g_EglDisplay, egl_config, SurfaceWin, nullptr);
        eglMakeCurrent(g_EglDisplay, g_EglSurface, g_EglSurface, g_EglContext);


    IMGUI_CHECKVERSION();
    //ImGui::CreateContext();

    g_Context = ImGui::CreateContext();
    imGuiIo = &ImGui::GetIO();
    imGuiStyle = &ImGui::GetStyle();

    ImGui_ImplAndroid_Init(SurfaceWin);
    ImGui_ImplOpenGL3_Init("#version 300 es");

    ImFontConfig font_cfg;
    font_cfg.SizePixels = 22.0f;
    font_cfg.FontDataOwnedByAtlas = false;
    imGuiIo->Fonts->AddFontFromMemoryTTF((void*)OPPOSans_H, OPPOSans_H_size, 30.0f, NULL, imGuiIo->Fonts->GetGlyphRangesChineseFull());//字体

    imGuiIo->Fonts->AddFontDefault();

    imGuiStyle->ScaleAllSizes(3.0f);
    ImGui::StyleColorsLight();

    imGuiStyle->WindowRounding = 20.0f;
    imGuiStyle->FrameRounding =20.0f;

    imGuiStyle->GrabRounding = 10.0f;   // 滚动条圆角
    imGuiStyle->LogSliderDeadzone=10.0f;
    imGuiStyle->WindowTitleAlign = ImVec2(0.5, 0.5);

    imGuiStyle->Colors[ImGuiCol_TitleBg] = ImColor(ImVec4(1.0f, 1.0f, 1.0f,0.75f));
    imGuiStyle->Colors[ImGuiCol_TitleBgActive] = ImColor(ImVec4(1.0f, 1.0f, 1.0f,0.75f));
    imGuiStyle->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(ImVec4(1,1,1,0.5));

    imGuiStyle->Colors[ImGuiCol_WindowBg] = ImColor(ImVec4(1.0f, 1.0f, 1.0f,0.75f));

    imGuiStyle->Colors[ImGuiCol_Text] = ImColor(0,0,0,255);

    imGuiStyle->Colors[ImGuiCol_Button] = ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    imGuiStyle->Colors[ImGuiCol_ButtonActive] = ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    imGuiStyle->Colors[ImGuiCol_ButtonHovered] = ImColor(ImVec4(0.0f, 0.75f, 1.0f, 1.0f));

    imGuiStyle->Colors[ImGuiCol_FrameBg] = ImColor(255,255,255,255);
    imGuiStyle->Colors[ImGuiCol_FrameBgActive] = ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    imGuiStyle->Colors[ImGuiCol_FrameBgHovered] = ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

    imGuiStyle->Colors[ImGuiCol_Header] = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);         // 未展开的节点背景色
    imGuiStyle->Colors[ImGuiCol_HeaderHovered] = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);  // 悬停时的背景色
    imGuiStyle->Colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.75f, 1.0f, 1.0f);   // 展开时的背景色

    imGuiStyle->Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 0.5f, 1.0f, 1.0f);
    imGuiStyle->FrameBorderSize = 3.0f; // 边框厚度
    imGuiStyle->FramePadding = ImVec2(10.0f, 10.0f);  // 水平和垂直填充

    g_Initialized = true;

    return 1;
}


void ImGui_Init::InputTouchEvent(int event_get_action, float x, float y) {
    switch (event_get_action){

        case eTouchEvent::TOUCH_OUTSIDE:
            imGuiIo->MouseDown[0] = false;
            break;
        case eTouchEvent::TOUCH_DOWN:
            imGuiIo->MousePos.x = x;
            imGuiIo->MousePos.y = y;
            imGuiIo->MouseDown[0] = true;
            break;
        case eTouchEvent::TOUCH_UP:
            imGuiIo->MouseDown[0] = false;
            break;
        case eTouchEvent::TOUCH_MOVE:
            imGuiIo->MousePos.x = x;
            imGuiIo->MousePos.y = y;
            break;
        default:
            break;
    }
}

void ImGui_Init::MyWindowFunction() {
    // 获取当前 ImGui 上下文
    if (g_Context == nullptr) {
        return; // 上下文为空，直接返回
    }
    // 获取窗口列表
    WinList = g_Context->Windows;

    // 使用迭代器遍历窗口列表
   /* for (auto it = WinList.begin(); it != WinList.end(); ++it) {
        g_Window = *it;

        // 检查窗口是否有效
        if (g_Window != nullptr && g_Window->Active && !g_Window->Collapsed) {
            // 在此处理有效窗口的逻辑
            // 例如，渲染或更新窗口内容
            LOGD("无效窗口：%s",g_Window->Name);
            //WinList.erase(WinList.begin());
        } else {
            // 窗口无效，进行清理或其他操作
            // 可以选择从列表中移除窗口（如果需要）
            LOGD("无效窗口：%s",g_Window->Name);
        }
    }
    */
}


ImGui_Menu* menu = new ImGui_Menu;
static bool WantTextInputLast = false;
void ImGui_Init::EglThread() {
    this->InitEGL();
    while (true) {
        // 检测输入框的鼠标点击事件
        if (imGuiIo->WantTextInput && !WantTextInputLast) {
            //this->test();
            LOGD("TRUE");  // 显示软键盘
        }
        WantTextInputLast = imGuiIo->WantTextInput;
        // 如果鼠标点击了输入框以外的地方，更新 WantTextInputLast
        if (ImGui::IsMouseClicked(0) && !ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup)) {
            LOGD("FALSE");
            WantTextInputLast = false;
        }

        ImGuiNewFrame();

        menu->MainMenu();

        ImGuiRender();
    }
}



void ImGui_Init::ImGuiNewFrame() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 启动 Dear ImGui 框架
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();
    MyWindowFunction();
}

void ImGui_Init::ImGuiRender() {
    // 渲染 Dear ImGui 框架
    ImGui::Render();
    // 使用 OpenGL 渲染 ImGui 界面
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //opengl当前buff传递至屏幕
    eglSwapBuffers(g_EglDisplay, g_EglSurface);

}

void ImGui_Init::Start() {
    std::thread thread_EGL([this]{EglThread();});
    thread_EGL.detach();

}

void ImGui_Init::SetUUID(char* UUID){
    //设备码 = UUID;
}

void ImGui_Init::SetPassword(char *Password){

   /* if (fopen(_kmPath, "r")){
        粘贴卡密=dq(_kmPath);
    }else{
        粘贴卡密 = Password;
        // sprintf(kmnr, "卡密:%s",粘贴卡密); 
    }
    */
}

void ImGui_Init::StartImGui(int width,int height)
{
    /*if (width > 100 && height > 100){
        _ScreenY = width;
        _ScreenX = height;
        LOGD("传输分辨率width：%d",width);
        LOGD("传输分辨率height：%d",height);
        px = height / 2.0;
        py = width / 2.0;
        glViewport(0, 0, width, height);
    }
     */
}




