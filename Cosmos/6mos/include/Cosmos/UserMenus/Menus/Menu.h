#ifndef USERMENU_H
#define USERMENU_H

#include "Cosmos/Cosmos.h"

#include "Cosmos/UserMenus/MenuObjects/MenuObject.h"
#include "Cosmos/Ambience/AmbienceObject.h"

#include <vector>

//abstract base class all our menus will inherit from

namespace Game::UserMenu
{
	using Ambience::AmbienceObject;

	class Menu
	{
	public:
		virtual void Init(Cosmos& Cosmos) = 0; //add MenuObjects/Ambience to vector
		virtual void Cleanup() = 0; //delete MenuObjects/Ambience from vector

		virtual void Select(Cosmos& Cosmos);
		virtual void SelectObj(int, Cosmos& Cosmos) = 0;
		virtual void Back() {}
		virtual void CursorUp() {}
		virtual void CursorDown() {}
		
		void ProcessMenuInput(Cosmos& Cosmos);

		virtual void UpdateMenuAmbienceObjects(Cosmos& Cosmos) {} //Natural state is do nothing
		virtual void UpdateMenuObjects(Cosmos& Cosmos);

		virtual void AddMenuAmbienceToPipeline(Cosmos& Cosmos); //Individual menus can override
		virtual void AddMenuObjectsToPipeline(Cosmos& Cosmos);

	protected:
		//each sub-class will know its own selection
		struct Cursor
		{
			int X;
			int Y;
			wchar_t CursorChar{ L'\x2022' };
			short CursorCol{ 0x000C };
		}Cursor{};

		std::vector<MenuObject*> MenuObjectsVec;
		std::vector<AmbienceObject*> AmbienceObjectsVec;

		//above should just be replaced by an object renderer
		//What is an object renderer?
		//an object renderer can contain any number of different type
		//object streams for it to render. Each of these object streams can be
		//customized with their own personal attributes specifying the render
		//specifications

		Menu() {}
	};
}
#endif
