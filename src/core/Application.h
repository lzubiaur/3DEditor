#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <boost/di.hpp>

#include <core/ISystem.h>
#include <core/IApplication.h>
#include <core/IPlatform.h>
#include <state/Store.h>

namespace Forged 
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

    bool isRunning() override;
    void close() override;

    void addSystem(SystemPtr system) override;
    void removeSystem(SystemPtr system) override;
    const IPlatform& getPlatform() const override;
    Store& getStore() override { return mStore; }

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
    std::vector<SystemPtr> mSystems;
    Store mStore;
};

}
