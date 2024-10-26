#pragma once

#include <state/Actions.h>
#include <state/Model.h>

#include <variant>
#include <functional>

namespace Forged::State
{
// TODO Use macros to declare reducer, predicate...

// TODO use reference for the State?
using MainReducer = std::function<AppState(AppState, AllActions)>;
using PanelSelector = std::function<Panel(AppState)>;

extern MainReducer mainReducer;
extern PanelSelector panelSelector;

// TODO use reference for the State?
using PanelReducer = std::function<AppState(AppState, PanelActions)>;
using PanelObserver = std::function<void(Panel)>;
using PanelPredicate = std::function<bool(Panel, Panel)>;

extern PanelReducer panelReducer;
extern PanelPredicate panelPredicate;

extern Panel &getPanel(AppState &state, const Guid &id);
}
