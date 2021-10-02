#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "Cosmos/Cosmos.h"
#include "Cosmos/UserMenus/Menus/Menu.h"

namespace Game::UserMenu 
{
	class SettingsMenu : public Menu
	{
	public:
		void Init(Cosmos& Cosmos);
		void Cleanup();
		void SelectObj(int menuObjNum, Cosmos& Cosmos);
		void AddMenuAmbienceToPipeline(Cosmos& Cosmos);
		static SettingsMenu* Instance()
		{
			if (m_SettingsMenu == nullptr)
			{
				m_SettingsMenu = new SettingsMenu();
			}
			return m_SettingsMenu;
		}
	private:
		SettingsMenu() {}
		SettingsMenu(const SettingsMenu& obj) {}
		static SettingsMenu* m_SettingsMenu;

	};
}
#endif 
