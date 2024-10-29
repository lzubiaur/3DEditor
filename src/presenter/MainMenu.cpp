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
    using namespace View::ControlHashes;

    services.getUIService().subscribeToPanelChanges([&](State::Panel panel)
        {
            mIsMessagePanelVisible = panel.isVisible;
        },
        MessagePanelHash);

    services.getUIService().subscribeToPanelChanges([&](State::Panel panel)
        {
            mIsDemoPanelVisible = panel.isVisible;
        },
        DemoPanelHash);

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
    dispatch(State::UpdateAppStatus(State::AppStatus::Closing));
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
    dispatch(State::TogglePanelVisibility(View::ControlHashes::DemoPanelHash));
}

void MainMenu::setIsMessagePanelVisible(bool value)
{
    dispatch(State::TogglePanelVisibility(View::ControlHashes::MessagePanelHash));
}

void MainMenu::dispatch(State::Reducer reducer)
{
    mServices.getUIService().getStore().dispatch(reducer);
}

}