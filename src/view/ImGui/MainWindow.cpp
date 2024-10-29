#include <view/ImGui/MainWindow.h>
#include <view/ImGui/Widgets.h>

#include <imgui.h>

namespace Forged::View
{

MainWindow::MainWindow(IServiceLocator& services, Presenter::IMainWindow& presenter)
: mPresenter(presenter)
{

}

MainWindow::~MainWindow()
{

}

void MainWindow::onInitialize()
{
}

void MainWindow::onShutdown() 
{
}

void MainWindow::onDraw()
{
    if (!ImGui::Begin("MainWindow"))
    {
        ImGui::End();
        return;
    }

    ImGui::End();
}

}