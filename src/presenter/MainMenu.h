#pragma once

#include <presenter/ReactiveProperty.h>
#include <presenter/ReactiveCommand.h>
#include <presenter/Command.h>
#include <services/IServiceLocator.h>

namespace Forged::Presenter
{

using namespace Command;

class IMainMenu
{
public:
    ~IMainMenu() noexcept = default;

    virtual ApplicationCommand& getApplicationCommand() = 0;
    virtual PanelCommand& getPanelCommand() = 0;
};

class MainMenu : public IMainMenu
{
public:
    MainMenu(IServiceLocator& services);

    ApplicationCommand& getApplicationCommand() { return mApplicationCommand; }
    PanelCommand& getPanelCommand() { return mPanelCommand; }
    
private:
    ApplicationCommand mApplicationCommand;
    PanelCommand mPanelCommand;
    IServiceLocator& mServices;
};

}