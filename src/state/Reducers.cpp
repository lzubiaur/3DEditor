#include <state/Reducers.h>

namespace Forged::State
{

Panel dummyPanel = { std::hash<View::ControlHashInfo>{}({ "DummyPanel", View::ControlType::Panel }), false, "DummyPanel" };

Panel& getPanel(AppState &state, const View::ControlHash &hash)
{
    auto iter = std::find_if(state.panels.begin(), state.panels.end(), [hash](const Panel &panel) { return panel.id == hash; });

    return iter != state.panels.end() ? *iter : dummyPanel;
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
        // TODO
        auto s = state;
        return getPanel(s, hash);
    };
}

Reducer AddPanel(const Panel& panel)
{
    return [&panel](AppState& state)
    {
        state.panels.push_back(panel);
        return state;
    };
}

Reducer UpdatePanelVisibility(const View::ControlHash& hash, bool value)
{
    return [value, hash](AppState& state)
    {
        auto& panel = getPanel(state, hash);
        panel.isVisible = value;

        return state;
    };
}

Reducer TogglePanelVisibility(const View::ControlHash& hash)
{
    return [hash](AppState& state)
    {
        auto& panel = getPanel(state, hash);
        panel.isVisible = !panel.isVisible;

        return state;
    };
}

}
