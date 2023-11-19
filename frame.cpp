#include "frame.h"
#include "imgui.h"

void frame() {

    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("AutoSens");

    ImGui::Text("This is some useful text.");

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

    if (ImGui::Button("Button"))
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::End();
}