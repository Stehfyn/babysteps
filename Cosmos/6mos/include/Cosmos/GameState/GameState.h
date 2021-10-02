#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Cosmos/Cosmos.h"

#include "Cosmos/UserMenus/Menus/Menu.h"

#include "Cosmos/Commands/Command.h"
#include "Cosmos/Ambience/AmbienceObject.h"
#include "Cosmos/Input/InputHandler.h"

namespace Game::GS
{
    using UserMenu::Menu;
    using Ambience::AmbienceObject;
    using Commands::Command;
    using Input::InputHandler;

    class GameState
    {
    public:
        /** OVERLOADED - GameState initialization/loading. **/
        virtual void Init(Cosmos& Cosmos) = 0;

        /** OVERLOADED - GameState de-construction/deloading. **/
        virtual void Cleanup() = 0;

        virtual void Pause() = 0;
        virtual void Resume(Cosmos& Cosmos) = 0;

        void ProcessInput(Cosmos& Cosmos);

        bool UpdateGameLogic(Cosmos& Cosmos); //Base Wraps the following two
            /** OVERLOADED - Derived (Ambience + Game + Menu) **/
    protected:
            virtual void UpdateGameStateObjects(Cosmos& Cosmos) = 0;
            virtual void UpdateMenuObjects(Cosmos& Cosmos) = 0;


    public:
        void AddToPipeline(Cosmos& Cosmos); //Base Wraps the following two
    protected:
            virtual void AddGameStateObjectsToPipeline(Cosmos& Cosmos) = 0;
            virtual void AddMenuObjectsToPipeline(Cosmos& Cosmos) = 0;
    public:
        bool IsUserMenuEmpty() const;
        void PushUserMenu(Menu* newMenu, Cosmos& Cosmos);
        void PopUserMenu();
        Menu* PeekUserMenu();

    protected:
        GameState();

        std::vector<Menu*> UserMenuStack;

        std::vector<Command*> CommandQueue;

        std::vector<AmbienceObject*> AmbienceObjectsVec;
        std::vector<AmbienceObject*> planetVec;

        float AmbienceDelay{};
        float AmbienceDelay2{};

        InputHandler* InputHandler;
    };
}
#endif
