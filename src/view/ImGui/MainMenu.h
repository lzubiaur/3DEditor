#pragma once

#include <view/IUIControl.h>
#include <services/IServiceLocator.h>

namespace Forged::View
{

class MainMenu : public IUIControl
{
public:
    MainMenu() = delete;
    MainMenu(IServiceLocator& services);

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

private:
    void drawFileMenu();
    void drawWindowsMenu();
    void drawHelpMenu();

private:
    IServiceLocator& mServices;
    SignalService& mSignals;
    IReactiveService& mReact;
};

}