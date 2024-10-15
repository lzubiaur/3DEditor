#pragma once
#include <core/IApplication.h>
#include <editor/IUIRenderer.h>

namespace Engine
{

class UIRenderer : public IUIRenderer
{
public:
    UIRenderer::UIRenderer(IApplication& application);
    ~UIRenderer() = default;

    void initialize() override;
    void shutdown() override;

    void newFrame() override;
    void render() override;

private:
    IApplication& mApplication;
};

}