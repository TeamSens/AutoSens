#include "autosens.h"

void AutoSens::MainLoop() {

	CounterStrike2 cs2;

	// Initialize GLFW and create a window
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(500, 300, "AutoSens", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Initialize ImGui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Remove .ini file
	io.IniFilename = nullptr;

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
		ImGui::Begin("##", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

		// Add a button to open the native file dialog (to choose the .cfg file or option file of the user)
		if (ImGui::Button("Change CFG file path")) {

			cs2.SetCfgPath();
		}

		// Display the chosen file path in a text dialog
		ImGui::Text("Chosen File Path: %s", cs2.cfgPath);

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
