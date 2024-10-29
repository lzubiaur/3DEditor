#pragma once

#include <state/Model.h>

#include <variant>
#include <functional>

namespace Forged::State
{

// -------------------------- Actions ---------------------------
using Reducer = std::function<AppState(const AppState&)>;

Reducer AddPanel(const Panel& panel);
Reducer UpdatePanelVisibility(const View::ControlHash& hash, bool value);
Reducer TogglePanelVisibility(const View::ControlHash& hash);

Reducer UpdateAppStatus(AppStatus status);

// ------------------------- Predicates -------------------------
using PanelPredicate = std::function<bool(const Panel&, const Panel&)>;
PanelPredicate GetPanelPredicate();

// ------------------------- Selectors --------------------------
using PanelSelector = std::function<Panel(const AppState&)>;
PanelSelector GetPanelSelector(const View::ControlHash& hash);

// ------------------------- Observers --------------------------
using PanelObserver = std::function<void(const Panel&)>;

}
