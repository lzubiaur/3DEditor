#include <editor/controls/ImGui/MainMenu.h>
#include <imgui.h>

namespace Engine
{

MainMenu::MainMenu(IServiceProvider& services)
: mServices(services)
{}

void MainMenu::onInitialize() 
{
}

void MainMenu::onDraw() 
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("Open", "Ctrl+O");
            ImGui::MenuItem("Save", "Ctrl+S");
            if (ImGui::MenuItem("Exit", "Alt+F4"))
            {
                mServices.getSignalService().getSignal<void()>("ui.onRequestAppClose")->emit();
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