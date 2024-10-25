#pragma once

#include <services/IServiceLocator.h>
#include <presenter/ReactiveProperty.h>
#include <presenter/Command.h>

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
};

class MessagePanel : public IMessagePanel
{
public:
    MessagePanel(IServiceLocator& services)
    : mServices(services) 
    , mVisible(false)
    , mStateProperty({ false })
    {
        services.getUIService().getPanelCommand().bind([&](Command::PanelCommandArgument arg)
        {
            if (arg.panelName == "MessageConsole" && arg.type == Command::PanelCommandType::TogglePanel)
            {
                mVisible = !mVisible;

                auto state = mStateProperty.getValue();
                state.isVisible = mVisible;
                mStateProperty.setValue(state);
            }
        });
    }

    bool isVisible() { return mVisible; }

private:
    IServiceLocator& mServices;
    Presenter::ReactiveProperty<PanelState> mStateProperty;
    bool mVisible = false;
};

}