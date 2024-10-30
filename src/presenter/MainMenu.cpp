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

    services.getUIService().subscribeToPanelChanges([&](State::Panel panel)
        {
            mIsPlotDemoPanelVisible = panel.isVisible;
        },
        PlotDemoPanelHash);
}

void MainMenu::closeApplication()
{
    dispatch(State::UpdateAppStatus(State::AppStatus::Closing));
}

bool MainMenu::isDemoPanelVisible()
{
    return mIsDemoPanelVisible;
}

bool MainMenu::isPlotDemoPanelVisible()
{
    return mIsPlotDemoPanelVisible;
}

bool MainMenu::isMessagePanelVisible()
{
    return mIsMessagePanelVisible;
}

void MainMenu::setIsDemoPanelVisible(bool value)
{
    dispatch(State::TogglePanelVisibility(View::ControlHashes::DemoPanelHash));
}

void MainMenu::setIsPlotDemoPanelVisible(bool value)
{
    dispatch(State::TogglePanelVisibility(View::ControlHashes::PlotDemoPanelHash));
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