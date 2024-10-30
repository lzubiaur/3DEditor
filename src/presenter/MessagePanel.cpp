#pragma once

#include <presenter/MessagePanel.h>

namespace Forged::Presenter
{

MessagePanel::MessagePanel(IServiceLocator& services)
: IMessagePanel(services)
{
    using namespace View::ControlHashes;

    services.getUIService().getStore().dispatch(State::UpdatePanelVisibility(MessagePanelHash, true));

    services.getUIService().subscribeToPanelChanges([&](const State::Panel &panel)
        {
            mVisible = panel.isVisible; 
        },
        MessagePanelHash);
}

void MessagePanel::setIsVisible(bool value)
{
    IMessagePanel::setIsVisible(value);
    dispatch(State::UpdatePanelVisibility(View::ControlHashes::MessagePanelHash, value));
}

}