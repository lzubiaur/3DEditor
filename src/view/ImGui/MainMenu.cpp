#include <view/ImGui/MainMenu.h>
#include <imgui.h>

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
            mPresenter.closeApplication();
        }
        ImGui::EndMenu();
    }
}

void MainMenu::drawWindowsMenu()
{
    if (ImGui::BeginMenu("Windows"))
    {
        if (ImGui::MenuItem("Messages Console", nullptr, mPresenter.isMessagePanelVisible()))
        {
            mPresenter.setIsMessagePanelVisible(false);
        }
        ImGui::Separator();

        if (ImGui::MenuItem("ImGui Demo", nullptr, mPresenter.isDemoPanelVisible()))
        {
            mPresenter.setIsDemoPanelVisible(false);
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