#include "Cosmos/GameState/GameState.h"
#include "Cosmos/UserMenus/Menus/Menu.h"

#include "Cosmos/Ambience/AmbienceObject.h"
#include "Cosmos/UserMenus/MenuObjects/MenuObject.h"

using Game::Cosmos;
using namespace Game::Ambience;
using namespace Game::UserMenu;

void Menu::Select(Cosmos& Cosmos)
{
	for (int i = 0; i < MenuObjectsVec.size(); i++)
	{
		if (MenuObjectsVec.at(i)->Highlighted)
		{
			Cosmos.PeekState()->PeekUserMenu()->SelectObj(i, Cosmos);
		}
	}
}
void Menu::ProcessMenuInput(Cosmos& Cosmos)
{
	Cursor.X = Cosmos.Mouse.CursorState.X;
	Cursor.Y = Cosmos.Mouse.CursorState.Y;

	for (int i = 0; i < MenuObjectsVec.size(); i++)
	{
		if (MenuObjectsVec.at(i)->Rec.isWithin(Cursor.X, Cursor.Y))
		{
			MenuObjectsVec.at(i)->Highlighted = true;
		}
		else
		{
			MenuObjectsVec.at(i)->Highlighted = false;
		}
	}

	//this->GetMenuObjects()
	//then we check these coordinates against the coordinates
	//of the menu objects, and flag the highlight function
	//of a menu object if the cursor is within it's rectangle
}
void Menu::UpdateMenuObjects(Cosmos& Cosmos)
{
	//Factory update menuobjects based off commands/cursor position
	//i.e. change color
	for (int i = 0; i < MenuObjectsVec.size(); i++)
	{
		if (MenuObjectsVec.at(i)->Highlighted)
		{
			MenuObjectsVec.at(i)->Col = Cosmos.ColorManager.m_colors[6];
		}
		else
		{
			MenuObjectsVec.at(i)->Col = Cosmos.ColorManager.m_colors[5];
		}
	}
}
void Menu::AddMenuAmbienceToPipeline(Cosmos& Cosmos)
{
	for (int i = 0; i < AmbienceObjectsVec.size(); i++)
	{
		AmbienceObjectsVec.at(i)->Render(Cosmos);
	}
}
void Menu::AddMenuObjectsToPipeline(Cosmos& Cosmos)
{
	//Cosmos.PeekState()->PeekUserMenu()->AddMenuObjectsToPipeline
	for (int i = 0; i < MenuObjectsVec.size(); i++)
	{
		MenuObjectsVec.at(i)->Render(Cosmos);
	}
}