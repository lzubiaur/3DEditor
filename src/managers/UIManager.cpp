#include <algorithm>

#include <implot.h>

#include <managers/UIManager.h>
#include <editor/NodeGraph.h>
#include <editor/MainMenu.h>

namespace Engine
{

UIManager::UIManager(IApplication& application, IUIRenderer& renderer)
: mApplication(application)
, mRenderer(renderer)
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

    // TODO move to plot class
    // ImPlot::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    mRenderer.initialize();

    // TODO use factory or other pattern to create and load the controls
    addControl(std::make_shared<NodeGraph>());
    addControl(std::make_shared<MainMenu>(*this));

    std::for_each(mControls.begin(), mControls.end(), [](auto control) { control->onInitialize(); });
}

void UIManager::onPreUpdate()
{
    mRenderer.newFrame();
    ImGui::NewFrame();
}

void UIManager::onUpdate()
{
    std::for_each(mControls.begin(), mControls.end(), [](auto control) { control->onDraw(); });
}

void UIManager::onPostUpdate()
{
    ImGui::Render();
    mRenderer.render();
}

void UIManager::onShutdown()
{
    onRequestCloseApp.disconnect_all_slots();

    // TODO
    // std::for_each(mControls.begin(), mControls.end(), [](auto control) { control->onShutDown(); });

    mRenderer.shutdown();
    ImGui::DestroyContext();
}

void UIManager::addControl(ControlPtr control)
{
    mControls.push_back(control);

    if (mApplication.isRunning())
    {
        control->onInitialize();
    }
}

void UIManager::notifyRequestCloseApp()
{
    onRequestCloseApp();
    mApplication.requestClose();
}

void UIManager::unsubscribeToRequestCloseApp(std::function<void()> callback)
{
    // onRequestCloseApp.disconnect(callback);
}

void UIManager::subscribeToRequestCloseApp(std::function<void()> callback)
{
    onRequestCloseApp.connect(callback);
}

}