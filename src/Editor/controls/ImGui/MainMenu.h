#pragma once

#include <editor/IControl.h>
#include <services/IServiceLocator.h>

namespace Engine
{

class MainMenu : public IControl
{
public:
    MainMenu() = delete;
    MainMenu(IServiceLocator& services);

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

private:
    IServiceLocator& mServices;
};

}