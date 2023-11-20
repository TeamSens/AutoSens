#include "gui.h"
#include "imgui.h"

using namespace ImGui;

void interface::gui() {

    Begin("AutoSens", &oppened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    const char* games[] = { "Apex","cs2","Minecraft" };
    //everything that is in the frame goes inside of the brackets
    {
        const float width = ImGui::GetWindowWidth();
        const float combo_width = width * 0.25f;

        SetNextItemWidth(combo_width);

        Combo("Select Current Game", &currentGame, games, numberOfGames);

        SetNextItemWidth(combo_width);

        Combo("Select Game to Change Sensitivity", &newGame, games, numberOfGames);
        
        if (currentGame == newGame) {
            Text("Games Cannot be the Same!");
        }
        else if (Button("Config My Sens!")) {
            // run the conf script
        }
    }


    ImGui::End();
}