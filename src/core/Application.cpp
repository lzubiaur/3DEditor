#include <core/Application.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>

#include <iostream>
#include <utility>
#include <memory>

#include <core/Common.h>

namespace Engine
{

Application::Application(PlatformPtr platform, std::vector<ManagerPtr>& managers)
: mPlatform(std::move(platform))
, mManagers(std::move(managers))
{
}

void Application::run()
{
    if (!initialize())
    {
        return;
    }

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    mRunning = true;

    while (!glfwWindowShouldClose(mPlatform->getHandle()))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        updateManagers();

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(mPlatform->getHandle(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mPlatform->getHandle());
    }

    mRunning = false;

    shutdown();
}

bool Application::initialize()
{
    if (!mPlatform->initialize())
    {
        return false;
    }

    initializeManagers();

    return initializeUI() && initializeScript();
}

bool Application::initializeScript()
{
    // TODO initialize managers
    // mScript.initialize();
    // mScript.run("scripts/main.nut");

    return true;
}

bool Application::initializeUI()
{
    bool succeeded = true;

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

    succeeded &= ImGui_ImplGlfw_InitForOpenGL(mPlatform->getHandle(), true);
    succeeded &= ImGui_ImplOpenGL3_Init(mPlatform->getGLSLVersion());

    // TODO initialize managers

    return succeeded;
}

void Application::shutdown()
{
    shutDownUI();
    shutDownScript();

    // TODO Move to Platform class
    glfwDestroyWindow(mPlatform->getHandle());
    glfwTerminate();

    shutdownManagers();

    spdlog::shutdown();
}

void Application::shutDownScript()
{
    // mScript.shutdown();
}

void Application::shutDownUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Application::initializeManagers()
{
    std::for_each(mManagers.begin(), mManagers.end(), [](const auto& manager) { manager->onInitialize(); });
}

void Application::updateManagers()
{
    std::for_each(mManagers.begin(), mManagers.end(), [](const ManagerPtr& manager) { manager->onUpdate(); });
}

void Application::shutdownManagers()
{
    std::for_each(mManagers.begin(), mManagers.end(), [](const auto& manager) { manager->onShutdown(); });
}

}
