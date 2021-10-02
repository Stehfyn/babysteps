#ifndef CREDITSMENU_H
#define CREDITSMENU_H

#include "Cosmos/Cosmos.h"
#include "Cosmos/UserMenus/Menus/Menu.h"

namespace Game::UserMenu
{
	class CreditsMenu : public Menu
	{
	public:
		void Init(Cosmos& Cosmos);
		void Cleanup();
		void SelectObj(int menuObjNum, Cosmos& Cosmos);
		void UpdateMenuObjects(Cosmos& Cosmos);
		void AddMenuAmbienceToPipeline(Cosmos& Cosmos);
		static CreditsMenu* Instance()
		{
			if (m_CreditsMenu == nullptr)
			{
				m_CreditsMenu = new CreditsMenu();
			}
			return m_CreditsMenu;
		}
	private:
		CreditsMenu() {}
		CreditsMenu(const CreditsMenu& obj) {}
		static CreditsMenu* m_CreditsMenu;

	};
}
#endif