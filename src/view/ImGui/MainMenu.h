#pragma once

#include <view/UserControl.h>
#include <services/IServiceLocator.h>
#include <presenter/MainMenu.h>

namespace Forged::View
{

class MainMenu : public UserControl
{
public:
    MainMenu() = delete;
    MainMenu(Presenter::IMainMenu& presenter);

    ControlType getType() override { return ControlType::MainMenu; }
    std::string getName() override { return "MainMenu"; }

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