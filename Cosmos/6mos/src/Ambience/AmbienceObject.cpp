#include "Cosmos/Ambience/AmbienceObject.h"
#include <iterator>

namespace Game::Ambience 
{
	Star::Star(int p_x, int p_y, wchar_t p_wchar, short p_col)
	{
		X = p_x;
		Y = p_y;
		Character = p_wchar;
		Col = p_col;
		Active = true;
	}
	void Star::Render(Cosmos& Cosmos)
	{
		Cosmos.DrawChar((int)round(X), (int)round(Y), Character, Col);
	}
	void Star::RenderFromToX(int p_x1, int p_x2, Cosmos& Cosmos)
	{
		//assumption is that stars begin within range, else they will be instantly destroyed
		int XPos = round(X);

		if ((XPos > p_x1) && (XPos < p_x2))
		{
			Render(Cosmos);
		}
		else
		{
			Active = false;
		}
	}
	void Star::RenderFromToY(int p_y1, int p_y2, Cosmos& Cosmos)
	{
		int YPos = round(Y);

		if ((YPos > p_y1) && (YPos < p_y2))
		{
			Render(Cosmos);
		}
		else
		{
			Active = false;
		}
	}
	void Star::RenderInRangeXY(int p_x1, int p_x2, int p_y1, int p_y2, Cosmos& Cosmos)
	{
		int XPos = X;
		int YPos = Y;

		if ((XPos >= p_x1) && (XPos <= p_x2) && (YPos >= p_y1) && (YPos <= p_y2))
		{
			Render(Cosmos);
		}
		else
		{
			Active = false;
		}
	}
	void Star::SetDirection(int p_dir)
	{
		if (p_dir >= 0 && p_dir <= 7)
		{
			Dir = p_dir;
		}
		else
		{
			throw "lmao wrong";
		}
	}
	bool Star::NeedsDestroy(Cosmos& Cosmos)
	{
		return !Active;
	}
	void Star::CheckRange(Cosmos& Cosmos)
	{
		if (!Range.isWithin(round(X), round(Y)))
		{
			Active = false;
		}
	}
	void AmbienceObject::ShowRange(Cosmos& Cosmos)
	{
		std::string x = std::to_string(Range.Width);
		std::string y = std::to_string(Range.Height);

		for (int i = 0; i < x.length(); i++)
		{
			Cosmos.DrawChar(0 + i, 5, x[i], 0x000F);
		}
		for (int i = 0; i < y.length(); i++)
		{
			Cosmos.DrawChar(0 + i, 6, y[i], 0x000F);
		}
	}
	void Star::Advance(Cosmos& Cosmos)
	{
		/*
		* West = 0
		* Northwest = 1
		* North = 2
		* Northeast = 3
		* East = 4
		* Southeast = 5
		* South = 6
		* Southwest = 7
		*/

		switch (Dir)
		{
		case 0:
		{
			X -= Speed * Cosmos.t_fElapsed;
			break;
		}
		case 1:
		{
			X -= Speed * Cosmos.t_fElapsed;
			Y -= Speed * Cosmos.t_fElapsed;
			break;
		}
		case 2:
		{
			Y -= Speed * Cosmos.t_fElapsed;
			break;
		}
		case 3:
		{
			X += Speed * Cosmos.t_fElapsed;
			Y -= Speed * Cosmos.t_fElapsed;
			break;
		}
		case 4:
		{
			X += Speed * Cosmos.t_fElapsed;
			break;
		}
		case 5:
		{
			X += Speed * Cosmos.t_fElapsed;
			Y += Speed * Cosmos.t_fElapsed;
			break;
		}
		case 6:
		{
			Y += Speed * Cosmos.t_fElapsed;
			break;
		}
		case 7:
		{
			X -= Speed * Cosmos.t_fElapsed;
			Y += Speed * Cosmos.t_fElapsed;
			break;
		}
		default:
		{
			break;
		}
		}
	}
	Logo::Logo(int p_x, int p_y, int p_width, int p_height)
	{
		//Constructor should just be for main fields
		//write getters and setters for LogoCharMap info
		X = p_x;
		Y = p_y;
		Width = p_width;
		Height = p_height;

		Str = {};
	}
	void AmbienceObject::SetStr(std::wstring p_str)
	{
		Str = p_str;
	}

	void Logo::SetMap(int p_int, wchar_t p_wchar, short p_col)
	{
		/*if (!(p_int >= 0 && p_int <= 3))
		{
			throw "oopsies";
		}
		else
		{
			Map[p_int].WChar = p_wchar;
			Map[p_int].Col = p_wchar;
		}*/
		Map[p_int].WChar = p_wchar;
		Map[p_int].Col = p_col;
	}
	void AmbienceObject::SetSpeed(int p_speed)
	{
		//TODO: Implement reasonable speed checking
		Speed = p_speed;
	}
	void AmbienceObject::SetPositionX(int p_x)
	{
		X = p_x;
	}
	void AmbienceObject::SetPositionY(float p_y)
	{
		Y = p_y;
	}
	void AmbienceObject::SetPositionXY(int p_x, int p_y)
	{
		//TODO: How would we check for valid position, esp when we intend
		//to place off screen coordinates for some

		X = p_x;
		Y = p_y;
	}
	void AmbienceObject::SetFinalPos(int p_x, int p_y)
	{
		FinalX = p_x;
		FinalY = p_y;
	}
	bool AmbienceObject::IsAtFinalPos()
	{
		return ((int)round(X) == FinalX) && ((int)round(Y) == FinalY);
	}
	float AmbienceObject::GetY()
	{
		return Y;
	}
	float AmbienceObject::GetSpeed()
	{
		return Speed;
	}
	void AmbienceObject::SetRange(const Shapes::Rectangle& p_range)
	{
		Range = p_range;
	}
	void Logo::Render(Cosmos& Cosmos)
	{
		for (int ly = 0; ly < Height; ly++)
			for (int lx = 0; lx < Width; lx++)
			{
				switch (Str[ly * Width + lx])
				{
				case L'+':
				{
					Cosmos.DrawChar((int)X + lx, (int)Y + ly, Map[0].WChar, Map[0].Col);
					break;
				}
				case L'-':
				{
					Cosmos.DrawChar((int)X + lx, (int)Y + ly, Map[1].WChar, Map[1].Col);
					break;
				}
				case L'.':
				{
					Cosmos.DrawChar((int)X + lx, (int)Y + ly, Map[2].WChar, Map[2].Col);
					break;
				}
				case L' ':
				{
					Cosmos.DrawChar((int)X + lx, (int)Y + ly, Map[3].WChar, Map[3].Col);
					break;
				}
				case L',':
				{
					Cosmos.DrawChar((int)X + lx, (int)Y + ly, Map[4].WChar, Map[4].Col);
					break;
				}
				case L'=':
				{
					Cosmos.DrawChar((int)X + lx, (int)Y + ly, Map[5].WChar, Map[5].Col);
					break;
				}
				case L'\"':
				{
					Cosmos.DrawChar((int)X + lx, (int)Y + ly, Map[6].WChar, Map[6].Col);
					break;
				}
				case L'\'':
				{
					Cosmos.DrawChar((int)X + lx, (int)Y + ly, Map[7].WChar, Map[7].Col);
					break;
				}
				case L'\\':
				{
					Cosmos.DrawChar((int)X + lx, (int)Y + ly, Map[8].WChar, Map[8].Col);
					break;
				}
				case L'_':
				{
					Cosmos.DrawChar((int)X + lx, (int)Y + ly, Map[9].WChar, Map[9].Col);
					break;
				}
				default:
				{
					break;
				}
				}
			}
	}
	void Logo::RenderFromToY(int p_y1, int p_y2, Cosmos& Cosmos)
	{
		for (int ly = 0; ly < Height; ly++)
			for (int lx = 0; lx < Width; lx++)
			{
				int XPos = round(X + lx);
				int YPos = round(Y + ly);

				if ((YPos > p_y1) && (YPos < p_y2))
				{
					switch (Str[ly * Width + lx])
					{
					case L'+':
					{
						Cosmos.DrawChar(XPos, YPos, Map[0].WChar, Map[0].Col);
						break;
					}
					case L'-':
					{
						Cosmos.DrawChar(XPos, YPos, Map[1].WChar, Map[1].Col);
						break;
					}
					case L'.':
					{
						Cosmos.DrawChar(XPos, YPos, Map[2].WChar, Map[2].Col);
						break;
					}
					case L' ':
					{
						Cosmos.DrawChar(XPos, YPos, Map[3].WChar, Map[3].Col);
					}
					default:
					{
						break;
					}
					}
				}
			}
	}
	Text::Text(int p_x, int p_y, std::wstring p_str, short p_col)
	{
		X = p_x;
		Y = p_y;
		Str = p_str;
		Col = p_col;
	}
	void Text::Render(Cosmos& Cosmos)
	{
		for (int i = 0; i < Str.length(); i++)
		{
			Cosmos.DrawChar(X + i, Y, Str[i], Col);
		}
	}
	void Text::RenderFromToX(int p_x1, int p_x2, Cosmos& Cosmos)
	{
		for (int i = 0; i < Str.length(); i++)
		{
			int XPos = round(X + i);
			int YPos = round(Y);

			if ((XPos < p_x1) && (XPos > p_x2))
			{
				Cosmos.DrawChar(XPos, YPos, Str[i], Col);
			}
		}
	}
	void Text::RenderFromToY(int p_y1, int p_y2, Cosmos& Cosmos)
	{
		for (int i = 0; i < Str.length(); i++)
		{
			int XPos = round(X + i);
			int YPos = round(Y);

			if ((YPos > p_y1) && (YPos < p_y2))
			{
				Cosmos.DrawChar(XPos, YPos, Str[i], Col);
			}
		}
	}
}