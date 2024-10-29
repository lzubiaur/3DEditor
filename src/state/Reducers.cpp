#include <state/Reducers.h>

namespace Forged::State
{

Panel dummyPanel = { std::hash<View::ControlHashInfo>{}({ "DummyPanel", View::ControlType::Panel }), false, "DummyPanel" };

Panel& findPanel(AppState &state, const View::ControlHash &hash)
{
    auto iter = state.panels.find(hash); 
    return iter != state.panels.end() ? iter->second : dummyPanel;
}

const Panel& findPanel(const AppState &state, const View::ControlHash &hash)
{
    auto iter = state.panels.find(hash); 
    return iter != state.panels.end() ? iter->second : dummyPanel;
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
        return findPanel(state, hash);
    };
}

Reducer AddPanel(const Panel& panel)
{
    return [&panel](const AppState& state)
    {
        AppState newState = state;
        newState.panels[panel.id] = panel;
        return newState;
    };
}

Reducer UpdatePanelVisibility(const View::ControlHash& hash, bool value)
{
    return [value, hash](const AppState& state)
    {
        AppState newState = state;
        auto& panel = findPanel(newState, hash);
        panel.isVisible = value;

        return newState;
    };
}

Reducer TogglePanelVisibility(const View::ControlHash& hash)
{
    return [hash](const AppState& state)
    {
        AppState newState = state;
        auto& panel = findPanel(newState, hash);
        panel.isVisible = !panel.isVisible;

        return newState;
    };
}

AppStatus validateAppStatus(AppStatus currentStatus, AppStatus newStatus)
{
    switch (newStatus)
    {
        case AppStatus::Starting:
            if (currentStatus == AppStatus::Closed)
            {
                return newStatus;
            }
        case AppStatus::Running:
            if (currentStatus == AppStatus::Starting)
            {
                return newStatus;
            }
        case AppStatus::Closing:
            if (currentStatus == AppStatus::Starting | currentStatus == AppStatus::Running)
            {
                return newStatus;
            }
        case AppStatus::Closed:
            if (currentStatus == AppStatus::Closing)
            {
                return newStatus;
            }
        default:
            return currentStatus;
    }
}

Reducer UpdateAppStatus(AppStatus status)
{
    return [status](const AppState& state)
    {
        AppState newState = state;
        newState.appStatus = validateAppStatus(state.appStatus, status);

        return newState;
    };
}

}
