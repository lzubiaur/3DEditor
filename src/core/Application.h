#pragma once

#include <memory>
#include <vector>

#include <core/Platform.h>
#include <managers/IManager.h>

namespace Engine 
{

class Application
{
public:
    using ManagerPtr = std::unique_ptr<IManager>;
    using PlatformPtr = std::unique_ptr<Platform>;

    Application(PlatformPtr platform, std::vector<ManagerPtr>& managers);
    ~Application() = default;

    Application(Application&&) noexcept = delete;
    Application& operator=(Application&&) noexcept = delete;

    Application(Application&) noexcept = delete;
    Application& operator=(Application&) noexcept = delete;

    void run();

private:
    bool initialize();
    void shutdown();

    bool initializeUI();
    bool initializeScript();

    void initializeManagers();
    void updateManagers();
    void shutdownManagers();

    void shutDownUI();
    void shutDownScript();

public:
    bool mRunning = false;
    PlatformPtr mPlatform;
    std::vector<ManagerPtr> mManagers;
};

}
