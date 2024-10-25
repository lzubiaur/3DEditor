#pragma once

#include <utils/Types.h>

#include <string>
#include <variant>

namespace Forge::State::Actions
{

struct AddObject
{
    Guid id;
};

struct RemoveObject
{
    Guid id;
};

struct GetObject
{
    Guid id;
};

struct UpdateTitle
{
    std::string title;
};

struct UpdateVisibility
{
    bool isVisible;
};

using PanelAction = std::variant<AddObject, RemoveObject, GetObject, UpdateTitle, UpdateVisibility>;

}