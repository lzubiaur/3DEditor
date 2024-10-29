#pragma once

#include <memory>
#include <vector>
#include <core/IApplication.h>
#include <view/IUIControl.h>
#include <view/IUIRenderer.h>
#include <view/IUIBuilder.h>
#include <managers/IManager.h>
#include <services/IServiceLocator.h>
#include <services/IUIService.h>
#include <services/EventLoop.h>
#include <view/UIControlHash.h>

namespace Forged
{

// UIManager offers a service locator and pre/post/update loops for UI control updates,
// along with an event loop for deferring function calls on the main UI thread.

class UIManager : public IManager, public IServiceLocator, public IUIService
{
public:
    using ControlPtr = std::shared_ptr<View::IUIControl>;

    struct Dependencies
    {
        IApplication& application;
        View::IUIRenderer& renderer;
        View::IUIBuilder& uiBuilder;
        SignalService& signalService;
        LogService& logService;
        IReactiveService& reactiveService;
        EventBus& eventBus;
        IEventLoopInternal& eventLoop;
    };

    UIManager() = delete;
    UIManager(const Dependencies& dependencies);

    void onInitialize() override;
    void onShutdown() override;

    void onPreUpdate() override;
    void onUpdate() override;
    void onPostUpdate() override;

    SignalService& getSignalService() override;
    LogService& getLogService() override;
    IReactiveService& getReactiveService() override;
    EventBus& getEventBus() override;
    IEventLoop& getEventLoop() override;
    IUIService& getUIService() override;

    ControlPtr createControl(ControlType type, const std::string& name) override;
    ControlPtr findControl(const std::string& name) override;
    ApplicationCommand& getApplicationCommand() override { return mApplicationCmd; }
    PanelCommand& getPanelCommand() override { return mPanelCmd; }

    Store& getStore() override { return mStore; }
    void subscribeToPanelChanges(State::PanelObserver observer, View::ControlHash id) override;

private:
    void addControl(ControlPtr control);

private:
    View::IUIRenderer& mRenderer;
    View::IUIBuilder& mUIBuilder;

    SignalService& mSignalService;
    LogService& mLogService;
    IApplication& mApplication;
    EventBus& mEventBus;
    IReactiveService& mReactiveService;

    IEventLoopInternal& mEventLoop;

    // TODO use hash instead of info
    std::unordered_map<View::ControlHashInfo, ControlPtr> mControls;

    // TODO Remove
    ApplicationCommand mApplicationCmd;
    PanelCommand mPanelCmd;
    IApplication::Store& mStore;
};

}