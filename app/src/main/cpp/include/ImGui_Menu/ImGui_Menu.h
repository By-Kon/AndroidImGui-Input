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
    ImVec2* screenSize;
    char inputText[128] = {};
    char inputText2[128] = {};

};
