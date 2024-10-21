#include <algorithm>

#include <managers/UIManager.h>
#include <presenter/Events.h>

namespace Forged
{

UIManager::UIManager(const Dependencies& dependencies)
: mApplication(dependencies.application)
, mUIBuilder(dependencies.uiBuilder)
, mRenderer(dependencies.renderer)
, mLogService(dependencies.logService)
, mSignalService(dependencies.signalService)
, mReactiveService(dependencies.reactiveService)
, mEventBus(dependencies.eventBus)
{}

void UIManager::onInitialize()
{
    auto signal = mSignalService.registerSignal<void()>(Presenter::UIEvents::OnRequestAppClose);

    signal->subscribe([&]()
    {
        mApplication.close();
    });

    mRenderer.onInitialize();

    addControl(mUIBuilder.buildMainMenu(*this));
    addControl(mUIBuilder.buildNodeGraph(*this));
    addControl(mUIBuilder.buildMessageConsole(*this));
    addControl(mUIBuilder.buildSandboxWindow(*this));

    std::for_each(mControls.begin(), mControls.end(), [](auto control) { control->onInitialize(); });
}

void UIManager::onPreUpdate()
{
    mRenderer.onNewFrame();
}

void UIManager::onUpdate()
{
    std::for_each(mControls.begin(), mControls.end(), [](auto control) { control->onDraw(); });
}

void UIManager::onPostUpdate()
{
    mRenderer.onRender();
}

void UIManager::onShutdown()
{
    std::for_each(mControls.begin(), mControls.end(), [](auto control) { control->onShutdown(); });

    mSignalService.onShutdown();
    mLogService.onShutdown();
    mRenderer.onShutdown();
}

SignalService& UIManager::getSignalService() 
{
    return mSignalService;
}

LogService& UIManager::getLogService()
{
    return mLogService;
}
    
IReactiveService& UIManager::getReactiveService()
{
    return mReactiveService;
}

EventBus& UIManager::getEventBus()
{
    return mEventBus;
}

void UIManager::addControl(ControlPtr control)
{
    mControls.push_back(control);

    if (mApplication.isRunning())
    {
        control->onInitialize();
    }
}

}