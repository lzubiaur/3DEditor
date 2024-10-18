#include <editor/controls/ImGui/MainMenu.h>
#include <editor/UIEvents.h>
#include <imgui.h>

namespace Engine
{

MainMenu::MainMenu(IServiceLocator& services)
: mServices(services)
{}

void MainMenu::onInitialize() 
{
}

void MainMenu::onShutdown() 
{
}

void MainMenu::onDraw() 
{
    auto signals = mServices.getSignalService();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("Open", "Ctrl+O");
            ImGui::MenuItem("Save", "Ctrl+S");
            if (ImGui::MenuItem("Exit", "Alt+F4"))
            {
                signals.getSignal<void()>(UIEvents::OnRequestAppClose)->emit();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::MenuItem("Undo", "Ctrl+Z");
            ImGui::MenuItem("Redo", "Ctrl+Y");
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About");
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

}