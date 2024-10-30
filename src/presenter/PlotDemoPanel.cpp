#pragma once

#include <presenter/PlotDemoPanel.h>

namespace Forged::Presenter
{

PlotDemoPanel::PlotDemoPanel(IServiceLocator& services)
: IPlotDemoPanel(services)
{
    setIsVisible(false);

    mServices.getUIService().subscribeToPanelChanges([&](const State::Panel& panel)
    {
       mVisible = panel.isVisible;
    }, 
    View::ControlHashes::PlotDemoPanelHash);
}

void PlotDemoPanel::setIsVisible(bool value)
{
    IPlotDemoPanel::setIsVisible(value);
    dispatch(State::UpdatePanelVisibility(View::ControlHashes::PlotDemoPanelHash, value));
}

}