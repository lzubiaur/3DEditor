#include <editor/controls/ImGui/UIRenderer.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <gsl/assert>

namespace Engine
{

UIRenderer::UIRenderer(IApplication& application)
: mApplication(application)
{
}

void UIRenderer::onInitialize()
{
    const auto platformData = mApplication.getPlatform().getPlatformData();
    
    Expects(platformData->getAPI() == GraphicsAPI::OpenGL);

    GLFWwindow* handle = static_cast<GLFWwindow*>(platformData->getWindowHandle());
    std::string version = platformData->getVersion();

    initializeImGui();

    Ensures(ImGui_ImplGlfw_InitForOpenGL(handle, true));
    Ensures(ImGui_ImplOpenGL3_Init(version.c_str()));
}

void UIRenderer::initializeImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();
}

void UIRenderer::onNewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UIRenderer::onRender()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIRenderer::onShutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

}
