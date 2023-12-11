#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Windows.h>
class Globals
{
public:
	const char* games[4] = { "Apex", "CS2", "Minecraft" };
	int selectedGameFrom = 0;
	int selectedGameTo = 0;
	int gui = 1;

};
class Game {
public:
	float sensitivity = 1.0f;
	char cfgPath[260] = "";
	void SetCfgPath();
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