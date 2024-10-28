
#pragma once

#include <utils/Types.h>
#include <view/UserControl.h>

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Forged::State
{

struct Panel
{
    View::ControlHash id;
    bool isVisible;
    std::string title;
};

struct AppState
{
    std::unordered_map<View::ControlHash, std::shared_ptr<Panel>> panels;
};

}