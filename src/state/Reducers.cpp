#include <state/Reducers.h>

namespace Forged::State
{

Panel dummyPanel = { std::hash<View::ControlHashInfo>{}({ "DummyPanel", View::ControlType::Panel }), false, "DummyPanel" };

Panel& getPanel(const AppState &state, const View::ControlHash &hash)
{
    if (state.panels.find(hash) != state.panels.end())
    {
        return *state.panels.at(hash);
    }

    return dummyPanel;
}

PanelPredicate GetPanelPredicate()
{
    return [](const Panel& a, const Panel& b)
    {
        return a.id == b.id && a.isVisible == b.isVisible && a.title == b.title;
    };
}

PanelSelector GetPanelSelector(const View::ControlHash& hash)
{
    return [hash](const AppState& state) -> Panel
    {
        return getPanel(state, hash);
    };
}

Reducer AddPanel(const Panel& panel)
{
    return [&panel](const AppState& state)
    {
        AppState newState = state;
        newState.panels[panel.id] = std::make_shared<Panel>(panel);
        return newState;
    };
}

Reducer UpdatePanelVisibility(const View::ControlHash& hash, bool value)
{
    return [value, hash](const AppState& state)
    {
        auto panel = getPanel(state, hash);
        panel.isVisible = value;

        return state;
    };
}

Reducer TogglePanelVisibility(const View::ControlHash& hash)
{
    return [hash](const AppState& state)
    {
        auto& panel = getPanel(state, hash);
        panel.isVisible = !panel.isVisible;

        return state;
    };
}

}
