#pragma once

#include <view/IUIControl.h>
#include <services/IServiceLocator.h>
#include <imgui.h>

// Stolen from ImGui demo

namespace Forged::View
{

class MessageConsole : public IUIControl
{
public:
    MessageConsole(IServiceLocator& services);

    ControlType getType() override { return ControlType::MessageConsole; }
    std::string getName() override { return "MessageConsole"; }

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

    void clear();
    void addLog(const char* fmt, ...) IM_FMTARGS(2);
    void draw(const char* title, bool* p_open = NULL);

    bool isVisible() override { return mOpen; }
    void show() override { mOpen = true; }
    void hide() override { mOpen = false; }

private:
    bool mOpen;
    ImGuiTextBuffer mBuf;
    ImGuiTextFilter mFilter;
    ImVector<int> mLineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool mAutoScroll;  // Keep scrolling if already at the bottom.
    IServiceLocator& mServices;
};

}