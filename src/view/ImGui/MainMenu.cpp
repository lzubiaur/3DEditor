#include <view/ImGui/MainMenu.h>
#include <imgui.h>
#include <presenter/Command.h>

using namespace Forged::Presenter::Command;

namespace Forged::View
{

MainMenu::MainMenu(Presenter::IMainMenu& presenter)
: mPresenter(presenter)
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
        }

        ImGui::MenuItem("Save", "Ctrl+S");
        if (ImGui::MenuItem("Exit", "Alt+F4"))
        {
            mPresenter.getApplicationCommand().execute({ ApplicationCommandType::Close });
        }
        ImGui::EndMenu();
    }
}

void MainMenu::drawWindowsMenu()
{
    if (ImGui::BeginMenu("Windows"))
    {
        if (ImGui::MenuItem("Messages Console"))
        {
            mPresenter.getPanelCommand().execute({ PanelCommandType::TogglePanel, "MessageConsole"});
        }
        ImGui::Separator();

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