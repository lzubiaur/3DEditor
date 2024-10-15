#pragma once

#include <memory>
#include <vector>

#include <core/IApplication.h>
#include <core/IPlatform.h>
#include <managers/IManager.h>

namespace Engine 
{

class Application : public IApplication
{
public:
    using ManagerPtr = std::unique_ptr<IManager>;

    Application(IPlatform& platform, std::vector<ManagerPtr>& managers);
    ~Application() = default;

    Application(Application&&) noexcept = delete;
    Application& operator=(Application&&) noexcept = delete;

    Application(Application&) noexcept = delete;
    Application& operator=(Application&) noexcept = delete;

    void run();

    void requestClose() override;
    const IPlatform& getPlatform() const override;

private:
    void initialize();
    void shutdown();

    void initializeManagers();
    void updateManagers();
    void shutdownManagers();

public:
    bool mRunning = false;
    bool mCloseRequested = false;
    IPlatform& mPlatform;
    std::vector<ManagerPtr> mManagers;
};

}
