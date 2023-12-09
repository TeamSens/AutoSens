#include "autosens.h"
#include <Windows.h>

int CALLBACK WinMain(
	HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow) 
{
	AutoSens::mainloop();
	return EXIT_SUCCESS;
}