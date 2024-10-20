#include <editor/view/ImGui/MainWindow.h>
#include <editor/view/ImGui/Widgets.h>

#include <imgui.h>

namespace Engine 
{

MainWindow::MainWindow(IServiceLocator& services, Presenter::IMainWindow& presenter)
: mPresenter(presenter)
, mTestBinding(mPresenter.getName())
{

}

MainWindow::~MainWindow()
{

}

void MainWindow::onInitialize()
{
    mTestBinding.bind();
}

void MainWindow::onShutdown() 
{
    mTestBinding.unbind();
}

void MainWindow::onDraw()
{
    if (!ImGui::Begin("Test properties"))
    {
        ImGui::End();
        return;
    }

    if (View::Widget::InputText("Test", mTestBinding))
    {
        // TODO do other stuff if the text changed....
    }

    ImGui::End();
}

}