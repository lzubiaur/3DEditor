#pragma once

#include <presenter/ReactiveProperty.h>
#include <presenter/ReactiveCommand.h>

namespace Forged::Presenter
{

struct MainMenuCommandParameter
{

};

class IMainMenu
{
public:
    using MainMenuCommand = ReactiveCommand<MainMenuCommandParameter>;

    ~IMainMenu() noexcept = default;

    virtual MainMenuCommand& getToggleLogMessagePanelCmd() = 0;
};

class MainMenu : public IMainMenu
{
public:
    MainMenu()
    {
        mToggleLogMessagePanelCmd.bind([](auto parameter)
        {
            
        });
    }

    MainMenuCommand& getToggleLogMessagePanelCmd() { return mToggleLogMessagePanelCmd; }
    

    
private:
    MainMenuCommand mToggleLogMessagePanelCmd;
};

}