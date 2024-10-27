#pragma once

#include <utils/Types.h>
#include <state/Model.h>

#include <string>
#include <variant>

namespace Forged::State
{

struct AddObject
{
    Panel panel;
};

struct RemoveObject
{
    Guid id;
};

struct UpdateTitle
{
    Guid id;
    std::string title;
};

struct UpdateVisibility
{
    Guid id;
    bool isVisible;
};

struct ToggleVisibility
{
    Guid id;
};

using TestActions = std::variant<UpdateTitle>;
using PanelActions = std::variant<AddObject, RemoveObject, UpdateTitle, UpdateVisibility, ToggleVisibility>;
using AllActions = std::variant<PanelActions, TestActions>;

}