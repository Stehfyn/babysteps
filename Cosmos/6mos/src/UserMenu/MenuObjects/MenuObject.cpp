#include "Cosmos/Cosmos.h"
#include "Cosmos/UserMenus/MenuObjects/MenuObject.h"

namespace Game::UserMenu
{
	void TextSelection::Render(Cosmos& Cosmos)
	{
		for (int i = 0; i < Str.String.length(); i++)
		{
			Cosmos.DrawChar(Str.X + i, Str.Y, Str.String[i], Col);
		}
	}
	Button::Button()
	{

	}
	void Button::Render(Cosmos& Cosmos)
	{

	}
	TextSelection::TextSelection(int p_x, int p_y, const std::string& p_str, short p_defaultcol, short p_highlightedcol)
	{
		//really should check if coordinates are valid and throw something if not
		Str = { p_x, p_y, p_str };
		DefaultCol = p_defaultcol;
		HighlightedCol = p_highlightedcol;
		Col = DefaultCol;

		//init the rec
		Rec.X = p_x;
		Rec.Y = p_y;
		Rec.Width = Str.String.length();
		Rec.Height = 1;
	}
}