
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

enum class AppStatus
{
    Starting, Running, Closing, Closed
};

struct AppState
{
    AppStatus appStatus;
    std::unordered_map<View::ControlHash, Panel> panels;
};

}