#pragma once

#include <view/IUIControl.h>
#include <services/IServiceLocator.h>
#include <presenter/MainMenu.h>

namespace Forged::View
{

class MainMenu : public IUIControl
{
public:
    MainMenu() = delete;
    MainMenu(Presenter::IMainMenu& presenter);

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

private:
    void drawFileMenu();
    void drawWindowsMenu();
    void drawHelpMenu();

private:
    Presenter::IMainMenu& mPresenter;
};

}