#ifndef MAINMENU_H
#define MAINMENU_H

#include "Cosmos/Cosmos.h"
#include "Cosmos/GameState/GameState.h"

#include <iostream>

namespace Game::GS
{
	using Game::Cosmos;

	class MainMenu : public GameState
	{
	public:
		void Init(Cosmos& Cosmos);
		void Cleanup() {}

		void Pause() {}
		void Resume(Cosmos& Cosmos);

		void UpdateGameStateObjects(Cosmos& Cosmos);
		void UpdateMenuObjects(Cosmos& Cosmos) { }
		void AddGameStateObjectsToPipeline(Cosmos& Cosmos);
		void AddMenuObjectsToPipeline(Cosmos& Cosmos) { }

		static MainMenu* Instance()
		{
			if (m_MainMenu == nullptr)
			{
				m_MainMenu = new MainMenu();
			}
			return m_MainMenu;
		}

	private:
		MainMenu() {}
		MainMenu(const MainMenu& obj) {}
		static MainMenu* m_MainMenu;
	};
}
#endif