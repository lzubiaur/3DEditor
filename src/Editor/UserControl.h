#pragma once

#include <editor/IControl.h>

namespace Engine 
{

class UserControl : public IControl
{
public:
    bool onInitialize() override;
    void onDraw() override;
};

}