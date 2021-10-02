#include "Cosmos/GameState/Demo.h"
#include "Cosmos/Ambience/AmbienceObject.h"
#include "Cosmos/Shapes/Rectangle.h"

#include "Cosmos/GameState/MainMenu.h"
#include "Cosmos/UserMenus/Menus/TopMenu.h"
#include "Cosmos/Ambience/AmbienceObject.h"

/* DEAR SOBER STEPH, AS YOU CAN SEE, THIS SHIT AINT DONE. SORRY XOXO*/


namespace Game::GS
{
	//use an alias here
	Game::GS::Demo* Game::GS::Demo::m_Demo = 0;



	using Game::UserMenu::TopMenu;
	using Game::Ambience::Star;
	using Game::Shapes::Rectangle;

	void Demo::Init(Cosmos& Cosmos)
	{
		Menu* startingMenu = nullptr;
		if (0)
			PushUserMenu(TopMenu::Instance(), Cosmos);
		//add Ambience objects that need to init along with state
	}
	void Demo::UpdateGameStateObjects(Cosmos& Cosmos)
	{

		//accumulating time
		AmbienceDelay += Cosmos.t_fElapsed;
		AmbienceDelay2 += Cosmos.t_fElapsed;


		if (AmbienceDelay > .1f)
		{
			//we solved it :)

			//red stars
			Star* newStar = new Star(rand() % 80, 3, L'/', 0x000F);

			newStar->SetDirection(7);
			newStar->SetSpeed(42);

			newStar->SetRange(Rectangle(0, 3, 80, 24));

			AmbienceObjectsVec.insert(AmbienceObjectsVec.begin(), newStar);

			//white stars
			Star* newStar2 = new Star(rand() % 80, 3, L'/', 0x000C);

			newStar2->SetDirection(7);
			newStar2->SetSpeed(18);

			newStar2->SetRange(Rectangle(0, 3, 80, 24));

			AmbienceObjectsVec.insert(AmbienceObjectsVec.begin(), newStar2);

			Star* newStar3 = new Star(rand() % 80, 3, L'/', 0x000B);

			newStar3->SetDirection(7);
			newStar3->SetSpeed(32);

			newStar3->SetRange(Rectangle(0, 3, 80, 24));

			AmbienceObjectsVec.insert(AmbienceObjectsVec.begin(), newStar3);


			AmbienceDelay = 0.0f;
		}
		if (AmbienceDelay2 > 10.0f)
		{
			//we solved it :)

			//red stars
			Star* newStar = new Star((rand() % 40) + 20, 3, L'\x03C6', 0x000D);

			newStar->SetDirection(7);
			newStar->SetSpeed(4);

			newStar->SetRange(Rectangle(0, 3, 80, 24));

			AmbienceObjectsVec.insert(AmbienceObjectsVec.begin(), newStar);


			AmbienceDelay2 = 0.0f;
		}
		//Advancing if valid, setting to nullptr if not
		for (size_t i = 0; i < AmbienceObjectsVec.size(); ++i)
		{
			Ambience::AmbienceObject* Current = AmbienceObjectsVec.at(i);

			Current->Advance(Cosmos);

			Current->CheckRange(Cosmos);

			if (Current->NeedsDestroy(Cosmos))
			{
				delete Current;
				Current = nullptr;

				AmbienceObjectsVec.at(i) = nullptr;
			}

		}

		//deleting nullptr objects
		//REMOVE ERASE IDIOM LETS GO LOOK AT YOU GOOOOOOOOO
		AmbienceObjectsVec.erase(std::remove(AmbienceObjectsVec.begin(),
			AmbienceObjectsVec.end(), nullptr), AmbienceObjectsVec.end());




		std::wstring vecSize = std::to_wstring(AmbienceObjectsVec.size());
		for (int i = 0; i < vecSize.length(); i++)
		{
			Cosmos.DrawChar(0 + i, 0, vecSize[i], 0x000F);
		}
	}
	void Demo::AddGameStateObjectsToPipeline(Cosmos& Cosmos)
	{
		for (int i = 0; i < 80; i++)
			Cosmos.DrawChar(i, 2, L'─', 0x000C);
		//Star background ish
		//refactor to vector of a vector ya dummyyy
		for (int i = 0; i < AmbienceObjectsVec.size(); i++)
		{
			Ambience::AmbienceObject* Object = AmbienceObjectsVec.at(i);

			Object->Render(Cosmos);
		}

		for (int i = 0; i < 80; i++)
			Cosmos.DrawChar(i, 27, L'─', 0x000C);
	}

}