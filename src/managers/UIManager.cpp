#include <algorithm>

#include <managers/UIManager.h>
#include <editor/NodeGraph.h>

namespace Engine
{

UIManager::UIManager()
{
}

void UIManager::onInitialize()
{
    addControl(std::make_unique<NodeGraph>());
}

void UIManager::onUpdate()
{
    std::for_each(mControls.begin(), mControls.end(), [](auto control) { control->onDraw(); });
}

void UIManager::onShutdown()
{
    std::for_each(mControls.begin(), mControls.end(), [](auto control) {
        // TODO
        // control->onShutDown();
    });
}

void UIManager::addControl(ControlPtr control)
{
    mControls.push_back(control);

    // TODO get pointer to the app and check is running
    // if (mRunning)
    {
        control->onInitialize();
    }
}

}