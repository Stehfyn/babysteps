#include "Cosmos/Shapes/Rectangle.h"

namespace Game::Shapes 
{
	Rectangle::Rectangle(int p_x, int p_y, int p_width, int p_height) : X(p_x), Y(p_y), Width(p_width), Height(p_height)
	{

	}
	bool Rectangle::isWithin(int p_x, int p_y)
	{
		int topEdge = Y;
		int botEdge = Y + Height - 1;

		int leftEdge = X;
		int rightEdge = X + Width - 1;

		if ((p_x >= leftEdge && p_x <= rightEdge) &&
			(p_y >= topEdge && p_y <= botEdge))
		{
			return true;
		}

		return false;
	}
}