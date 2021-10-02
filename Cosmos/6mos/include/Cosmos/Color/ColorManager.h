#ifndef COLOR_MANAGER_H
#define COLOR_MANAGER_H
#include "Color.h"
namespace Game::Colors
{
	class ColorManager
	{

	public:
		Color m_colors[10];
	private:
		static ColorManager* m_ColorManager;
		static ColorManager* Instance()
		{
			if (m_ColorManager == nullptr)
			{
				m_ColorManager = new ColorManager();
			}
			return m_ColorManager;
		}
	public:
		ColorManager() {}
		ColorManager(const ColorManager& obj) {}
		

	};
}
#endif