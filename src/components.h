#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Windows.h>

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

class Apex: public Game
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