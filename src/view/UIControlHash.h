#pragma once

#include <string>

namespace Forged::View
{

enum class ControlType
{
    None,
    Menu,
    Panel,
};

namespace ControlName
{
constexpr const char* MainMenu = "MainMenu";
constexpr const char* DemoPanel = "DemoPanel";
constexpr const char* NodeGraph = "NodeGraph";
constexpr const char* MainWindow = "MainWindow";
constexpr const char* MessagePanel = "MessagePanel";
}

struct ControlHashInfo
{
    std::string name;
    ControlType type;
    bool operator==(const ControlHashInfo &) const = default;
};
 
template<>
struct std::hash<ControlHashInfo>
{
    std::size_t operator()(const ControlHashInfo& id) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(id.name);
        std::size_t h2 = std::hash<ControlType>{}(id.type);
        return h1 ^ (h2 << 1);
    }
};

using ControlHash = std::size_t;

namespace ControlHashes
{
inline ControlHash MainMenuHash = std::hash<ControlHashInfo>{}({ ControlName::MainMenu, ControlType::Menu });
inline ControlHash NodeGraphHash = std::hash<ControlHashInfo>{}({ ControlName::NodeGraph, ControlType::Panel});
inline ControlHash DemoPanelHash = std::hash<ControlHashInfo>{}({ ControlName::DemoPanel, ControlType::Panel });
inline ControlHash MainWindowHash = std::hash<ControlHashInfo>{}({ ControlName::MainWindow, ControlType::Panel });
inline ControlHash MessagePanelHash = std::hash<ControlHashInfo>{}({ ControlName::MessagePanel, ControlType::Panel });
}

}