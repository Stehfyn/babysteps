#pragma once
#include "Buffer.h"
class Game
{
public:
	void getInput(Buffer, int);
	void shoot();
	void addEnemy(int, int, int, wchar_t);
	void advanceEnemy(Buffer);
	void advanceLaser(Buffer);
	void check(Buffer);
	void printPlayer(Buffer);
	void printEnemy(Buffer);
	void printLaser(Buffer);
	void deleteLaser(int);
	void deleteEnemy(int);
	void addScore(int);
	double calcAccuracy();
	int getScore();
	int getRemaining();
private:
	struct Player
	{
		int xPos{39};
		int yPos{27};
		int lives{ 3 };
		int inventory[10]{};
		wchar_t character{ L'^' };
	};
	struct Enemy
	{
		int xPos{};
		int yPos{};
		int health{};
		wchar_t character{};
		bool active{};
	};
	struct Laser
	{
		int xPos{};
		int yPos{};
		wchar_t character{};
		bool dual{};
		bool active{};
	};
	struct Item
	{
		int xPos{};
		int yPos{};
		wchar_t item{};
	};

	Player player{};

	Enemy enemyList[120];
	Laser laserList[120];
	Item itemList[120];

	int score{};
	double shotsFired{};
	double numHits{};
	double accuracy{};

	int enemyIndex{};
	int laserIndex{};

	int input[4];
	bool holdL{ false };
	bool holdR{ false };
	bool shootDelay{ false };
	int shootTick{};
};