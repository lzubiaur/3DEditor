#pragma once

#include <presenter/ReactiveCommand.h>
#include <presenter/CommandHelper.h>

namespace Forged::Presenter::Command
{

COMMAND_TYPE(Application, Close, OpenProject, SaveProject)
COMMAND(Application)

COMMAND_TYPE(Dialog, OpenDialog, CloseDialog, AcceptDialog)
COMMAND(Dialog)

COMMAND_TYPE(Panel, ShowPanel, HidePanel, TogglePanel)
BEGIN_COMMAND(Panel)
    std::string panelName;
END_COMMAND(Panel)

// TODO
// NavigationCommands
// EditingCommands
// MediaCommands
// ComponentCommands

}
