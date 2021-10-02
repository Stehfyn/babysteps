#ifndef COMMAND_H
#define COMMAND_H

#include "Cosmos/Cosmos.h"

namespace Game::Commands
{
    using Game::Cosmos;

    enum COMMAND_PRESS
    {
        PRESSED,
        HELD,
        RELEASED,
        SCROLL
    };

    class Command
    {
    public:
        virtual ~Command() {}
        virtual void Execute(Cosmos& Cosmos) = 0;

        COMMAND_PRESS ActiveOn;
    };

    class Select : public Command
    {
        void Execute(Cosmos& Cosmos);
    };
}
#endif
