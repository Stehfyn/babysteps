#ifndef COSMOS_H
#define COSMOS_H

#include <iostream>
#include <vector>

#include "CEngine/CEngine.h"
#include "Color/ColorManager.h"

namespace Game 
{
	namespace GS
	{
		class GameState;
	}

	class Cosmos : public CEngine
	{
		friend class Command;
		friend class InputHandler;
	public:
		Cosmos();
		bool OnUserCreate();

		/** Function Wrapper for Game Loop **/
		bool OnUserUpdate();

		/** Function Wrapper for OnUserUpdate **/
		void ExecuteGameLoop();

		/** GameObservers **/
		int GetScreenWidth() const;
		int GetScreenHeight() const;
		bool Running() const;

		/** GameMutators **/
		void Quit();
		void PushState(GS::GameState* state);
		void PopState();
		GS::GameState* PeekState();

		Game::Colors::ColorManager ColorManager;

	private:
		std::vector<GS::GameState*> GameStateStack;

		bool ActiveSession;

		//Each individual state should know how to do its own:
			//ProcessInput (command pattern)
			//Update Game Logic
			//Add to pipeline

	};
}
#endif