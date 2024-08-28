//
// Created by Administrator on 2024/8/25.
//

#include "ImGui_Menu.h"



void ImGui_Menu::MainMenu() {
    ImGui::SetNextWindowSize(ImVec2(500.0f,500.0f));
    ImGui::Begin("Sak_Text_Input");
    ImGui::InputText("Text Input", this->inputText, IM_ARRAYSIZE(this->inputText));
    ImGui::InputText("Text Input2", this->inputText, IM_ARRAYSIZE(this->inputText));
    ImGui::End();

}
ImGui_Menu::ImGui_Menu() {

    screenSize = ImVec2(1080,1920);//imGui.DisplaySize;
}
