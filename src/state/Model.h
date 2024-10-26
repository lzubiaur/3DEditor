
#pragma once

#include <utils/Types.h>

#include <string>
#include <vector>

namespace Forged::State
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