#include <presenter/MainWindow.h>
#include <view/UserControl.h>
#include <services/IServiceLocator.h>

namespace Forged::View
{

class MainWindow : public UserControl
{
public:
    // TODO remove services. Should use the presenter only
    MainWindow(IServiceLocator& services, Presenter::IMainWindow& presenter);
    ~MainWindow();

    ControlHash getHash() override { return ControlHashes::MainWindowHash; }
    ControlType getType() override { return ControlType::Panel; }
    std::string getName() override { return ControlName::MainWindow; }

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

private:
    Presenter::IMainWindow& mPresenter;
};

}