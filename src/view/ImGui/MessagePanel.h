#pragma once

#include <view/UserControl.h>
#include <services/IServiceLocator.h>
#include <presenter/MessagePanel.h>
#include <imgui.h>

// Stolen from ImGui demo

namespace Forged::View
{

class MessagePanel : public UserControl
{
public:
    // TODO remove services. Should use the presenter only
    MessagePanel(IServiceLocator& services, Presenter::IMessagePanel& presenter);

    ControlHash getHash() override { return ControlHashes::MessagePanelHash; }
    ControlType getType() override { return ControlType::Panel; }
    std::string getName() override { return ControlName::MessagePanel; }

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

    void clear();
    void addLog(const char* fmt, ...) IM_FMTARGS(2);
    void draw(const char* title, bool* p_open = NULL);

private:
    ImGuiTextBuffer mBuf;
    ImGuiTextFilter mFilter;
    ImVector<int> mLineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool mAutoScroll;  // Keep scrolling if already at the bottom.
    IServiceLocator& mServices;
    Presenter::IMessagePanel &mPresenter;
};

}