#pragma once

#include <memory>
#include <vector>
#include <editor/IControl.h>
#include <editor/IUIRenderer.h>
#include <managers/IManager.h>

namespace Engine
{

class UIManager : public IManager
{
public:
    using ControlPtr = std::shared_ptr<IControl>;

    UIManager() = delete;
    UIManager(IUIRenderer& renderer);

    void onInitialize() override;
    void onShutdown() override;

    void onPreUpdate() override;
    void onUpdate() override;
    void onPostUpdate() override;

    void addControl(ControlPtr control);

private:
    IUIRenderer& mRenderer;
    std::vector<ControlPtr> mControls;
};
}