#include <editor/UIRenderer.h>

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

void UIRenderer::initialize()
{
    const auto platformData = mApplication.getPlatform().getPlatformData();
    
    Expects(platformData->getAPI() != GraphicsAPI::OpenGL);

    GLFWwindow* handle = static_cast<GLFWwindow*>(platformData->getWindowHandle());
    std::string version = platformData->getVersion();

    ImGui_ImplGlfw_InitForOpenGL(handle, true);
    ImGui_ImplOpenGL3_Init(version.c_str());
}

void UIRenderer::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
}

void UIRenderer::newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
}

void UIRenderer::render()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}
