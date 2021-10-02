#ifndef TOPMENU_H
#define TOPMENU_H

#include "Cosmos/Cosmos.h"
#include "Cosmos/UserMenus/Menus/Menu.h"

namespace Game::UserMenu
{
	class TopMenu : public Menu
	{
	public:
		void Init(Cosmos& Cosmos);
		void Cleanup();
		void SelectObj(int menuObjNum, Cosmos& Cosmos);
		void AddMenuAmbienceToPipeline(Cosmos& Cosmos);
		static TopMenu* Instance()
		{
			if (m_TopMenu == nullptr)
			{
				m_TopMenu = new TopMenu();
			}
			return m_TopMenu;
		}
	private:
		TopMenu() {}
		TopMenu(const TopMenu& obj) {}
		static TopMenu* m_TopMenu;
	};
}
#endif
