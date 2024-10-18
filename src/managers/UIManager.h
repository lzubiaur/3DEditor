#pragma once

#include <memory>
#include <vector>
#include <core/IApplication.h>
#include <editor/IControl.h>
#include <editor/IUIRenderer.h>
#include <editor/IUIBuilder.h>
#include <managers/IManager.h>
#include <services/IServiceLocator.h>

namespace Engine
{

class IUI

class UIManager : public IManager, public IServiceLocator
{
public:
    using ControlPtr = std::shared_ptr<IControl>;

    UIManager() = delete;
    UIManager(IApplication& application, IUIRenderer& renderer, IUIBuilder& uiBuilder, SignalService& signalService, LogService& logService);

    void onInitialize() override;
    void onShutdown() override;

    void onPreUpdate() override;
    void onUpdate() override;
    void onPostUpdate() override;

    SignalService& getSignalService() override;
    LogService& getLogService() override;

    void addControl(ControlPtr control);

private:
    IUIRenderer& mRenderer;
    IUIBuilder& mUIBuilder;
    SignalService& mSignalService;
    LogService& mLogService;
    IApplication& mApplication;
    std::vector<ControlPtr> mControls;
};

}