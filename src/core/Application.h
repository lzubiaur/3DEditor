#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <boost/di.hpp>

#include <core/ISystem.h>
#include <core/IApplication.h>
#include <core/IPlatform.h>

namespace Engine 
{

class Application : public IApplication
{
public:
    Application() = delete;
    ~Application() noexcept = default;

    BOOST_DI_INJECT(Application, IPlatform& platform);

    Application(Application&&) noexcept = delete;
    Application& operator=(Application&&) noexcept = delete;

    Application(Application&) noexcept = delete;
    Application& operator=(Application&) noexcept = delete;

    void run();

    void requestClose() override;

    void addSystem(ISystem& system) override;
    void removeSystem(ISystem& system) override;

    const IPlatform& getPlatform() const override;

private:
    void initialize();
    void shutdown();

    void initializeSystems();
    void updateSystems();
    void shutdownSystems();

public:
    bool mRunning = false;
    bool mCloseRequested = false;
    IPlatform& mPlatform;
    std::vector<std::reference_wrapper<ISystem>> mSystems;
};

}
