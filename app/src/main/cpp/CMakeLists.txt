cmake_minimum_required(VERSION 3.22.1)

# 项目名称
project("ImGui")

# 禁用所有警告
add_definitions(-w)

# 设置包含头文件的目录
include_directories(
        include/ImGui
        include/ImGui_Init
        include/ImGui_Image
        include/ImGui_Menu
        include/WeiYanTool
        include/Tool
        include/ESP
        include/GameRevise
)

# 查找源文件并将其分组
file(GLOB SakImGui "src/ImGui/*.cpp")
file(GLOB ImGuiInit "src/ImGui_Init/*.cpp")
file(GLOB ImGuiImage "src/ImGui_Image/*.cpp")
file(GLOB ImGuiMenu "src/ImGui_Menu/*.cpp")
file(GLOB Tool "src/Tool/*.cpp")


# 创建共享库
add_library(${CMAKE_PROJECT_NAME} SHARED
        ${SakImGui}
        ${ImGuiInit}
        ${ImGuiImage}
        ${ImGuiMenu}
        ${Tool}
        include/WeiYanTool/cJSON.c
        native-lib.cpp
)

# 链接所需的库
target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        EGL
        GLESv3
        log
)
