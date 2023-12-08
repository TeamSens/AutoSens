#include "autosens.h"



void AutoSens::MainLoop() {

	Globals globals;
	Minecraft mc;
	Apex apex;
	CounterStrike2 cs2;

	// Initialize GLFW and create a window
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(547, 300, "AutoSens", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Initialize ImGui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	// Remove .ini file
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;

	// Main loop
	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		// Start the ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Set the ImGui window to fill up the full GLFW window, disable the resize grip, disable title bar, and prevent collapse
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
		ImGui::Begin("##window1", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
		
		switch(globals.gui)
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
		
		
		ImGui::End();

		// Render ImGui
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}
