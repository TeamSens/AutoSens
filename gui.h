#pragma once

#include<iostream>

class interface
{
public:
	void gui();
	const int x = 500, y = 200;
	int currentGame = 0;
	int newGame = 1;
private:
	bool oppened;
	int numberOfGames = 3;
};
