#include "Cosmos/Cosmos.h"

#include "Cosmos/GameState/GameState.h"
#include "Cosmos/GameState/MainMenu.h"
#include "Cosmos/Color/Color.h"
namespace Game 
{
	using GS::MainMenu;
	using GS::GameState;

	Cosmos::Cosmos() : ActiveSession(true)
	{
		if (OnUserCreate())
		{
			//we push our starting state
			PushState(MainMenu::Instance());
		}
		else
		{
			Quit();
		}
	}
	bool Cosmos::OnUserCreate()
	{
		bool success{ true };
		ConstructConsole(80, 30, 10, 10);
		using namespace Game::Colors;
		//Anaglyph = 1st three
		ColorManager.m_colors[0] = FG_RED;
		ColorManager.m_colors[1] = FG_WHITE; //fcb
		ColorManager.m_colors[2] = FG_RED;

		ColorManager.m_colors[3] = FG_CYAN;

		ColorManager.m_colors[4] = FG_RED;
		ColorManager.m_colors[5] = FG_RED;
		ColorManager.m_colors[6] = FG_RED;
		ColorManager.m_colors[7] = FG_RED;
		//init state to be pushed
		return success;
	}
	bool Cosmos::OnUserUpdate()
	{

		/** Clear CEngine Buffer **/
		RenderClear();

		/** Update CEngine Events **/
		UpdateConsoleEvents();

		/** GameState Loop **/
		PeekState()->ProcessInput(*this);
		bool run = PeekState()->UpdateGameLogic(*this);
		PeekState()->AddToPipeline(*this);

		/** Blit **/
		PresentRender();
		return run;
	}
	void Cosmos::ExecuteGameLoop()
	{
		if (!OnUserUpdate())
		{
			Quit();
		}
	}
	bool Cosmos::Running() const 
	{ 
		return ActiveSession; 
	}
	void Cosmos::Quit() 
	{ 
		ActiveSession = false; 
	}

	int Cosmos::GetScreenWidth() const 
	{ 
		return m_nScreenWidth; 
	}
	int Cosmos::GetScreenHeight() const 
	{ 
		return m_nScreenHeight; 
	}

	void Cosmos::PushState(GameState* state)
	{
		if (!GameStateStack.empty())
		{
			GameStateStack.back()->Pause();
		}
		GameStateStack.push_back(state);
		GameStateStack.back()->Init(*this);
	}
	void Cosmos::PopState()
	{
		if (!GameStateStack.empty())
		{
			GameStateStack.back()->Cleanup();
			GameStateStack.pop_back();
		}
		//check after popping if there's another state in the stack
		if (!GameStateStack.empty())
		{
			GameStateStack.back()->Resume(*this);
		}
	}
	GameState* Cosmos::PeekState()
	{
		if (!GameStateStack.empty())
		{
			return GameStateStack.back();
		}
		else
		{
			throw "Empty State Stack";
		}
	}
}