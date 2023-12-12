#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Windows.h>
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
	char cfgPath[260] = "";
	void SetCfgPath();
	float toGlobalSense(Game game);
};

class CounterStrike2 : public Game
{
public:
private:

};

class Apex : public Game
{
public:
private:

};

class Minecraft : public Game
{
public:
private:

};
#endif // COMPONENTS_H