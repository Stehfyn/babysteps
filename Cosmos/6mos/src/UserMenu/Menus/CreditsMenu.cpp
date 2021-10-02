#include "Cosmos/UserMenus/Menus/CreditsMenu.h"

#include "Cosmos/GameState/GameState.h" //sus

#include "Cosmos/UserMenus/MenuObjects/MenuObject.h"
#include "Cosmos/Ambience/AmbienceObject.h"

//use an alias here
Game::UserMenu::CreditsMenu* Game::UserMenu::CreditsMenu::m_CreditsMenu = 0;

namespace Game::UserMenu
{
	void CreditsMenu::Init(Cosmos& Cosmos)
	{
		//MenuObjectsStack.clear();
		//AmbienceObjectsStack.clear();

		MenuObject* BACK = new TextSelection(38, 26, "BACK", Cosmos.ColorManager.m_colors[5], Cosmos.ColorManager.m_colors[6]);
		MenuObjectsVec = { BACK };


		using namespace Ambience;
		//init menuAmbience here
		std::wstring ROLEStr = L"Programming";
		Ambience::Text* ROLE = new Ambience::Text(34, 27, ROLEStr, 0x000F);
		ROLE->SetSpeed(10);
		ROLE->SetFinalPos(34, 10);

		std::wstring NAMEStr = L"Stephen Foster";
		Ambience::Text* NAME = new Ambience::Text(33, 29, NAMEStr, 0x000F);
		NAME->SetSpeed(10);
		NAME->SetFinalPos(33, 12);

		std::wstring SCHOOLStr = L"University of Nevada, Reno";
		Ambience::Text* SCHOOL = new Ambience::Text(2, 62, SCHOOLStr, 0x000F);
		SCHOOL->SetSpeed(10);
		SCHOOL->SetFinalPos(2, 22);

		Logo* UNR = new Logo(6, 45, 17, 15);

		std::wstring UNRStr;
		UNRStr.append(L"                 ");
		UNRStr.append(L"                 ");
		UNRStr.append(L"                 ");
		UNRStr.append(L"   ++++  +++++   ");
		UNRStr.append(L"   +   + +   +   ");
		UNRStr.append(L"    +   + + +    ");
		UNRStr.append(L"    + +  .+ +    ");
		UNRStr.append(L"    + ++ ++ +    ");
		UNRStr.append(L"    + +     +    ");
		UNRStr.append(L"   .+ +.+   +.   ");
		UNRStr.append(L"   +   + +   +   ");
		UNRStr.append(L"   .....  ....   ");
		UNRStr.append(L"                 ");
		UNRStr.append(L"                 ");
		UNRStr.append(L"                 ");

		UNR->SetStr(UNRStr);
		UNR->SetMap(0, L' ', 0x00FF);
		UNR->SetMap(2, L' ', 0x0077);
		UNR->SetMap(3, L' ', 0x0011);

		UNR->SetSpeed(10);
		UNR->SetFinalPos(6, 5);

		/*Logo* SRS = new Logo(5, 45, 24, 15);
		std::wstring SRSStr;

		//width = 24
		//height = 15
		//+ = white
		//. = light grey

		SRSStr.append(L"     ++.         +++    ");
		SRSStr.append(L"  ++++++++     +++++++  ");
		SRSStr.append(L" .+++++++++   +++++++++ ");
		SRSStr.append(L" +++++++++++ +++++++++++");
		SRSStr.append(L"++++   +++++ +++++ . +++");
		SRSStr.append(L"++++.+  ++++ ++++ ++. ++");
		SRSStr.append(L"++.++.+ ++++ +++ .+ ++++");
		SRSStr.append(L"++ +. ++++++ +++ +++ +++");
		SRSStr.append(L" ++++++ ++++ +++ ++++ ++");
		SRSStr.append(L"  ++ .  ++++ +++   . ++ ");
		SRSStr.append(L"   ++   ++++ +++   ++.  ");
		SRSStr.append(L"        ++++++++        ");
		SRSStr.append(L"        ++++++++        ");
		SRSStr.append(L"        ++++++++  .     ");
		SRSStr.append(L"        ++++++++        ");

		SRS->SetStr(SRSStr);
		SRS->SetMap(0, L' ', 0x00FF);
		SRS->SetMap(2, L' ', 0x0077);
		SRS->SetMap(3, L' ', 0x0000);
		SRS->SetSpeed(10);
		SRS->SetFinalPos(5, 5);*/

		AmbienceObjectsVec = { ROLE, NAME, UNR, SCHOOL }; //SRS

	}
	void CreditsMenu::Cleanup()
	{

	}
	void CreditsMenu::SelectObj(int menuObjNum, Cosmos& Cosmos)
	{
		switch (menuObjNum)
		{
		case 0:
		{
			Cosmos.PeekState()->PopUserMenu();
			break;
		}
		default:
		{
			break;
		}
		}
	}
	void CreditsMenu::UpdateMenuObjects(Cosmos& Cosmos)
	{
		//do some time shit with Cosmos.t_elapsed
		//pos = Speed (pixels per second) * t_elapsed;
		//int pos = (int)(float * float)

		
		float testPos;
		for (int i = 0; i < AmbienceObjectsVec.size(); i++)
		{
			Ambience::AmbienceObject* Current = AmbienceObjectsVec.at(i);
			if (!Current->IsAtFinalPos())
			{
				Current->SetPositionY(Current->GetY() - (Current->GetSpeed() * Cosmos.t_fElapsed));
			}
			//debug shit VVV
			testPos = Current->GetY();
		}

		//-------------COPIED from menu.cpp---------------
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



		//debug shit VVVV
		std::wstring test = std::to_wstring(Cosmos.t_fElapsed);
		for (int i = 0; i < test.length(); i++)
		{
			Cosmos.DrawChar(0 + i, 5, test[i], 0x000F);
		}

		std::wstring testPosStr = std::to_wstring(testPos);
		for (int i = 0; i < testPosStr.length(); i++)
		{
			Cosmos.DrawChar(0 + i, 7, testPosStr[i], 0x000F);
		}

	}
	void CreditsMenu::AddMenuAmbienceToPipeline(Cosmos& Cosmos)
	{
		//a way to identify and discern the Logo objects within this vector
		//from how we want to render them
		for (int i = 0; i < AmbienceObjectsVec.size(); i++)
		{
			AmbienceObjectsVec.at(i)->RenderFromToY(2, 27, Cosmos);
		}

		//if x>= 0 and x <= 79 and y>=2 and y <= 26
		//then print line by line until y !< 27

		/*std::wstring SRSLogo;
		//width = 24
		//height = 15
		//+ = white
		//* = Dark grey
		//. = light grey
		SRSLogo.append(L"     ++.         +++    ");
		SRSLogo.append(L"  ++++++++     +++++++  ");
		SRSLogo.append(L" .+++++++++   +++++++++ ");
		SRSLogo.append(L" +++++++++++ +++++++++++");
		SRSLogo.append(L"++++   +++++ +++++ . +++");

		SRSLogo.append(L"++++.+  ++++ ++++ ++. ++");
		SRSLogo.append(L"++.++.+ ++++ +++ .+ ++++");
		SRSLogo.append(L"++ +. ++++++ +++ +++ +++");
		SRSLogo.append(L" ++++++ ++++ +++ ++++ ++");
		SRSLogo.append(L"  ++ .  ++++ +++   . ++ ");

		SRSLogo.append(L"   ++   ++++ +++   ++.  ");
		SRSLogo.append(L"        ++++++++        ");
		SRSLogo.append(L"        ++++++++        ");
		SRSLogo.append(L"        ++++++++  .     ");
		SRSLogo.append(L"        ++++++++        ");

		for (int y = 0; y < 15; y++)
			for (int x = 0; x < 24; x++)
			{
				switch (SRSLogo[y * 24 + x])
				{
				case L'+':
				{
					Cosmos.DrawChar(5 + x, 6 + y, L' ', 0x00FF);
					break;
				}
				case L'.':
				{
					Cosmos.DrawChar(5 + x, 6 + y, L' ', 0x0077);
					break;
				}
				default:
				{

					break;
				}
				}
			}
		std::wstring Position = L"Programming";
		for (int i = 0; i < Position.length(); i++)
			Cosmos.DrawChar(35 + i, 13, Position[i], 0x000F);
		std::wstring Name = L"Stephen Foster";
		for (int i = 0; i < Name.length(); i++)
			Cosmos.DrawChar(34 + i, 15, Name[i], 0x000F);
		std::wstring SRS = L"Sea Ranch Softworks";
		for (int i = 0; i < SRS.length(); i++)
			Cosmos.DrawChar(5 + i, 25, SRS[i], 0x000F);
		std::wstring UNR = L"University of Nevada, Reno";
		for (int i = 0; i < UNR.length(); i++)
			Cosmos.DrawChar(50 + i, 25, UNR[i], 0x000F);*/
	}
}