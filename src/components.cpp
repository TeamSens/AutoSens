#include "components.h"

void Game::SetCfgPath()
{
	// Open native file dialog
	OPENFILENAME ofn;
	char szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All Files\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn)) {

		strcpy_s(cfgPath, sizeof(cfgPath), szFile);
	}
}


float Game::toGlobalSense(Game game)
{
	/* My thought process here is u convert your game's sensitivity
	to a global one, which can than be edited to all different games, 
	this makes it so we dont need to do a bunch of ghetto math to convert
	game to game. */
}