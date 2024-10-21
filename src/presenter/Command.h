#pragma once

#include <presenter/ReactiveCommand.h>

namespace Forged::Presenter
{

enum class ApplicationCommandType
{
    Close = 0,
    Open,
    Save,
};

struct ApplicationCommandArgument
{
    ApplicationCommandType type;
};

using ApplicationCommand = ReactiveCommand<ApplicationCommandArgument>;

// TODO
// NavigationCommands
// EditingCommands
// MediaCommands
// ComponentCommands

}
