#include <state/Reducers.h>
#include <state/Model.h>

namespace Forged::State
{

Panel dummyPanel = { "DummyPanel", false, "Dummy Panel" };

Panel &getPanel(AppState &state, const Guid &id)
{
    auto iter = std::find_if(state.panels.begin(), state.panels.end(), [&id](const Panel &panel) { return panel.id == id; });

    return iter != state.panels.end() ? *iter : dummyPanel;
}

PanelPredicate panelPredicate = [](Panel a, Panel b)
{
    return a.id == b.id && a.isVisible == b.isVisible && a.title == b.title;
};

PanelSelector panelSelector = [](AppState state) -> Panel
{
    // TODO
    // return getPanel(state, id);
    return dummyPanel;
};

PanelReducer panelReducer = [](AppState state, PanelActions action)
{
    std::visit([&state](auto&& action)
    {
        using T = std::decay_t<decltype(action)>;

        if constexpr (std::is_same_v<T, AddObject>)
        {
            state.panels.push_back(action.panel);
        }
        else if constexpr (std::is_same_v<T, RemoveObject>)
        {
            // TODO
        }
        else if constexpr (std::is_same_v<T, UpdateTitle>)
        {
            getPanel(state, action.id).title = action.title;
        }
        else if constexpr (std::is_same_v<T, ToggleVisibility>)
        {
            auto& panel = getPanel(state, action.id);
            panel.isVisible = !panel.isVisible;
        }
        else if constexpr (std::is_same_v<T, UpdateVisibility>)
        {
            getPanel(state, action.id).isVisible = action.isVisible;
        }
        else 
        {
           static_assert(false, "non-exhaustive visitor!");
        }
    }, action);

    return state;
};

extern MainReducer mainReducer = [](AppState state, AllActions action)
{
    std::visit([&state](auto&& action)
    {
        using T = std::decay_t<decltype(action)>;

        if constexpr (std::is_same_v<T, PanelActions>)
        {
            state = panelReducer(state, action);
        }
        else if constexpr (std::is_same_v<T, TestActions>)
        {
            // TODO
        }
        else 
        {
           static_assert(false, "non-exhaustive visitor!");
        }
    }, action);

    return state;
};

}
