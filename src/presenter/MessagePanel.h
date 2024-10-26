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
        services.getUIService().getStore().dispatch(State::UpdateVisibility{ "MessageConsole", true });

        services.getUIService().subscribeToPanelChanges([&](const State::Panel& panel)
        {
            mVisible = panel.isVisible;
        }, 
        "MessageConsole");

        // services.getUIService().getPanelCommand().bind([&](Command::PanelCommandArgument arg)
        // {
        //     if (arg.panelName == "MessageConsole" && arg.type == Command::PanelCommandType::TogglePanel)
        //     {
        //         mVisible = !mVisible;

        //         auto state = mStateProperty.getValue();
        //         state.isVisible = mVisible;
        //         mStateProperty.setValue(state);
        //     }
        // });
    }

    bool isVisible() { return mVisible; }
    void setIsVisible(bool value)
    {
         mVisible = value;
         execute(State::UpdateVisibility{ "MessageConsole", value });
    }

    void execute(State::PanelActions action)
    {
        mServices.getUIService().getStore().dispatch(action);
    }

private:
    IServiceLocator& mServices;
    Presenter::ReactiveProperty<PanelState> mStateProperty;
    bool mVisible = false;
};

}