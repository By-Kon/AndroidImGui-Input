//
// Created by Administrator on 2024/8/25.
//
#pragma once
#include "pch.h"
#include <string>
#include <cstdio>
#include "JniTool.h"
class ImGui_Menu {
public:
    ImGui_Menu(ImVec2* screenSize);

    void MainMenu();

private:
    ImVec2* DisplaySize;
    char account[128] = {};
    char password[128] = {};

};
