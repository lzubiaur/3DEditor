#pragma once

#include <presenter/MainMenu.h>
#include <presenter/Events.h>
#include <services/IUIService.h>

namespace Forged::Presenter
{

MainMenu::MainMenu(IServiceLocator& services)
: mServices(services)
{
    mApplicationCommand.bind([&services](ApplicationCommandArgument arg) 
    {
        switch (arg.type)
        {
            case ApplicationCommandType::Close:
                services.getSignalService().getSignal<void()>(UIEvents::OnRequestAppClose)->emit();
                break;
        }
    });

    mPanelCommand.bind([&services](PanelCommandArgument arg) 
    {
        auto panel = services.getUIService().findControl(arg.panelName);

        // TODO Change the name to something generic and not implementation specific
        if (!panel && arg.panelName == "ImGuiDemo")
        {
            panel = services.getUIService().createControl(View::IUIControl::ControlType::UIDemoPanel, "ImGuiDemo");
        }

        switch (arg.type)
        {
            case PanelCommandType::TogglePanel:
                panel->isVisible() ? panel->hide() : panel->show();
                break;
        }
    });
}

}