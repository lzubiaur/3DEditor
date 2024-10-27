#pragma once

#include <services/IServiceLocator.h>
#include <state/Store.h>
#include <state/Model.h>

namespace Forged::Presenter
{

class IDemoPanel
{
public:
    virtual bool isVisible() = 0;
    virtual void setIsVisible(bool value) = 0;
};

class DemoPanel : public IDemoPanel
{
public:
    DemoPanel(IServiceLocator& services)
    : mServices(services)
    , mVisible(false)
    {
        services.getUIService().getStore().dispatch(State::UpdateVisibility{ "DemoPanel", false });

        services.getUIService().subscribeToPanelChanges([&](const State::Panel& panel)
        {
            mVisible = panel.isVisible;
        }, 
        "DemoPanel");
    }

    bool isVisible() { return mVisible; }

    void setIsVisible(bool value)
    {
         mVisible = value;
         execute(State::UpdateVisibility{ "DemoPanel", value });
    }

    void execute(State::PanelActions action)
    {
        mServices.getUIService().getStore().dispatch(action);
    }

private:
    IServiceLocator& mServices;
    bool mVisible = false;
};

}