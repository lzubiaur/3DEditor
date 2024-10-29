#include <core/Application.h>

#include <iostream>
#include <utility>
#include <memory>

#include <utils/Common.h>
#include <state/Reducers.h>

namespace Forged
{

// TODO add saving/loading for the store

Application::Application(IPlatform& platform)
: mPlatform(platform)
, mStore(State::AppState{})
{
}

void Application::addSystem(SystemPtr system)
{
    mSystems.push_back(system);
}

void Application::removeSystem(SystemPtr system)
{
    // TODO
}

void Application::run()
{
    initialize();

    while (!mPlatform.shouldClose() && !mCloseRequested)
    {
        mPlatform.onPreUpdate();

        updateSystems();

        mPlatform.onPostUpdate();
    }

    shutdown();
}

bool Application::isRunning()
{
    return mRunning;
}

void Application::close()
{
    // TODO signal close requested

    // TODO if closing confirm then close

    mCloseRequested = true;
}

const IPlatform& Application::getPlatform() const
{
    return mPlatform;
}

void Application::initialize()
{
    mStore.subscribeToState([&](State::AppState state)
    {
        if (state.appStatus == State::AppStatus::Closing)
        {
            close();
        }
    });

    mStore.startEmitting();
    mStore.dispatch(State::UpdateAppStatus(State::AppStatus::Starting));

    mPlatform.onInitialize();
    initializeSystems();

    mRunning = true;
    mStore.dispatch(State::UpdateAppStatus(State::AppStatus::Running));

    mLogService.info("Application ready");
}

void Application::shutdown()
{
    mLogService.info("Shutting Down...");

    shutdownSystems();
    mPlatform.onShutdown();

    mLogService.info("Closed");
    mLogService.onShutdown();
    mRunning = false;
}

void Application::initializeSystems()
{
    std::for_each(mSystems.begin(), mSystems.end(), [](SystemPtr system) { system->onInitialize(); });
}

void Application::updateSystems()
{
    std::for_each(mSystems.begin(), mSystems.end(), [](SystemPtr system) { system->onPreUpdate(); });
    std::for_each(mSystems.begin(), mSystems.end(), [](SystemPtr system) { system->onUpdate(); });
    std::for_each(mSystems.begin(), mSystems.end(), [](SystemPtr system) { system->onPostUpdate(); });
}

void Application::shutdownSystems()
{
    std::for_each(mSystems.begin(), mSystems.end(), [](SystemPtr system) { system->onShutdown(); });
}

}
