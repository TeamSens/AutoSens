#include "gui.h"
#include "imgui.h"

void gui() {

    static float f = 0.0f;
    static int counter = 0;
    bool oppened;

    ImGui::Begin("AutoSens", &oppened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    ImGui::Text("This is some useful text.");

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

    if (ImGui::Button("Button"))
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::End();
}