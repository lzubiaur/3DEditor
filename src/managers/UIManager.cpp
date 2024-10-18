#include <algorithm>

#include <managers/UIManager.h>
#include <editor/UIEvents.h>

namespace Engine
{

UIManager::UIManager(IApplication& application, IUIRenderer& renderer, IUIBuilder& uiBuilder, SignalService& signalService, LogService& logService)
: mApplication(application)
, mUIBuilder(uiBuilder)
, mRenderer(renderer)
, mLogService(logService)
, mSignalService(signalService)
{}

void UIManager::onInitialize()
{
    auto signal = mSignalService.registerSignal<void()>(UIEvents::OnRequestAppClose);

    signal->subscribe([&]()
    {
        mApplication.requestClose();
    });

    mRenderer.onInitialize();

    addControl(mUIBuilder.buildMainMenu(*this));
    addControl(mUIBuilder.buildNodeGraph(*this));
    addControl(mUIBuilder.buildMessageConsole(*this));

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

void UIManager::addControl(ControlPtr control)
{
    mControls.push_back(control);

    if (mApplication.isRunning())
    {
        control->onInitialize();
    }
}

}