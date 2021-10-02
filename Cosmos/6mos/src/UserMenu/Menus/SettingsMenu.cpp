#include "Cosmos/GameState/GameState.h"
#include "Cosmos/UserMenus/Menus/SettingsMenu.h"
#include "Cosmos/UserMenus/Menus/CreditsMenu.h"
#include "Cosmos/UserMenus/Menus/ColorMenu.h"

//use an alias here
Game::UserMenu::SettingsMenu* Game::UserMenu::SettingsMenu::m_SettingsMenu = 0;
namespace Game::UserMenu 
{
	

	void SettingsMenu::Init(Cosmos& Cosmos)
	{
		MenuObject* ASSET_EDITOR = new TextSelection(1, 7, "ASSETS", Cosmos.ColorManager.m_colors[5], Cosmos.ColorManager.m_colors[6]);
		MenuObject* COLORS = new TextSelection(1, 9, "COLORS", Cosmos.ColorManager.m_colors[5], Cosmos.ColorManager.m_colors[6]);
		MenuObject* CONTROLS = new TextSelection(1, 11, "CONTROLS", Cosmos.ColorManager.m_colors[5], Cosmos.ColorManager.m_colors[6]);
		MenuObject* CREDITS = new TextSelection(1, 13, "CREDITS", Cosmos.ColorManager.m_colors[5], Cosmos.ColorManager.m_colors[6]);
		MenuObject* BACK = new TextSelection(38, 26, "BACK", Cosmos.ColorManager.m_colors[5], Cosmos.ColorManager.m_colors[6]);
		MenuObjectsVec = { ASSET_EDITOR, COLORS, CONTROLS, CREDITS, BACK };
	}
	void SettingsMenu::Cleanup()
	{

	}
	void SettingsMenu::SelectObj(int menuObjNum, Cosmos& Cosmos)
	{
		switch (menuObjNum)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			Cosmos.PeekState()->PushUserMenu(ColorMenu::Instance(), Cosmos);
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			Cosmos.PeekState()->PushUserMenu(CreditsMenu::Instance(), Cosmos);
			break;
		}
		case 4:
		{
			Cosmos.PeekState()->PopUserMenu();
			break;
		}
		default:
		{
			break;
		}
		}
	}
	void SettingsMenu::AddMenuAmbienceToPipeline(Cosmos& Cosmos)
	{

	}
}