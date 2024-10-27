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
            mIsMessagePanelVisible = panel.isVisible;
        },
        "MessageConsole");

    services.getUIService().subscribeToPanelChanges([&](State::Panel panel)
        {
            mIsDemoPanelVisible = panel.isVisible;
        },
        "DemoPanel");

    // TODO remove command and use the global
    services.getUIService().getApplicationCommand().bind([&services](ApplicationCommandArgument arg) 
    {
        switch (arg.type)
        {
            case ApplicationCommandType::Close:
                services.getSignalService().getSignal<void()>(UIEvents::OnRequestAppClose)->emit();
                break;
        }
    });
}

void MainMenu::closeApplication()
{
    // TODO
}

bool MainMenu::isDemoPanelVisible()
{
    return mIsDemoPanelVisible;
}

bool MainMenu::isMessagePanelVisible()
{
    return mIsMessagePanelVisible;
}

void MainMenu::setIsDemoPanelVisible(bool value)
{
    mServices.getUIService().getStore().dispatch(State::ToggleVisibility{ "DemoPanel" });
}

void MainMenu::setIsMessagePanelVisible(bool value)
{
    mServices.getUIService().getStore().dispatch(State::ToggleVisibility{ "MessageConsole" });
}

}