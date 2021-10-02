#pragma once
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <codecvt>
#include "Buffer.h"
#include "Game.h"
class HUD
{
public:
	void displayScore(int, Buffer);
	void displayEnemies(int, Buffer);
	void displayAccuracy(double, Buffer);
	void displayLine(Buffer);
private:
	std::wstring currAccString{};
	std::wstring lastAccString{};

	std::wstring scoreString{};

	std::wstring currRemainString{};
	std::wstring lastRemainString{};

	wchar_t* scoreArray{};
};