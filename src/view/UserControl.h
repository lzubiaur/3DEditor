#pragma once

#include <view/IUIControl.h>

namespace Forged::View
{

class UserControl : public IUIControl
{
public:
    bool isVisible() override { return mOpen; }
    void hide() override { mOpen = false; }
    void show() override { mOpen = true; }

protected:
    bool mOpen = true;
};

}