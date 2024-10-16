#pragma once

#include <editor/IControl.h>

namespace Engine 
{

class UserControl : public IControl
{
public:
    void onInitialize() override;
    void onDraw() override;
};

}