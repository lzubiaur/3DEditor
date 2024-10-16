#pragma once

#include <editor/IControl.h>
#include <managers/UIManager.h>

namespace Engine
{

class MainMenu : public IControl
{
public:
    MainMenu() = delete;
    MainMenu(UIManager& manager);

    void onInitialize() override;
    void onDraw() override;

private:
    UIManager& mManager;
};

}