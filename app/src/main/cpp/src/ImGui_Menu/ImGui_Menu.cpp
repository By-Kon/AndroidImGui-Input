//
// Created by Administrator on 2024/8/25.
//

#include "ImGui_Menu.h"


JniTool* jnitool = new JniTool();
void ImGui_Menu::MainMenu() {
    //ImGui::SetNextWindowSize(ImVec2(500.0f,500.0f));
    static float Login_h  = 0.0f;
    if(Login_h < 500.0f){
        Login_h += 1.0f;
    }
    ImGui::SetNextWindowSize(ImVec2(900.0f,Login_h));
    ImVec2 beginSize = {900,Login_h};
    ImGui::SetNextWindowPos(ImVec2((screenSize->x - beginSize.x) / 2, (screenSize->y - beginSize.y) / 2));
    ImGui::Begin("Sak_Text_Input", nullptr,3);

    ImGui::InputText("Text Input", this->inputText, IM_ARRAYSIZE(this->inputText));
    ImGui::InputText("Text Input2", this->inputText2, IM_ARRAYSIZE(this->inputText2));
    ImGui::End();

}
ImGui_Menu::ImGui_Menu(ImVec2* screenSize2) {

    screenSize = screenSize2;//imGui.DisplaySize;
}
