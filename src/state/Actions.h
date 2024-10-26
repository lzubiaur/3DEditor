#pragma once

#include <utils/Types.h>

#include <string>
#include <variant>

namespace Forged::State
{

struct AddObject
{
    Guid id;
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

using TestActions = std::variant<UpdateTitle>;
using PanelActions = std::variant<AddObject, RemoveObject, UpdateTitle, UpdateVisibility>;
using AllActions = std::variant<PanelActions, TestActions>;

}