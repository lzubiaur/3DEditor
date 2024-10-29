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

    virtual bool isMessagePanelVisible() = 0;
    virtual bool isDemoPanelVisible() = 0;

    virtual void setIsMessagePanelVisible(bool value) = 0;
    virtual void setIsDemoPanelVisible(bool value) = 0;

    virtual void closeApplication() = 0;
};

class MainMenu : public IMainMenu
{
public:
    MainMenu(IServiceLocator& services);

    bool isMessagePanelVisible() override;
    bool isDemoPanelVisible() override;

    void setIsMessagePanelVisible(bool value) override;
    void setIsDemoPanelVisible(bool value) override;

    void closeApplication() override;

private:
    void dispatch(State::Reducer reducer);

private:
    bool mIsMessagePanelVisible;
    bool mIsDemoPanelVisible;
    IServiceLocator& mServices;
};

}