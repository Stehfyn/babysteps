
#include <iostream>
#include <thread>
#include <chrono>
#include "Buffer.h"
#include "Ambience.h"
#include "Game.h"
#include "HUD.h"
#include "GameState.h"
#include "Keyboard.h"
#include "Gamepad.h"

#define TICK_RATE 16.67ms //60 fps
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 30

COORD cdBuffer {SCREEN_WIDTH, SCREEN_HEIGHT};
_SMALL_RECT srWindow {0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1};
using namespace std;

int main()
{
	GameState MainMenu(SCREEN_WIDTH, SCREEN_HEIGHT);
	GameState Practice(SCREEN_WIDTH, SCREEN_HEIGHT);
	GameState Game(SCREEN_WIDTH, SCREEN_HEIGHT);

	Keyboard keyboard;
	Gamepad gamepad(1);
	int state{MAINMENU};
	while (state != EXIT) 
	{
		switch (state)
		{
		case MAINMENU:
		{
			MainMenu.getBuffer().setHandle();
			while (state == MAINMENU)
			{
				auto start = std::chrono::high_resolution_clock::now();

				state = MainMenu.mm_getInput(keyboard, gamepad);
				MainMenu.mm_display();
				//MoveWindow(MainMenu.getBuffer().getWnd(), 80, 30, 600, 300, false);

				SetConsoleWindowInfo(MainMenu.getBuffer().getHandle(), true, &srWindow);
				SetConsoleScreenBufferSize(MainMenu.getBuffer().getHandle(), cdBuffer);
				
				auto end = chrono::high_resolution_clock::now();
				auto elapsed = chrono::duration_cast<chrono::microseconds>(start - end);
				this_thread::sleep_for((TICK_RATE - elapsed) / 2);
			}
			MainMenu.getBuffer().closeHandle();
			break;
		}
		case PRACTICE: //practice
		{
			Practice.getBuffer().setHandle();
			while (state == PRACTICE)
			{
				auto start = std::chrono::high_resolution_clock::now();


				auto end = chrono::high_resolution_clock::now();
				auto elapsed = chrono::duration_cast<chrono::microseconds>(start - end);
				this_thread::sleep_for((TICK_RATE - elapsed) / 2);
			}
		}
		case 10:
		{
			Buffer buffer(SCREEN_WIDTH, SCREEN_HEIGHT);
			buffer.setHandle();
			Ambience ambience{};
			::Game game{};
			HUD hud{};
			//buffer.setWindow();
			int tickCounter{};

			//game loop
			bool run = true;
			while (run)
			{
				//take clock time
			//===============
				auto start = std::chrono::high_resolution_clock::now();
				//get user input
				game.getInput(buffer, tickCounter);
				//game.check(buffer);
				//--input buffer

				//get game logic input
				//--game logic buffer
				//compare and calculate next frame
				if (tickCounter % 4 == 0)
				{
					ambience.addStar(0);
					ambience.advanceStars(buffer);
				}
				if (tickCounter % 1 == 0)
				{
					game.advanceLaser(buffer);
				}
				ambience.printStars(buffer);
				if (tickCounter % 30 == 0)
				{
					game.advanceEnemy(buffer);
				}
				if (tickCounter % 60 == 0)
				{
					game.addEnemy(rand() % 80, 0, 1, L'?');
				}
				game.check(buffer);
				//===============
				//take clock time
				//fix framerate based on elapsed
				//debug - draw player

				game.printEnemy(buffer);
				game.printLaser(buffer);
				game.printPlayer(buffer);
				//update frame with next frame
				//game.addScore(1);
				hud.displayScore(game.getScore(), buffer);
				hud.displayEnemies(game.getRemaining(), buffer);
				hud.displayAccuracy(game.calcAccuracy(), buffer);
				hud.displayLine(buffer);
				buffer.update();
				tickCounter++;
				auto end = chrono::high_resolution_clock::now();
				auto elapsed = chrono::duration_cast<chrono::microseconds>(start - end);
				this_thread::sleep_for((TICK_RATE - elapsed) / 2);
			}
			break;
		}
		}
	}
	/*Buffer buffer(ScreenWidth, ScreenHeight);
	Ambience ambience{};
	Game game{};
	HUD hud{};
	//buffer.setWindow();
	int tickCounter{};

	//game loop
	bool run = true;
	while (run)
	{
     		//take clock time
		//===============
		auto start = std::chrono::high_resolution_clock::now();
		//get user input
		game.getInput(buffer, tickCounter);
		//game.check(buffer);
		//--input buffer

		//get game logic input
		//--game logic buffer
		//compare and calculate next frame
		if (tickCounter % 4 == 0)
		{
			ambience.addStar();
			ambience.advanceStars(buffer);
		}
		if (tickCounter % 1 == 0)
		{
			game.advanceLaser(buffer);
		}
		ambience.printStars(buffer);
		if (tickCounter % 30 == 0)
		{
			game.advanceEnemy(buffer);
		}
		if (tickCounter % 60 == 0)
		{
			game.addEnemy(rand() % 80, 0, 1, L'?');
		}
		game.check(buffer);
		//===============
		//take clock time
		//fix framerate based on elapsed
		//debug - draw player

		game.printEnemy(buffer);
		game.printLaser(buffer);
		game.printPlayer(buffer);
		//update frame with next frame
		//game.addScore(1);
		hud.displayScore(game.getScore(), buffer);
		hud.displayEnemies(game.getRemaining(), buffer);
		hud.displayAccuracy(game.calcAccuracy(), buffer);
		hud.displayLine(buffer);
		buffer.update();
		tickCounter++;
		auto end = chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::microseconds>(start - end);
		this_thread::sleep_for((TICK_RATE - elapsed)/2);
	}*/
	//system("taskkill /IM Cosmos.exe /F");
	return 0;
}