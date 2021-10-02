#include "Cosmos/Globals.h"
#include "Cosmos/Color/Color.h"
#include "Cosmos/Color/ColorManager.h"
#include "Cosmos/UserMenus/Menus/ColorMenu.h"

#include "Cosmos/GameState/GameState.h" //sus

#include "Cosmos/UserMenus/MenuObjects/MenuObject.h"
#include "Cosmos/Ambience/AmbienceObject.h"

//use an alias here
Game::UserMenu::ColorMenu* Game::UserMenu::ColorMenu::m_ColorMenu = 0;

namespace Game::UserMenu
{
	void ColorMenu::Init(Cosmos& Cosmos)
	{
		//MenuObjectsStack.clear();
		//AmbienceObjectsStack.clear();

		//MenuObject* PRIMARY = new TextSelection
		MenuObject* ANAGLYPH = new TextSelection(1, 7, "ANAGLYPH", 0x000F, 0x000B);
		MenuObject* COSMONAUT = new TextSelection(1, 9, "COSMONAUT", 0x000E, 0x000C);
		MenuObject* BOY_MEETS_WORLD = new TextSelection(1, 11, "BOY MEETS WORLD", 0x0003, 0x0005);
		MenuObject* CUSTOM = new TextSelection(1, 13, "CUSTOM", 0x000F, 0x000C);
		MenuObject* BACK = new TextSelection(38, 26, "BACK", 0x000F, 0x000C);
		MenuObjectsVec = { ANAGLYPH, COSMONAUT, BOY_MEETS_WORLD, CUSTOM, BACK };


		using namespace Ambience;

		//AmbienceObjectsVec = { ROLE, NAME, UNR, SCHOOL }; //SRS

	}
	void ColorMenu::Cleanup()
	{

	}
	void ColorMenu::SelectObj(int menuObjNum, Cosmos& Cosmos)
	{
		using namespace Game::Colors;
		switch (menuObjNum)
		{
		case 0:
		{
			
			Cosmos.ColorManager.m_colors[0] = FG_WHITE; //lines
			Cosmos.ColorManager.m_colors[1] = FG_WHITE; //fastest
			Cosmos.ColorManager.m_colors[2] = FG_RED; //slowest
			Cosmos.ColorManager.m_colors[3] = FG_CYAN; //middle
			Cosmos.ColorManager.m_colors[4] = FG_DARK_MAGENTA; //planet
			Cosmos.ColorManager.m_colors[5] = FG_WHITE; //text
			Cosmos.ColorManager.m_colors[6] = FG_CYAN; //highlight
			break;
		}
		case 1:
		{
			Cosmos.ColorManager.m_colors[0] = FG_RED;
			Cosmos.ColorManager.m_colors[1] = FG_WHITE;
			Cosmos.ColorManager.m_colors[2] = FG_WHITE;
			Cosmos.ColorManager.m_colors[3] = FG_WHITE;
			Cosmos.ColorManager.m_colors[4] = FG_YELLOW;
			Cosmos.ColorManager.m_colors[5] = FG_WHITE; //text
			Cosmos.ColorManager.m_colors[6] = FG_RED; //highlight
			break;
		}
		case 2:
		{
			Cosmos.ColorManager.m_colors[0] = FG_DARK_CYAN;
			Cosmos.ColorManager.m_colors[1] = FG_DARK_MAGENTA;
			Cosmos.ColorManager.m_colors[2] = FG_DARK_CYAN;
			Cosmos.ColorManager.m_colors[3] = FG_DARK_MAGENTA;
			Cosmos.ColorManager.m_colors[4] = FG_WHITE;
			Cosmos.ColorManager.m_colors[5] = BG_DARK_MAGENTA; //text
			Cosmos.ColorManager.m_colors[6] = BG_DARK_CYAN; //highlight
			break;
		}
		case 3:
		{
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
	void ColorMenu::UpdateMenuObjects(Cosmos& Cosmos)
	{
		//do some time shit with Cosmos.t_elapsed
		//pos = Speed (pixels per second) * t_elapsed;
		//int pos = (int)(float * float)


		float testPos = 0.0f;
		for (int i = 0; i < AmbienceObjectsVec.size(); i++)
		{
			Ambience::AmbienceObject* Current = AmbienceObjectsVec.at(i);
			if (!Current->IsAtFinalPos())
			{
				Current->SetPositionY(Current->GetY() - (Current->GetSpeed() * Cosmos.t_fElapsed));
			}
			//debug shit VVV
			testPos = Current->GetY();
		}

		//-------------COPIED from menu.cpp---------------
		for (int i = 0; i < MenuObjectsVec.size(); i++)
		{
			if (MenuObjectsVec.at(i)->Highlighted)
			{
				MenuObjectsVec.at(i)->Col = MenuObjectsVec.at(i)->HighlightedCol;
			}
			else
			{
				MenuObjectsVec.at(i)->Col = MenuObjectsVec.at(i)->DefaultCol;
			}
		}

	}
	void ColorMenu::AddMenuAmbienceToPipeline(Cosmos& Cosmos)
	{
		//a way to identify and discern the Logo objects within this vector
		//from how we want to render them
		for (int i = 0; i < AmbienceObjectsVec.size(); i++)
		{
			AmbienceObjectsVec.at(i)->RenderFromToY(2, 27, Cosmos);
		}
	}
}