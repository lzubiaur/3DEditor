#include <algorithm>

#include <managers/UIManager.h>

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
    auto signal = mSignalService.registerSignal<void()>("ui.onRequestAppClose");

    signal->subscribe([&]()
    {
        mApplication.requestClose();
    });

    mRenderer.initialize();

    addControl(mUIBuilder.buildMainMenu(*this));
    addControl(mUIBuilder.buildNodeGraph(*this));

    std::for_each(mControls.begin(), mControls.end(), [](auto control) { control->onInitialize(); });
}

void UIManager::onPreUpdate()
{
    mRenderer.newFrame();
}

void UIManager::onUpdate()
{
    std::for_each(mControls.begin(), mControls.end(), [](auto control) { control->onDraw(); });
}

void UIManager::onPostUpdate()
{
    mRenderer.render();
}

void UIManager::onShutdown()
{
    // TODO
    // std::for_each(mControls.begin(), mControls.end(), [](auto control) { control->onShutDown(); });

    mRenderer.shutdown();
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