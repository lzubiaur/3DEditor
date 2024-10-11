#include <imgui.h>
#include <Editor/IUIControl.h>

namespace Engine 
{

class MainWindow : public IUIControl
{
public:
    MainWindow();
    ~MainWindow();

    virtual bool onInitialize() = 0;
    virtual void onDraw() = 0;

private:
};

}