#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <windows.h>
#include <shobjidl.h>
#include <shlwapi.h>
#include <iostream>
#include <string>

#pragma comment(lib, "shlwapi.lib")
class Globals
{
public:
	const char* games[3] = { "Apex", "CS2", "Minecraft" };
	//Game* gameList[3] = { new Apex, new CounterStrike2 , new Minecraft };
	int selectedGameFrom = 0;
	int selectedGameTo = 0;
	int gui = 1;
};
class Game {
public:
	float sensitivity = 1.0f;
	std::wstring cfgPath;
	void SetCfgPath();
};

class CounterStrike2 : public Game
{
public:
	float multiplier = 0;
private:

};

class Apex : public Game
{
public:
	float multiplier = 0;
private:

};

class Minecraft : public Game
{
public:
	float multiplier = 0;
	std::string pathRecomendation = "%appdata%/.minecraft/options.txt";
private:

};
#endif // COMPONENTS_H