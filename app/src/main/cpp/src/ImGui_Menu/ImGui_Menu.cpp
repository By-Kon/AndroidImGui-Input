//
// Created by Administrator on 2024/8/25.
//

#include "ImGui_Menu.h"


JniTool* jnitool = new JniTool();
void ImGui_Menu::MainMenu() {
    ImGui::SetNextWindowSize(ImVec2(500.0f,500.0f));
    ImGui::Begin("Sak_Text_Input");
    ImGui::InputText("Text Input", this->inputText, IM_ARRAYSIZE(this->inputText));
    ImGui::InputText("Text Input2", this->inputText2, IM_ARRAYSIZE(this->inputText2));


    ImGui::End();

}
ImGui_Menu::ImGui_Menu() {
    screenSize = ImVec2(1080,1920);//imGui.DisplaySize;
}
