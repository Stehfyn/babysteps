#ifndef AMBIENCEOBJECT_H
#define AMBIENCEOBJECT_H

#include "Cosmos/Cosmos.h"
#include "Cosmos/Shapes/Rectangle.h"

#include <string>

namespace Game::Ambience
{
	using Shapes::Rectangle;

	class AmbienceObject
	{
	public:
		AmbienceObject() : X(0), Y(0), Width(0), Height(0), Speed(0), FinalX(0), FinalY(0), Active(false), Range(0, 0, 0, 0)
		{

		}
		virtual void Render(Cosmos& Cosmos) = 0;

		virtual void RenderFromToX(int p_x1, int p_x2, Cosmos& Cosmos) = 0;
		virtual void RenderFromToY(int p_y1, int p_y2, Cosmos& Cosmos) = 0;
		virtual void RenderInRangeXY(int p_x1, int p_x2, int p_y1, int p_y2, Cosmos& Cosmos) = 0;

		void SetStr(std::wstring p_str);
		bool IsAtFinalPos();
		void SetFinalPos(int p_x, int p_y);
		//read about default parameters to maybe spruce up the following 3 funcs
		void SetPositionX(int p_x);
		void SetPositionY(float p_y);
		void SetPositionXY(int p_x, int p_y);
		void SetSpeed(int p_speed);

		void SetRange(const Rectangle& p_range);
		
		//bad virtuals bc ur dumb and didnt write vector of a vector 
		//so make sure to refactor these out
		virtual void Advance(Cosmos& Cosmos) = 0;
		//current implementation is checking range in update
		//what we should do is make range (rectangle) an inherent member of 
		//an ambience object, then just wrap the render function based off the range
		virtual void CheckRange(Cosmos& Cosmos) = 0;
		virtual void ShowRange(Cosmos& Cosmos);
		virtual bool NeedsDestroy(Cosmos& Cosmos) = 0;

		//TODO: think of a better way than virtual getters and setters to access
		//derived member fields
		float GetY();
		float GetSpeed();
	protected:
		float X;
		float Y;

		int Width;
		int Height;

		float Speed;

		int FinalX;
		int FinalY;

		bool Active;
		std::wstring Str;

		Rectangle Range;
	};
	class Star : public AmbienceObject
	{
	public:
		Star(int p_x, int p_y, wchar_t p_wchar, short p_col);

		void Render(Cosmos& Cosmos);
		void RenderFromToX(int p_x1, int p_x2, Cosmos& Cosmos);
		void RenderFromToY(int p_y1, int p_y2, Cosmos& Cosmos);
		void RenderInRangeXY(int p_x1, int p_x2, int p_y1, int p_y2, Cosmos& Cosmos);
		void SetDirection(int p_dir);

		void Advance(Cosmos& Cosmos);
		void CheckRange(Cosmos& Cosmos);
		bool NeedsDestroy(Cosmos& Cosmos);

		~Star();
	private:
		wchar_t Character;
		short Col;
		int Dir;
	};
	class Logo : public AmbienceObject
	{
		/*
		* L'+' Map[0]
		* L'-' Map[1]
		* L'.' Map[2]
		* L' ' Map[3]
		* 
		* L',' Map[4]
		* L'=' Map[5]
		* L'"' Map[6]
		* L''' Map[7]
		* 
		* L'\' Map[8]
		* L'' Map[9]
		*/

		struct LogoCharMap
		{
			wchar_t WChar;
			short Col;
		};

	public:
		Logo(int p_x, int p_y, int p_width, int p_height);
	private: //do later when not dumb
		//void RenderSwitch(int p_logoCoord, int p_forCoord, int p_precond, Cosmos& Cosmos);
	public:
		void Render(Cosmos& Cosmos);

		void RenderFromToX(int p_x1, int p_x2, Cosmos& Cosmos) {}
		void RenderFromToY(int p_y1, int p_y2, Cosmos& Cosmos);
		void RenderInRangeXY(int p_x1, int p_x2, int p_y1, int p_y2, Cosmos& Cosmos) {}
		void Advance(Cosmos& Cosmos) { }

		void CheckRange(Cosmos& Cosmos) {}
		bool NeedsDestroy(Cosmos& Cosmos) { return true; } //lol }
		void SetMap(int p_int, wchar_t p_wchar, short p_col);


	private:
		LogoCharMap Map[10];
	};
	class Text : public AmbienceObject
	{
	public:
		Text(int p_x, int p_y, std::wstring p_str, short p_col);

		void Render(Cosmos& Cosmos);

		void Advance(Cosmos& Cosmos) { }
		void CheckRange(Cosmos& Cosmos) { }
		bool NeedsDestroy(Cosmos& Cosmos) { return true; }

		void RenderFromToX(int p_x1, int p_x2, Cosmos& Cosmos);
		void RenderFromToY(int p_y1, int p_y2, Cosmos& Cosmos);
		void RenderInRangeXY(int p_x1, int p_x2, int p_y1, int p_y2, Cosmos& Cosmos) { }
	private:
		short Col;
	};
}
#endif
