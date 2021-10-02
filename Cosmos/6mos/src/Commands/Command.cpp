#include "Cosmos/Commands/Command.h"
#include "Cosmos/GameState/GameState.h"
#include "Cosmos/UserMenus/Menus/Menu.h"

namespace Game::Commands
{
	using Game::Cosmos;
	using Game::GS::GameState;
	using Game::UserMenu::Menu;
	using Game::UserMenu::MenuObject;

	void Select::Execute(Cosmos& Cosmos)
	{
		if(!Cosmos.PeekState()->IsUserMenuEmpty())
			Cosmos.PeekState()->PeekUserMenu()->Select(Cosmos);
		else
			Cosmos.PopState();
	}
}