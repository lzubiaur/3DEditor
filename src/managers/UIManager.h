#pragma once

#include <memory>
#include <vector>
#include <core/IApplication.h>
#include <editor/IControl.h>
#include <editor/IUIRenderer.h>
#include <managers/IManager.h>
#include <editor/MainWindow.h>

#include <boost/signals2.hpp>

namespace Engine
{

class UIManager : public IManager
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

    void notifyRequestCloseApp();
    void unsubscribeToRequestCloseApp(std::function<void()> callback);
    void subscribeToRequestCloseApp(std::function<void()> callback);

private:
    boost::signals2::signal<void ()> onRequestCloseApp;

    IUIRenderer& mRenderer;
    IApplication& mApplication;
    std::vector<ControlPtr> mControls;
};

}