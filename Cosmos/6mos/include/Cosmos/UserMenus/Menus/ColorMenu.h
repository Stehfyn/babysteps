#ifndef COLORMENU_H
#define COLORMENU_H
#include "Cosmos/Cosmos.h"
#include "Cosmos/UserMenus/Menus/Menu.h"

namespace Game::UserMenu
{
	class ColorMenu : public Menu
	{
	public:
		void Init(Cosmos& Cosmos);
		void Cleanup();
		void SelectObj(int menuObjNum, Cosmos& Cosmos);
		void UpdateMenuObjects(Cosmos& Cosmos);
		void AddMenuAmbienceToPipeline(Cosmos& Cosmos);
		static ColorMenu* Instance()
		{
			if (m_ColorMenu == nullptr)
			{
				m_ColorMenu = new ColorMenu();
			}
			return m_ColorMenu;
		}
	private:
		ColorMenu() {}
		ColorMenu(const ColorMenu& obj) {}
		static ColorMenu* m_ColorMenu;
	};
}
#endif
