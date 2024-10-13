#pragma once

#include <memory>
#include <vector>
#include <editor/IControl.h>
#include <managers/IManager.h>

namespace Engine
{

class UIManager : public IManager
{
public:
    using ControlPtr = std::shared_ptr<IControl>;

    UIManager();
    ~UIManager() = default;

    void onInitialize() override;
    void onUpdate() override;
    void onShutdown() override;

    void addControl(ControlPtr control);

private:
  std::vector<ControlPtr> mControls;
};
}