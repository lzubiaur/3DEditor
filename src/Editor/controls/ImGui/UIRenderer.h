#pragma once
#include <core/IApplication.h>
#include <editor/IUIRenderer.h>

namespace Engine
{

class UIRenderer : public IUIRenderer
{
public:

    // TODO decouple from Application class
    UIRenderer::UIRenderer(IApplication& application);
    ~UIRenderer() = default;

    void initialize() override;
    void shutdown() override;

    void newFrame() override;
    void render() override;

private:
    void initializeImGui();

private:
    IApplication& mApplication;
};

}