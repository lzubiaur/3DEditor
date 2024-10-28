#pragma once

#include <services/IServiceLocator.h>
#include <state/Store.h>
#include <state/Model.h>
#include <view/UIControlHash.h>

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
    // using DemoPanelHash = Forged::View::ControlHashes::DemoPanelHash;

    DemoPanel(IServiceLocator& services)
    : mServices(services)
    , mUIService(services.getUIService())
    , mVisible(false)
    {
        setIsVisible(false);

        mUIService.subscribeToPanelChanges([&](const State::Panel& panel)
        {
            mVisible = panel.isVisible;
        }, 
        View::ControlHashes::DemoPanelHash);
    }

    bool isVisible() { return mVisible; }

    void setIsVisible(bool value)
    {
         mVisible = value;
         mUIService.getStore().dispatch(State::UpdatePanelVisibility(View::ControlHashes::DemoPanelHash, value));
    }

private:
    IServiceLocator& mServices;
    IUIService &mUIService;
    bool mVisible = false;
};

}