#pragma once

#include <presenter/DemoPanel.h>

namespace Forged::Presenter
{

DemoPanel::DemoPanel(IServiceLocator& services)
: IDemoPanel(services)
{
    setIsVisible(false);

    mServices.getUIService().subscribeToPanelChanges([&](const State::Panel& panel)
    {
       mVisible = panel.isVisible;
    }, 
    View::ControlHashes::DemoPanelHash);
}

void DemoPanel::setIsVisible(bool value)
{
    IDemoPanel::setIsVisible(value);
    dispatch(State::UpdatePanelVisibility(View::ControlHashes::DemoPanelHash, value));
}

}