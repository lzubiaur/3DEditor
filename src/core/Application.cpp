#include <core/Application.h>

#include <iostream>
#include <utility>
#include <memory>

#include <utils/Common.h>

namespace Engine
{

Application::Application(IPlatform& platform, std::vector<ManagerPtr>& managers)
: mPlatform(platform)
, mManagers(std::move(managers))
{
}

void Application::run()
{
    initialize();
    mRunning = true;

    while (!mPlatform.shouldClose() && !mCloseRequested)
    {
        mPlatform.onPreUpdate();

        updateManagers();

        mPlatform.onPostUpdate();
    }

    mRunning = false;
    shutdown();
}

void Application::requestClose()
{
    // TODO signal close requested

    // TODO if closing confirm then close

    mCloseRequested = false;
}

const IPlatform& Application::getPlatform() const
{
    return mPlatform;
}

void Application::initialize()
{
    initializeManagers();

    mPlatform.onInitialize();
}

void Application::shutdown()
{
    shutdownManagers();
}

void Application::initializeManagers()
{
    std::for_each(mManagers.begin(), mManagers.end(), [](const auto& manager) { manager->onInitialize(); });
}

void Application::updateManagers()
{
    std::for_each(mManagers.begin(), mManagers.end(), [](const ManagerPtr& manager) { manager->onPreUpdate(); });
    std::for_each(mManagers.begin(), mManagers.end(), [](const ManagerPtr& manager) { manager->onUpdate(); });
    std::for_each(mManagers.begin(), mManagers.end(), [](const ManagerPtr& manager) { manager->onPostUpdate(); });
}

void Application::shutdownManagers()
{
    std::for_each(mManagers.begin(), mManagers.end(), [](const auto& manager) { manager->onShutdown(); });
}

}
