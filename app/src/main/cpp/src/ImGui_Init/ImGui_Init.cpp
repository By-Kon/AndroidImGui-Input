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

// 计算新的字体大小
float CalculateScaledFontSize(float baseFontSize, int baseWidth, int baseHeight, int newWidth, int newHeight)
{
    // 计算水平和垂直缩放因子
    float horizontalScale = static_cast<float>(newWidth) / baseWidth;
    float verticalScale = static_cast<float>(newHeight) / baseHeight;

    // 使用水平和垂直缩放因子的平均值
    float scaleFactor = (horizontalScale + verticalScale) / 2.0f;

    // 返回新的字体大小
    return baseFontSize * scaleFactor;
}

// Helper to retrieve data placed into the assets/ directory (android/app/src/main/assets)
int ImGui_Init::GetAssetData(const char* filename, void** outData)
{
    int num_bytes = 0;
    AAsset* asset_descriptor = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);
    if (asset_descriptor)
    {
        num_bytes = AAsset_getLength(asset_descriptor);
        *outData = IM_ALLOC(num_bytes);
        int64_t num_bytes_read = AAsset_read(asset_descriptor, *outData, num_bytes);
        AAsset_close(asset_descriptor);
        IM_ASSERT(num_bytes_read == num_bytes);
    }
    return num_bytes;
}

void ImGui_Init::init(JNIEnv* env, jobject surface) {
    // 获取ANativeWindow并保存相关信息
    this->SurfaceWin = ANativeWindow_fromSurface(env, surface);
}

void ImGui_Init::LoadFont() {


    // 设置字体配置
    ImFontConfig fontConfig;
    fontConfig.OversampleH = 2;  // 提高水平采样质量
    fontConfig.OversampleV = 2;  // 提高垂直采样质量
    fontConfig.PixelSnapH = true;  // 启用像素对齐

    // 读取字体数据
    void* font_data = nullptr;
    int font_data_size = GetAssetData("test.ttf", &font_data);

    if (font_data_size > 0)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImFontAtlas* atlas = io.Fonts;

        // 清除现有的字体
        atlas->Clear();

        // 加载字体，指定字符范围，包括中文字符范围
        static const ImWchar ranges[] = {
                0x0020, 0x00FF,  // 基本拉丁字符
                0x4E00, 0x9FAF,  // CJK（中文）字符
                0
        };
        // 基准分辨率和字体大小 (1080x2400, 字体大小 60.0f)
        float baseFontSize = 50.0f; // 基准字体大小
        int baseWidth = 1080;       // 基准宽度
        int baseHeight = 2400;      // 基准高度
        float newFontSize = CalculateScaledFontSize(baseFontSize, baseWidth, baseHeight, DisplaySize.x, DisplaySize.y);

        LOGD("字体大小：%.2f",newFontSize);
        // 从文件数据加载字体并指定字符范围
        imFont = io.Fonts->AddFontFromMemoryTTF((void*)font_data, font_data_size, newFontSize, &fontConfig, ranges);
        // 构建字体图集
        atlas->Build();
        // 释放字体数据
        IM_FREE(font_data);
    }
    else
    {

        fprintf(stderr, "Failed to load font data from assets.\n");
    }
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

    LoadFont();
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

void ImGui_Init::SetAAssetManager(AAssetManager* assetManager2) {
   this->assetManager = assetManager2;
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

void KeyboardView(){
    JNIEnv *g_Env = nullptr;
    jint result = JniTool::g_VM->AttachCurrentThread(&g_Env, nullptr);
    if (result != JNI_OK || g_Env == nullptr) {
        LOGD("Failed to attach thread or obtain JNIEnv, result: %d", result);
        return;
    }
    // Log classpath
    LOGD("Looking for class in thread...");

    if (JniTool::FloatWinServiceClass == nullptr) {
        LOGD("Failed to find class");
    } else {
        LOGD("Class found: %p", JniTool::FloatWinServiceClass);
    }

    jmethodID myMethod = g_Env->GetStaticMethodID(JniTool::FloatWinServiceClass, "addKeyboardView", "()V");
    if (myMethod == nullptr) {
        LOGD("Failed to find method");
    } else {
        LOGD("Method found: %p", myMethod);
    }

    if (myMethod != nullptr) {
        g_Env->CallStaticVoidMethod(JniTool::FloatWinServiceClass, myMethod);
    }

    JniTool::g_VM->DetachCurrentThread();
}



void ImGui_Init::EglThread() {
    this->InitEGL();
    ImGui_Menu* menu = new ImGui_Menu(&DisplaySize);
    while (true) {

        static bool WantTextInputLast = false;
        if (imGuiIo->WantTextInput && !WantTextInputLast) {
            LOGD("获取焦点");
            KeyboardView();
        } else if (!imGuiIo->WantTextInput && WantTextInputLast) {
            LOGD("失去焦点");
            KeyboardView();
        }
        WantTextInputLast = imGuiIo->WantTextInput;

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
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    eglSwapBuffers(g_EglDisplay, g_EglSurface);

}

void ImGui_Init::Start() {
    std::thread thread_EGL([this]{EglThread();});
    thread_EGL.detach();

}

void ImGui_Init::UpDisplaySize(int width,int height){
    LOGD("分辨率：%d\n%d",width,height);
    DisplaySize = ImVec2(width,height);
}





