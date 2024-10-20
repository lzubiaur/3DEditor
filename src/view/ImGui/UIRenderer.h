#pragma once
#include <core/IApplication.h>
#include <view/IUIRenderer.h>

namespace Forged::View
{

class UIRenderer : public IUIRenderer
{
public:

    // TODO decouple from Application class
    UIRenderer::UIRenderer(IApplication& application);
    ~UIRenderer() = default;

    void onInitialize() override;
    void onShutdown() override;

    void onNewFrame() override;
    void onRender() override;

private:
    void initializeImGui();

private:
    IApplication& mApplication;
};

}