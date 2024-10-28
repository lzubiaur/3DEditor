#pragma once

#include <utils/Types.h>
#include <state/Model.h>
#include <view/UIControlHash.h>

#include <string>
#include <variant>

namespace Forged::State
{

struct AddObject
{
    View::ControlHash id;
    bool isVisible;
    std::string title;
};

struct RemoveObject
{
    View::ControlHash id;
};

struct UpdateTitle
{
    View::ControlHash id;
    std::string title;
};

struct UpdateVisibility
{
    View::ControlHash id;
    bool isVisible;
};

struct ToggleVisibility
{
    View::ControlHash id;
};

using TestActions = std::variant<UpdateTitle>;
using PanelActions = std::variant<AddObject, RemoveObject, UpdateTitle, UpdateVisibility, ToggleVisibility>;
using AllActions = std::variant<PanelActions, TestActions>;

}