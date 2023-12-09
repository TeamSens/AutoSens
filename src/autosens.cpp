#include "autosens.h"
#include "gui.h"

void AutoSens::mainloop()
{
	gui::CreateHWindow("AutoSens", "sns");
	gui::CreateDevice();
	gui::CreateImGui();

	while (gui::exit)
	{
		gui::BeginRender();
		gui::Render();
		gui::EndRender();
	}

	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();
}