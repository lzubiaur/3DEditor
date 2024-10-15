#include <core/Application.h>

#include <iostream>
#include <utility>
#include <memory>

#include <utils/Common.h>

namespace Engine
{

Application::Application(IPlatform& platform)
: mPlatform(platform)
{
}

void Application::addSystem(ISystem& system)
{
    mSystems.push_back(system);
}

void Application::removeSystem(ISystem& system)
{
    // TODO
}

void Application::run()
{
    initialize();
    mRunning = true;

    while (!mPlatform.shouldClose() && !mCloseRequested)
    {
        mPlatform.onPreUpdate();

        updateSystems();

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
    mPlatform.onInitialize();
    initializeSystems();
}

void Application::shutdown()
{
    shutdownSystems();
    mPlatform.onShutdown();
}

void Application::initializeSystems()
{
    std::for_each(mSystems.begin(), mSystems.end(), [](ISystem& system) { system.onInitialize(); });
}

void Application::updateSystems()
{
    std::for_each(mSystems.begin(), mSystems.end(), [](ISystem& system) { system.onPreUpdate(); });
    std::for_each(mSystems.begin(), mSystems.end(), [](ISystem& system) { system.onUpdate(); });
    std::for_each(mSystems.begin(), mSystems.end(), [](ISystem& system) { system.onPostUpdate(); });
}

void Application::shutdownSystems()
{
    std::for_each(mSystems.begin(), mSystems.end(), [](ISystem& system) { system.onShutdown(); });
}

}
