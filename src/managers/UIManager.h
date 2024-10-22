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

namespace Forged
{

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
    IUIService& getUIService() override;

    ControlPtr createControl(ControlType type, const std::string& name) override;
    ControlPtr findControl(const std::string& name) override;

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
    std::vector<ControlPtr> mControls;
    EventLoop mEventLoop;
};

}