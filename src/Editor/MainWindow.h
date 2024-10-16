#include <imgui.h>
#include <editor/IControl.h>

namespace Engine 
{

class MainWindow : public IControl
{
public:
    MainWindow();
    ~MainWindow();

    void onInitialize() override;
    void onDraw() override;
};

}