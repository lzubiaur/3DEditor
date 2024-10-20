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

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

private:
    Presenter::IMainWindow& mPresenter;
    Presenter::StringBinding mTestBinding;
};

}