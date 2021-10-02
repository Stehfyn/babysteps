#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <vector>

#include "Cosmos/Commands/Command.h"

namespace Game::Input
{
    using Game::Commands::Command;

    class InputHandler
    {
    public://refactor to currState? hmmmstephhhuh
        std::vector<Command*> HandleInput(Cosmos& Cosmos);
        /*
        -Getters and Setters
        -for assigning commands to input*/
    private:
        bool active{ false };
        Command* KeyboardCommands[256]{ nullptr };

        Command* MouseCommands[3]{ nullptr };
        Command* MouseWheelCommands[3]{ nullptr };

        Command* GamepadCommands[14]{ nullptr };
        Command* GamepadTriggerCommands[2]{ nullptr };

    };
}
#endif