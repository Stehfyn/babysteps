#include "Cosmos/Cosmos.h"
#include "Cosmos/GameState/GameState.h"
#include "Cosmos/GameState/Demo.h"

#include "Cosmos/UserMenus/Menus/Menu.h"
#include "Cosmos/UserMenus/Menus/TopMenu.h"
#include "Cosmos/UserMenus/Menus/SettingsMenu.h"

#include "Cosmos/UserMenus/MenuObjects/MenuObject.h"

//use an alias here


namespace Game::UserMenu 
{
	//using Game::UserMenu::TopMenu;
	//using Game::UserMenu::MenuObject;
	using Game::GS::Demo;
	TopMenu* TopMenu::m_TopMenu = 0;

	void TopMenu::Init(Cosmos& Cosmos)
	{
		//push back menu objects for menu
		MenuObject* LAUNCH = new TextSelection(37, 16, "LAUNCH", Cosmos.ColorManager.m_colors[5], Cosmos.ColorManager.m_colors[6]);
		MenuObject* PRACTICE = new TextSelection(36, 18, "PRACTICE", Cosmos.ColorManager.m_colors[5], Cosmos.ColorManager.m_colors[6]);
		MenuObject* HIGH_SCORES = new TextSelection(35, 20, "HIGH SCORES", Cosmos.ColorManager.m_colors[5], Cosmos.ColorManager.m_colors[6]);
		MenuObject* SETTINGS = new TextSelection(36, 22, "SETTINGS", Cosmos.ColorManager.m_colors[5], Cosmos.ColorManager.m_colors[6]);
		MenuObject* EXIT = new TextSelection(38, 24, "EXIT", Cosmos.ColorManager.m_colors[5], Cosmos.ColorManager.m_colors[6]);

		MenuObjectsVec = { LAUNCH, PRACTICE, HIGH_SCORES, SETTINGS, EXIT };
	}
	void TopMenu::Cleanup()
	{

	}
	void TopMenu::SelectObj(int menuObjNum, Cosmos& Cosmos)
	{
		switch (menuObjNum)
		{
		case 0:
		{
			Cosmos.PeekState()->PopUserMenu();
			Cosmos.PushState(Demo::Instance());
			break;
		}
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			Cosmos.PeekState()->PushUserMenu(SettingsMenu::Instance(), Cosmos);
			break;
		}
		case 4:
		{
			Cosmos.Quit();
			break;
		}
		default:
		{
			break;
		}
		}
	}
	void TopMenu::AddMenuAmbienceToPipeline(Cosmos& Cosmos)
	{
		std::wstring top = L"┌─┐┌─┐┌─┐┌┬┐┌─┐┌─┐";
		std::wstring mid = L"│  │ │└─┐││││ │└─┐";
		std::wstring bot = L"└─┘└─┘└─┘┴ ┴└─┘└─┘";

		for (int i = 0; i < top.length(); i++)
			Cosmos.DrawChar(31 + i, 5, top[i], 0x000D);
		for (int i = 0; i < mid.length(); i++)
			Cosmos.DrawChar(31 + i, 6, mid[i], 0x000F);
		for (int i = 0; i < bot.length(); i++)
			Cosmos.DrawChar(31 + i, 7, bot[i], 0x000F);
	}
}