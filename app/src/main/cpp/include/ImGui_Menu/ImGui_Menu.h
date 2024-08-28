//
// Created by Administrator on 2024/8/25.
//
#pragma once
#include "pch.h"
#include <string>
#include <cstdio>
class ImGui_Menu {
public:
    ImGui_Menu();

    void MainMenu();

private:
    ImVec2 screenSize;
    char inputText[128] = {};

};
