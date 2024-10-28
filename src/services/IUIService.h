#pragma once

#include <view/IUIControl.h>
#include <services/IService.h>
#include <presenter/Command.h>
#include <state/Store.h>
#include <state/Reducers.h>
#include <state/Model.h>
#include <view/UIControlHash.h>

#include <string>
#include <memory>

namespace Forged
{
// TODO rename IUIControlService

class IUIService
{
public:
    using ControlPtr = std::shared_ptr<View::IUIControl>;
    using ControlType = View::ControlType;
    using ApplicationCommand = Presenter::Command::ApplicationCommand;
    using PanelCommand = Presenter::Command::PanelCommand;
    using Store = State::Store<State::AppState>;

    virtual ControlPtr createControl(ControlType type, const std::string& name) = 0;
    virtual ControlPtr findControl(const std::string& panelName) = 0;

    virtual Store& getStore() = 0;
    virtual void subscribeToPanelChanges(State::PanelObserver observer, View::ControlHash id) = 0;

    // Access to application global commands
    virtual ApplicationCommand& getApplicationCommand() = 0;
    virtual PanelCommand& getPanelCommand() = 0; 
};

}