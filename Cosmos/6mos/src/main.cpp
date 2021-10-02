//Main Driver
#include "Cosmos/Cosmos.h"
#include "Cosmos/Globals.h"

int main()
{

	Game::Cosmos Cosmos;
	Game::primaryCol = 0x000C;
	while (Cosmos.Running())
	{
		Cosmos.ExecuteGameLoop();
	}

	ConsoleHandlerRoutine(CTRL_CLOSE_EVENT);

	return 0;
}