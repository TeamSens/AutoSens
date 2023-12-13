#include "gui.h"
#include "../Fonts/roboto.h" // had to stay in here, would error otherwise idek


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
Globals globals;
Minecraft mc;
Apex apex;
CounterStrike2 cs2;

LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam))
		return true;

	switch (message) {
	case WM_SIZE:
		if (gui::device && wParam != SIZE_MINIMIZED) {
			gui::presentParameters.BackBufferWidth = LOWORD(lParam);
			gui::presentParameters.BackBufferHeight = HIWORD(lParam);
			gui::ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		gui::position = MAKEPOINTS(lParam);
		return 0;
	case WM_MOUSEMOVE:
		if (wParam == MK_LBUTTON) {
			const auto points = MAKEPOINTS(lParam);
			auto rect = ::RECT{};
			GetWindowRect(gui::window, &rect);

			rect.left += points.x - gui::position.x;
			rect.top += points.y - gui::position.y;

			if (gui::position.x >= 0 &&
				gui::position.x <= gui::WIDTH &&
				gui::position.y >= 0 &&
				gui::position.y <= 19)

				SetWindowPos(gui::window, HWND_TOPMOST, rect.left, rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER);
		}
		return 0;
	}

	return DefWindowProc(window, message, wParam, lParam);
}

void gui::CreateHWindow(const char* windowName, const char* className) noexcept {

	windowClass.cbSize = sizeof(WNDCLASSEXA);
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = className;
	windowClass.hIconSm = 0;

	RegisterClassExA(&windowClass);

	window = CreateWindowA(className, windowName, WS_POPUP, 100, 100, WIDTH, HEIGHT, 0, 0, windowClass.hInstance, 0);

	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}

void gui::DestroyHWindow() noexcept {

	DestroyWindow(window);
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool gui::CreateDevice() noexcept {

	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d)
		return false;

	ZeroMemory(&presentParameters, sizeof(presentParameters));

	presentParameters.Windowed = TRUE;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	presentParameters.EnableAutoDepthStencil = TRUE;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParameters,
		&device) < 0)
		return false;

	return true;
}

void gui::ResetDevice() noexcept {

	ImGui_ImplDX9_InvalidateDeviceObjects();

	const auto result = device->Reset(&presentParameters);

	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

void gui::DestroyDevice() noexcept {

	if (device) {
		device->Release();
		device = nullptr;
	}

	if (d3d)
	{
		d3d->Release();
		d3d = nullptr;
	}
}

void gui::CreateImGui() noexcept
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ::ImGui::GetIO();

	io.IniFilename = nullptr;
	io.LogFilename = nullptr;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
	// u can load these from a file, but im just grabbing it from a decompiled TTF so no downloading is needed.
	ImFontConfig font_cfg;
	font_cfg.FontDataOwnedByAtlas = false;
	ImFont* font1 = io.Fonts->AddFontFromMemoryTTF(robotoRaw,sizeof(robotoRaw),16,&font_cfg);
}
void gui::DestroyImGui() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void gui::BeginRender() noexcept
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
		{
			gui::isRunning = false;
			return;
		}
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

}

void gui::EndRender() noexcept {

	ImGui::EndFrame();

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	if (device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();
	}

	const auto result = device->Present(0, 0, 0, 0);

	if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		ResetDevice();
}

void gui::Render() noexcept {

	ImGui::SetNextWindowPos({ 0,0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGui::Begin(
		"Test",
		&isRunning,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove);



	switch (globals.gui)
	{
	case 1:

		ImGui::SetCursorPos({ 5.f,25.f }); // child for the game you are converting from

		ImGui::BeginChild("##convertingfrom", { 250.f,200.f }, true);
		ImGui::PushItemWidth(240.f);
		ImGui::ListBox("##gameslist1", &globals.selectedGameFrom, globals.games, 3);
		ImGui::PopItemWidth();
		ImGui::EndChild();

		ImGui::SetCursorPos({ 267.f,115.f });

		ImGui::Text("to");

		ImGui::SetCursorPos({ 292.f,25.f });

		ImGui::BeginChild("##convertingto", { 250.f,200.f }, true);
		ImGui::PushItemWidth(240.f);
		ImGui::ListBox("##gameslist2", &globals.selectedGameTo, globals.games, 3);
		ImGui::PopItemWidth();
		ImGui::EndChild();

		ImGui::SetCursorPos({ 5.f, 245.f });
		if (ImGui::Button("Convert", { 537.f, 50.f })) {
			if (globals.selectedGameFrom != globals.selectedGameTo)
				globals.gui = 2;
		}
		break;
	case 2:
		// I didnt know if there was a better way to do this part, idrc
		ImGui::SetCursorPos({ 5.f,25.f }); // child for the game you are converting from
		ImGui::BeginChild("##convertingfrom", { 250.f,200.f }, true);
		switch (globals.selectedGameFrom)
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

		ImGui::SetCursorPos({ 292.f,25.f });
		ImGui::BeginChild("##convertingto", { 250.f,200.f }, true);
		switch (globals.selectedGameTo)
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

		ImGui::SetCursorPos({ 5.f, 245.f });
		if (ImGui::Button("Convert", { 537.f, 50.f }))
		{
			
		}

		break; // breaka out of case 2
	}

	ImGui::End();
}