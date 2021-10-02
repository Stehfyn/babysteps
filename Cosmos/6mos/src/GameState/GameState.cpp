#include "Cosmos/Cosmos.h"
#include "Cosmos/GameState/GameState.h"
#include "Cosmos/UserMenus/Menus/Menu.h"

namespace Game::GS
{

	GameState::GameState()
	{
		InputHandler = new class InputHandler();
	}

	void GameState::ProcessInput(Cosmos& Cosmos)
	{
		/** Game Commands **/
		CommandQueue.clear();
		if (Cosmos.CE_InFocus)
		{
			CommandQueue = InputHandler->HandleInput(Cosmos);
		}

		/** GameState Logic **/

		/** Menu Logic **/
		if(!IsUserMenuEmpty())
			PeekUserMenu()->ProcessMenuInput(Cosmos);
	}
	bool GameState::UpdateGameLogic(Cosmos& Cosmos)
	{
		/** Execute Commands **/
		for (int i = 0; i < CommandQueue.size(); i++)
		{
			CommandQueue.at(i)->Execute(Cosmos);
		}

		/** GameState explicit update (Will include core game objects) +-**/
		UpdateGameStateObjects(Cosmos);

		/** Menu explicit update **/

		if (!IsUserMenuEmpty())
		{
			PeekUserMenu()->UpdateMenuAmbienceObjects(Cosmos);
			PeekUserMenu()->UpdateMenuObjects(Cosmos);
		}


		//we should consolidate above into one UpdateObjects()
		


		/** ABOVE should just be:
		*	-Execute Commands
		*	-Update GameState Objects(Ambience)
		*	-Update Menu Objects(Ambience + Menu)
		**/

		
		//link to a command
		return true;
	}
	void GameState::AddToPipeline(Cosmos& Cosmos)
	{
		//Separate State Ambience from UserMenu Ambience/Objects
		// Posterity -> :) Cosmos.PeekState()->AddGameStateObjectsToPipeline(Cosmos);

		//Gamestate specific
		this->AddGameStateObjectsToPipeline(Cosmos);

		//User Menu specific

		if (!IsUserMenuEmpty())
		{
			PeekUserMenu()->AddMenuAmbienceToPipeline(Cosmos);
			PeekUserMenu()->AddMenuObjectsToPipeline(Cosmos);
		}
	}
	bool GameState::IsUserMenuEmpty() const
	{
		return UserMenuStack.size() == 0;
	}
	void GameState::PushUserMenu(Menu* newMenu, Cosmos& Cosmos)
	{

		UserMenuStack.push_back(newMenu);
		UserMenuStack.back()->Init(Cosmos);

	}
	void GameState::PopUserMenu()
	{

		UserMenuStack.back()->Cleanup();
		UserMenuStack.pop_back();

	}
	Menu* GameState::PeekUserMenu()
	{
		if(!IsUserMenuEmpty())
			return UserMenuStack.back();
	}
}