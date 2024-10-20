#include <editor/IControl.h>
#include <services/IServiceLocator.h>
#include <editor/presenter/TestPresenter.h>
#include <editor/presenter/Bindings.h>

namespace Engine 
{

class MainWindow : public IControl
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