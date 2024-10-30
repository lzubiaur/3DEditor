#include <algorithm>

#include <managers/UIManager.h>
#include <presenter/Events.h>
#include <state/Reducers.h>

namespace Forged
{

using ControlPtr = UIManager::ControlPtr;

UIManager::UIManager(const Dependencies& dependencies)
: mApplication(dependencies.application)
, mUIBuilder(dependencies.uiBuilder)
, mRenderer(dependencies.renderer)
, mLogService(dependencies.logService)
, mSignalService(dependencies.signalService)
, mReactiveService(dependencies.reactiveService)
, mEventBus(dependencies.eventBus)
, mEventLoop(dependencies.eventLoop)
, mStore(dependencies.application.getStore())
{}

void UIManager::onInitialize()
{
    mRenderer.onInitialize();

    addControl(mUIBuilder.buildMainMenu(*this));
    addControl(mUIBuilder.buildNodeGraph(*this));
    addControl(mUIBuilder.buildMessageConsole(*this));
    addControl(mUIBuilder.buildSandboxWindow(*this));
    addControl(mUIBuilder.buildDemoPanel(*this));
    addControl(mUIBuilder.buildPlotDemoPanel(*this));

    std::for_each(mControls.begin(), mControls.end(), [](const auto& pair) { pair.second->onInitialize(); });

    mLogService.info("UI system ready...");
}

void UIManager::onPreUpdate()
{
    mRenderer.onNewFrame();
}

void UIManager::onUpdate()
{
    std::for_each(mControls.begin(), mControls.end(), [](const auto& pair) { pair.second->onDraw(); });

    mEventLoop.update();
}

void UIManager::onPostUpdate()
{
    mRenderer.onRender();
}

void UIManager::onShutdown()
{
    std::for_each(mControls.begin(), mControls.end(), [](const auto& pair) { pair.second->onShutdown(); });

    mSignalService.onShutdown();
    mRenderer.onShutdown();
    mEventLoop.onShutdown();
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

IEventLoop& UIManager::getEventLoop()
{
    return mEventLoop;
}

IUIService& UIManager::getUIService()
{
    return *this;
}

void UIManager::addControl(ControlPtr control)
{
    if (control == nullptr)
    {
        return;
    }

    mControls[{ control->getName(), View::ControlType::Panel }] = control;
    mStore.dispatch(State::AddPanel({ control->getHash(), false, control->getName() }));

    if (mApplication.isRunning())
    {
        control->onInitialize();
    }
}

ControlPtr UIManager::createControl(IUIService::ControlType type, const std::string& name)
{
    auto control = findControl(name);

    if (control != nullptr)
    {
        return control;
    }

    control = mUIBuilder.buildControl(type, *this);

    // Defer adding the control to the event loop so that createControl,
    // which modifies the controls list, can be called within the update loop.
    mEventLoop.immediate([&, control]() { addControl(control); });

    return control;
}

ControlPtr UIManager::findControl(const std::string& name)
{
    auto iter = mControls.find({ name, View::ControlType::Panel });

    return iter != mControls.end() ? iter->second : nullptr;
}

void UIManager::subscribeToPanelChanges(State::PanelObserver observer, View::ControlHash id)
{
    mStore.subscribeToSlice(
        State::GetPanelSelector(id),
        State::GetPanelPredicate(),
        observer);
}

}