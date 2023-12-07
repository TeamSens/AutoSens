#include "autosens.h"
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

#ifdef _DEBUG
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONIN$", "r", stdin);
	freopen_s(&file, "CONOUT$", "w", stdout);
	freopen_s(&file, "CONOUT$", "w", stderr);
#endif
	AutoSens::MainLoop();
#ifdef _DEBUG
	FreeConsole();
#endif
	return 0;
}