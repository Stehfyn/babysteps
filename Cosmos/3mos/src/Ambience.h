#pragma once
#include "Buffer.h"
#include <random>
class Ambience
{
public:
	void addStar(int);
	void advanceStars(Buffer);
	void printStars(Buffer);
	void deleteStar(int);
private:
	struct Star
	{
		int xPos{};
		int yPos{};
		wchar_t character{L'.'};
		bool active{};
	};
	Star stars[120];
	int starIndex{};
	int lastX{};
};

