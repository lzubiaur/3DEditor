#include <view/ImGui/MainMenu.h>
#include <view/UIEvents.h>
#include <imgui.h>

namespace Forged::View
{

MainMenu::MainMenu(IServiceLocator& services)
: mServices(services)
, mSignals(services.getSignalService())
, mReact(services.getReactiveService())
{}

void MainMenu::onInitialize() 
{
}

void MainMenu::onShutdown() 
{
}

void MainMenu::onDraw() 
{
    if (ImGui::BeginMainMenuBar())
    {
        drawFileMenu();
        drawWindowsMenu();
        drawHelpMenu();
        ImGui::EndMainMenuBar();
    }
}

void MainMenu::drawFileMenu()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Open", "Ctrl+O"))
        {
            mServices.getEventBus().emitEvent(Events::TraceMessageEvent{Events::LogLevel::Error, "Hello React!"});
        }

        ImGui::MenuItem("Save", "Ctrl+S");
        if (ImGui::MenuItem("Exit", "Alt+F4"))
        {
            mSignals.getSignal<void()>(View::UIEvents::OnRequestAppClose)->emit();
        }
        ImGui::EndMenu();
    }
}

void MainMenu::drawWindowsMenu()
{
    if (ImGui::BeginMenu("Windows"))
    {
        if (ImGui::MenuItem("Messages"))
        {
        }
        if (ImGui::MenuItem("ImGui Demo"))
        {
        }
        if (ImGui::MenuItem("ImPlot Demo"))
        {
        }
        ImGui::EndMenu();
    }
}

void MainMenu::drawHelpMenu()
{
    if (ImGui::BeginMenu("Help"))
    {
        ImGui::MenuItem("About");
        ImGui::EndMenu();
    }
}

}