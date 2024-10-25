
#pragma once

#include <utils/Types.h>

#include <string>
#include <vector>

namespace Forge::State::Model
{

struct Panel
{
    Guid id;
    bool isVisible;
    std::string title;
};

struct AppState
{
    std::vector<Panel> panels;
};

}