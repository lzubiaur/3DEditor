#pragma once

#include <state/Actions.h>
#include <state/Model.h>

#include <variant>
#include <functional>

namespace Forged::State
{

Panel& getPanel(AppState &state, const View::ControlHash &id);

// -------------------------- Actions ---------------------------
using Reducer = std::function<AppState(AppState&)>;

Reducer AddPanel(const Panel& panel);
Reducer UpdatePanelVisibility(const View::ControlHash& hash, bool value);
extern Reducer TogglePanelVisibility(const View::ControlHash& hash);

// ------------------------- Predicates -------------------------
using PanelPredicate = std::function<bool(const Panel&, const Panel&)>;
extern PanelPredicate GetPanelPredicate();

// ------------------------- Selectors --------------------------
using PanelSelector = std::function<Panel(const AppState&)>;
extern PanelSelector GetPanelSelector(const View::ControlHash& hash);

// ------------------------- Observers --------------------------

using PanelObserver = std::function<void(const Panel&)>;
}
