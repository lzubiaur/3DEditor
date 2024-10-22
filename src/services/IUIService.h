#pragma once

#include <view/IUIControl.h>
#include <services/IService.h>

#include <string>
#include <memory>

namespace Forged
{

class IUIService
{
public:
    using ControlPtr = std::shared_ptr<View::IUIControl>;

    // TODO createDialog

    virtual ControlPtr findControl(const std::string& panelName) = 0;
};

}