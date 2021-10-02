#ifndef MENUOBJECT_H
#define MENUOBJECT_H

#include "Cosmos/Cosmos.h"
#include "Cosmos/Shapes/Rectangle.h"
#include "Cosmos/UserMenus/MenuObjects/Text.h"
#include <string>

namespace Game::UserMenu 
{
	using Game::Shapes::Rectangle;

	class MenuObject
	{
	public:
		//TODO: MenuObject(); Constructors
		MenuObject() : Rec(0,0,0,0) { }
		Rectangle Rec;
		Text Str;

		bool Highlighted{};
		short Col;
		short DefaultCol;
		short HighlightedCol;
	public:
		virtual void Render(class Cosmos& Cosmos) = 0;
		//Select does a specific action based off not the type of the
		//menu object but the menu object itself
	};

	class TextSelection : public MenuObject
	{
	public:
		TextSelection(int p_x, int p_y, const std::string& p_str, short p_defaultcol, short p_highlightedcol);
		void Render(Cosmos& Cosmos);
	};
	class Button : public MenuObject
	{
	public:
		Button();
		void Render(Cosmos& Cosmos);
	};
	
}
#endif
