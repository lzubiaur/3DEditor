#pragma once

#include <presenter/MainMenu.h>
#include <presenter/Events.h>
#include <state/Reducers.h>
#include <services/IUIService.h>

namespace Forged::Presenter
{

MainMenu::MainMenu(IServiceLocator& services)
: mServices(services)
{
    services.getUIService().subscribeToPanelChanges([&](State::Panel panel)
        {
            mMessagePanelVisible = panel.isVisible;
        },
        "MessageConsole");

    services.getUIService().getApplicationCommand().bind([&services](ApplicationCommandArgument arg) 
    {
        switch (arg.type)
        {
            case ApplicationCommandType::Close:
                services.getSignalService().getSignal<void()>(UIEvents::OnRequestAppClose)->emit();
                break;
        }
    });

    services.getUIService().getPanelCommand().bind([&](PanelCommandArgument arg) 
    {
        auto panel = services.getUIService().findControl(arg.panelName);

        // TODO Change the name to something generic and not implementation specific
        if (!panel && arg.panelName == "ImGuiDemo")
        {
            panel = services.getUIService().createControl(View::IUIControl::ControlType::UIDemoPanel, "ImGuiDemo");
        }
    });
}

void MainMenu::execute(State::PanelActions action)
{
    mServices.getUIService().getStore().dispatch(action);
}

}