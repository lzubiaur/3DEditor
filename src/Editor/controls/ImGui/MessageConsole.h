#pragma once

#include <editor/IControl.h>
#include <services/IServiceLocator.h>
#include <imgui.h>

// Stolen from ImGui demo

namespace Engine
{

class MessageConsole : public IControl
{
public:
    MessageConsole(IServiceLocator& services);

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

    void clear();
    void addLog(const char* fmt, ...) IM_FMTARGS(2);
    void draw(const char* title, bool* p_open = NULL);

private:
    bool mOpen;
    ImGuiTextBuffer mBuf;
    ImGuiTextFilter mFilter;
    ImVector<int> mLineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool mAutoScroll;  // Keep scrolling if already at the bottom.
    IServiceLocator& mServices;
};

}