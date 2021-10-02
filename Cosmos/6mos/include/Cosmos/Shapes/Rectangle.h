#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace Game::Shapes
{
	class Rectangle
	{
	public:
		Rectangle(int p_x, int p_y, int p_width, int p_height);
		bool isWithin(int p_x, int p_y);

		int Y;
		int X;
		int Width;
		int Height;
	};
}
#endif