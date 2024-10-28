
#pragma once

#include <utils/Types.h>
#include <view/UserControl.h>

#include <string>
#include <vector>

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
    // TODO use std::unordored_map<View::ControlHash, std::shared_ptr<Panel>>
    std::vector<Panel> panels;
};

}