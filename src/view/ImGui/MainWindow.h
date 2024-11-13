#include <presenter/MainWindow.h>
#include <view/UserControl.h>
#include <services/IServiceLocator.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <ImGuizmo.h>

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
    void TransformStart(float* cameraView, float* cameraProjection, float* matrix);
    void EditTransform(float* cameraView, float* cameraProjection, float* matrix);
    void TransformEnd();

private:
    Presenter::IMainWindow& mPresenter;
    
       // Camera projection
   bool isPerspective = true;
   float fov = 27.f;
   float viewWidth = 10.f; // for orthographic
   float camYAngle = 165.f / 180.f * 3.14159f;
   float camXAngle = 32.f / 180.f * 3.14159f;

   bool firstFrame = true;

   bool useSnap = false;
   float snap[3] = {1.f, 1.f, 1.f};
   int lastUsing = 0;
   ImGuizmo::OPERATION mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
   ImGuizmo::MODE mCurrentGizmoMode = ImGuizmo::WORLD;

   float cameraView[16] = {
       1.f, 0.f, 0.f, 0.f,
       0.f, 1.f, 0.f, 0.f,
       0.f, 0.f, 1.f, 0.f,
       0.f, 0.f, 0.f, 1.f};

   float cameraProjection[16];

   const float identityMatrix[16] = {
       1.f, 0.f, 0.f, 0.f,
       0.f, 1.f, 0.f, 0.f,
       0.f, 0.f, 1.f, 0.f,
       0.f, 0.f, 0.f, 1.f};

   float objectMatrix[4][16] = {
       {1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f},

       {1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        2.f, 0.f, 0.f, 1.f},

       {1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        2.f, 0.f, 2.f, 1.f},

       {1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 2.f, 1.f}};

   int gizmoCount = 1;
   float camDistance = 8.f;
};

}