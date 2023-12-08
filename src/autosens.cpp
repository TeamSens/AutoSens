#include "autosens.h"



void AutoSens::MainLoop() {

	Globals globals;
	Minecraft mc;
	Apex apex;
	CounterStrike2 cs2;

	switch (globals.gui)
	{
	case 1:
		ImGui::SetCursorPos({ 5.f,5.f }); // child for the game you are converting from
		ImGui::BeginChild("##convertingfrom", { 250.f,200.f }, true);
		ImGui::PushItemWidth(240.f);
		ImGui::ListBox("##gameslist1", &globals.SelectedGame1, globals.games, 3);
		ImGui::PopItemWidth();
		ImGui::EndChild();

		ImGui::SetCursorPos({ 265.f,75.f });
		ImGui::Text("to");

		ImGui::SetCursorPos({ 292.f,5.f });
		ImGui::BeginChild("##convertingto", { 250.f,200.f }, true);
		ImGui::PushItemWidth(240.f);
		ImGui::ListBox("##gameslist2", &globals.SelectedGame2, globals.games, 3);
		ImGui::PopItemWidth();
		ImGui::EndChild();

		ImGui::SetCursorPos({ 5.f, 225.f });
		if (ImGui::Button("Convert", { 537.f, 50.f })) {
			if (globals.SelectedGame1 != globals.SelectedGame2)
				globals.gui = 2;
		}
		break;
	case 2:
		// I didnt know if there was a better way to do this part, idrc
		ImGui::SetCursorPos({ 5.f,5.f }); // child for the game you are converting from
		ImGui::BeginChild("##convertingfrom", { 250.f,200.f }, true);
		switch (globals.SelectedGame1)
		{
		case 0:
			if (ImGui::Button("Change CFG file path")) {

				apex.SetCfgPath();
			}
			ImGui::Text("Chosen File Path: %s", apex.cfgPath);

			break;
		case 1:
			if (ImGui::Button("Change CFG file path")) {

				cs2.SetCfgPath();
			}
			ImGui::Text("Chosen File Path: %s", cs2.cfgPath);
			break;
		case 2:
			if (ImGui::Button("Change CFG file path")) {

				mc.SetCfgPath();
			}
			ImGui::Text("Chosen File Path: %s", mc.cfgPath);
			break;
		}
		ImGui::EndChild();

		ImGui::SetCursorPos({ 292.f,5.f });
		ImGui::BeginChild("##convertingto", { 250.f,200.f }, true);
		switch (globals.SelectedGame2)
		{
		case 0:
			if (ImGui::Button("Change CFG file path")) {

				apex.SetCfgPath();
			}
			ImGui::Text("Chosen File Path: %s", apex.cfgPath);

			break;
		case 1:
			if (ImGui::Button("Change CFG file path")) {

				cs2.SetCfgPath();
			}
			ImGui::Text("Chosen File Path: %s", cs2.cfgPath);
			break;
		case 2:
			if (ImGui::Button("Change CFG file path")) {

				mc.SetCfgPath();
			}
			ImGui::Text("Chosen File Path: %s", mc.cfgPath);
			break;
		}
		ImGui::EndChild();

		ImGui::SetCursorPos({ 5.f, 225.f });
		if (ImGui::Button("Convert", { 537.f, 50.f }))
		{
			// convert logic
		}

		break; // breaka out of case 2
	}
}
