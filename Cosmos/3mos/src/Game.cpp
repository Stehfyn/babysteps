#include "Game.h"
#include "Buffer.h"
#include "Windows.h"

#define CTRL input[0] 
#define LEFT input[1]
#define RIGHT input[2]
#define SPACE input[3]

void::Game::getInput(Buffer buffer, int tickCounter) //implicitly tracks tickCount
{
	//Obtain input from user for current tick
	for (int k = 0; k < 4; k++)								// Ctrl L R S
		input[k] = (0x8000 & GetKeyState((unsigned char)("\x11\x25\x27\x20"[k]))) != 0;

	//Clear delay flags
	if (!input[1])
		holdL = false;
	if (!input[2])
		holdR = false;

	if (CTRL)
	{
		if (LEFT && !holdL && player.xPos != 0)
		{
			buffer.edit(player.xPos, player.yPos, L' ');
			player.xPos--;
			holdL = true;
		}
		if (RIGHT && !holdR && player.xPos != 79)
		{
			buffer.edit(player.xPos, player.yPos, L' ');
			player.xPos++;
			holdR = true;
		}
	}
	if (LEFT && !CTRL)
	{
		if (player.xPos != 0)
		{
			buffer.edit(player.xPos, player.yPos, L' ');
			player.xPos--;
		}
	}
	if(RIGHT && !CTRL)
	{
		if (player.xPos != 79)
		{
			buffer.edit(player.xPos, player.yPos, L' ');
			player.xPos++;
		}
	}
	if (SPACE)
	{
		if (!shootDelay)
		{
			shoot();
			shootTick = tickCounter;
			//shootDelay = true;
		}
	}
}
void::Game::shoot()
{
	//add laser
	if (laserIndex == 120)
		laserIndex = 0;
	laserList[laserIndex].xPos = player.xPos;
	laserList[laserIndex].yPos = player.yPos - 1; //can do direct y because player will be overwrite the laser
	laserList[laserIndex].character = L'\u2551';
	laserList[laserIndex].active = true;
	laserIndex++;
	shotsFired++;
}
void::Game::addEnemy(int x, int y, int health, wchar_t enemy)
{
	if (enemyIndex == 120)
		enemyIndex = 0;
	enemyList[enemyIndex].xPos = x;
	enemyList[enemyIndex].yPos = y; //can do direct y because player will be overwrite the laser
	enemyList[enemyIndex].character = enemy;
	enemyList[enemyIndex].active = true;
	enemyIndex++;
}
void::Game::advanceEnemy(Buffer buffer)
{
	for (int i = 0; i < 120; i++)
		if (enemyList[i].active == true)
		{
			buffer.edit(enemyList[i].xPos, enemyList[i].yPos, L' ');
			enemyList[i].yPos++;
			if (enemyList[i].yPos == 30)
				deleteEnemy(i);
		}
}
void::Game::advanceLaser(Buffer buffer)
{
	for (int i = 0; i < 120; i++)
		if (laserList[i].active == true)
		{
			buffer.edit(laserList[i].xPos, laserList[i].yPos, L' ');
			laserList[i].yPos--;
			if (laserList[i].yPos == -1)
				deleteLaser(i);
		}
}
void::Game::check(Buffer buffer)
{
	for (int i = 0; i < 120; i++)
		for (int j = 0; j < 120; j++)
			if(laserList[i].active && enemyList[j].active)
				if (laserList[i].xPos == enemyList[j].xPos && laserList[i].yPos == enemyList[j].yPos)
				{
					deleteLaser(i);
					buffer.edit(enemyList[j].xPos, enemyList[j].yPos, L' ');
					deleteEnemy(j);
					numHits++;
					score += 1000;
				}
}
void::Game::printPlayer(Buffer buffer)
{
	buffer.edit(player.xPos, player.yPos, player.character);
}
void::Game::printEnemy(Buffer buffer)
{
	for (int i = 0; i < 120; i++)
		if (enemyList[i].active == true)
			buffer.edit(enemyList[i].xPos, enemyList[i].yPos, enemyList[i].character);
}
void::Game::printLaser(Buffer buffer)
{
	for (int i = 0; i < 120; i++)
		if (laserList[i].active == true)
			buffer.edit(laserList[i].xPos, laserList[i].yPos, laserList[i].character);
}
void::Game::deleteLaser(int index)
{
	laserList[index].active = false;
}
void::Game::deleteEnemy(int index)
{
	enemyList[index].active = false;
}
void::Game::addScore(int add)
{
	score += add;
}
double::Game::calcAccuracy()
{
	accuracy = numHits / shotsFired;
	return accuracy;
}
int::Game::getScore()
{
	return score;
}
int::Game::getRemaining()
{
	int count{};
	for (int i{}; i < 120; i++)
		if (enemyList[i].active)
			count++;
	return count;
}