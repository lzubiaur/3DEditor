#include <algorithm>

#include <implot.h>

#include <managers/UIManager.h>
#include <editor/NodeGraph.h>

namespace Engine
{

UIManager::UIManager(IUIRenderer& renderer)
: mRenderer(renderer)
{}

void UIManager::onInitialize()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImPlot::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    mRenderer.initialize();

    addControl(std::make_unique<NodeGraph>());
}

void UIManager::onPreUpdate()
{
    mRenderer.newFrame();
}

void UIManager::onUpdate()
{
    ImGui::NewFrame();
    std::for_each(mControls.begin(), mControls.end(), [](auto control) { control->onDraw(); });
    ImGui::Render();
}

void UIManager::onPostUpdate()
{
    mRenderer.render();
}

void UIManager::onShutdown()
{
    std::for_each(mControls.begin(), mControls.end(), [](auto control) {
        // TODO
        // control->onShutDown();
    });

    mRenderer.shutdown();
    ImGui::DestroyContext();
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