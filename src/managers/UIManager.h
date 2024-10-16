#pragma once

#include <memory>
#include <vector>
#include <core/IApplication.h>
#include <editor/IControl.h>
#include <editor/IUIRenderer.h>
#include <managers/IManager.h>
#include <editor/MainWindow.h>
#include <services/SignalService.h>

namespace Engine
{

class UIManager : public IManager, public SignalService
{
public:
    using ControlPtr = std::shared_ptr<IControl>;

    UIManager() = delete;
    UIManager(IApplication& application, IUIRenderer& renderer);

    void onInitialize() override;
    void onShutdown() override;

    void onPreUpdate() override;
    void onUpdate() override;
    void onPostUpdate() override;

    void addControl(ControlPtr control);

private:
    IUIRenderer& mRenderer;
    IApplication& mApplication;
    std::vector<ControlPtr> mControls;
};

}