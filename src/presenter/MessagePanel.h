#pragma once

#include <services/IServiceLocator.h>
#include <presenter/ReactiveProperty.h>
#include <presenter/Command.h>
#include <state/Store.h>
#include <state/Model.h>

namespace Forged::Presenter
{

struct PanelState
{
    bool isVisible;
};

class IMessagePanel
{
public:
    virtual bool isVisible() = 0;
    virtual void setIsVisible(bool value) = 0;
};

class MessagePanel : public IMessagePanel
{
public:
    MessagePanel(IServiceLocator& services)
    : mServices(services) 
    , mVisible(true)
    , mStateProperty({ false })
    {
        using namespace View::ControlHashes;

        services.getUIService().getStore().dispatch(State::UpdatePanelVisibility(MessagePanelHash, true));

        services.getUIService().subscribeToPanelChanges([&](const State::Panel& panel)
        {
            mVisible = panel.isVisible;
        }, 
        MessagePanelHash);
    }

    bool isVisible() { return mVisible; }

    void setIsVisible(bool value)
    {
         mVisible = value;
         mServices.getUIService().getStore().dispatch(State::UpdatePanelVisibility(View::ControlHashes::MessagePanelHash, value));
    }

private:
    IServiceLocator& mServices;
    Presenter::ReactiveProperty<PanelState> mStateProperty;
    bool mVisible = false;
};

}