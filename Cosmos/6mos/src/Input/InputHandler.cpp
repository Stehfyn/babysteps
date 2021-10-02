#include "Cosmos/Input/InputHandler.h"

namespace Game::Input
{
    using namespace Game::Commands;

    std::vector<Command*> InputHandler::HandleInput(Cosmos& Cosmos)
    {
        std::vector<Command*> CommandQueue;
        //Clean this up later

        //Keyboard Commands
        if (!this->active)
        {
            //demo key mappin

            MouseCommands[0] = new Select;
            MouseCommands[0]->ActiveOn = PRESSED;

            active = true;
        }
        //oh my god like oh myyy godddd its like it filled the command spot like a bucket the water is there after the pass
        for (int i = 0; i < 256; i++)
        {
            if (KeyboardCommands[i] != nullptr)
            {
                switch (KeyboardCommands[i]->ActiveOn)
                {
                case PRESSED:
                {
                    if (Cosmos.Keyboard.m_keys[i].bPressed)
                        CommandQueue.push_back(KeyboardCommands[i]);
                    break;
                }
                case HELD:
                {
                    if (Cosmos.Keyboard.m_keys[i].bHeld)
                        CommandQueue.push_back(KeyboardCommands[i]);
                    break;
                }
                case RELEASED:
                {
                    if (Cosmos.Keyboard.m_keys[i].bReleased)
                        CommandQueue.push_back(KeyboardCommands[i]);
                    break;
                }
                default:
                    break;
                }
            }
        }
        //think how you can split pressed held and released in this context
        //Mouse Commands
        for (int i = 0; i < 3; i++)
        {
            if (MouseCommands[i] != nullptr)
            {
                switch (MouseCommands[i]->ActiveOn)
                {
                case PRESSED:
                {
                    if (Cosmos.Mouse.ButtonState[i].bPressed)
                        CommandQueue.push_back(MouseCommands[i]);
                    break;
                }
                case HELD:
                {
                    if (Cosmos.Mouse.ButtonState[i].bHeld)
                        CommandQueue.push_back(MouseCommands[i]);
                    break;
                }
                case RELEASED:
                {
                    if (Cosmos.Mouse.ButtonState[i].bReleased)
                        CommandQueue.push_back(MouseCommands[i]);
                    break;
                }
                default:
                    break;
                }
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (MouseWheelCommands[i] != nullptr)
            {
                switch (MouseWheelCommands[i]->ActiveOn)
                {
                case SCROLL:
                {
                    if (Cosmos.Mouse.MouseWheelState[i])
                        CommandQueue.push_back(MouseWheelCommands[i]);
                    break;
                }
                default:
                    break;
                }
            }
        }

        //Gamepad Commands
        for (int i = 0; i < 14; i++)
        {
            if (GamepadCommands[i] != nullptr)
            {
                switch (GamepadCommands[i]->ActiveOn)
                {
                case PRESSED:
                {
                    if (Cosmos.Gamepad.m_Buttons[i].bPressed)
                        CommandQueue.push_back(GamepadCommands[i]);
                    break;
                }
                case HELD:
                {
                    if (Cosmos.Gamepad.m_Buttons[i].bHeld)
                        CommandQueue.push_back(GamepadCommands[i]);
                    break;
                }
                case RELEASED:
                {
                    if (Cosmos.Gamepad.m_Buttons[i].bReleased)
                        CommandQueue.push_back(GamepadCommands[i]);
                    break;
                }
                default:
                    break;
                }
            }
        }
        return CommandQueue;
        /*TODO: Hardcode analogs and also hook triggers to commands*/


    }
}