#include <view/IUIControl.h>
#include <services/IServiceLocator.h>
#include <presenter/TestPresenter.h>
#include <presenter/Bindings.h>

namespace Forged::View
{

class MainWindow : public IUIControl
{
public:
    MainWindow(IServiceLocator& services, Presenter::IMainWindow& presenter);
    ~MainWindow();

    ControlType getType() override { return ControlType::MainWindow; }
    std::string getName() override { return "MainWindow"; }

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

    bool isVisible() override { return true; }
    void show() override {}
    void hide() override {}

private:
    Presenter::IMainWindow& mPresenter;
    Presenter::StringBinding mTestBinding;
};

}