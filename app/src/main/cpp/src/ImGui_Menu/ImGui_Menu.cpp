
#include "ImGui_Menu.h"
static  ImGuiWindowFlags windowflags =  ImGuiWindowFlags_NoTitleBar |
ImGuiWindowFlags_NoResize |
ImGuiWindowFlags_NoScrollWithMouse |
ImGuiWindowFlags_NoCollapse;
static float beginHeight  = 0.0f;
std::string hint = {};
void ImGui_Menu::MainMenu() {
    float framerate = ImGui::GetIO().Framerate;
    if(beginHeight < 400.0f){
        beginHeight += 8.0f;
    }
    ImGui::SetNextWindowSize(ImVec2(500.0f,beginHeight));
    ImGui::Begin("Sak_Text_Input", nullptr,windowflags);
    ImGui::Text("FPS: %.1f", framerate);
    ImGui::InputTextWithHint("账号","请输入账号", this->account, IM_ARRAYSIZE(this->account));
    ImGui::InputTextWithHint("密码", "请输入密码",this->password, IM_ARRAYSIZE(this->password));
    if(ImGui::Button("登录")){
        if (strcmp(account, "") == 0 || strcmp(password, "") == 0) {
            hint = "账户名和密码不能为空!";
        } else if (strcmp(account, "Sak") == 0 && strcmp(password, "QQ:1276787482") == 0){
            hint = "登录成功!";
        }else{
            hint = "账号密码错误!";
        }
    }
    ImGui::Text(hint.c_str());
    ImGui::End();
}
ImGui_Menu::ImGui_Menu(ImVec2* displaySize) {
    DisplaySize = displaySize;
}
