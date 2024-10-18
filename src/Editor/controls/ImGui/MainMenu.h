#pragma once

#include <editor/IControl.h>
#include <services/IServiceProvider.h>

namespace Engine
{

class MainMenu : public IControl
{
public:
    MainMenu() = delete;
    MainMenu(IServiceProvider& services);

    void onInitialize() override;
    void onDraw() override;

private:
    IServiceProvider& mServices;
};

}