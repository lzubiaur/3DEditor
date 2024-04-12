#pragma once

#include <imgui.h>

namespace Engine
{

class AppLog
{
public:
    AppLog();

    void clear();
    void addLog(const char* fmt, ...) IM_FMTARGS(2);
    void draw(const char* title, bool* p_open = NULL);

private:
    ImGuiTextBuffer     m_buf;
    ImGuiTextFilter     m_filter;
    ImVector<int>       m_lineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool                m_autoScroll;  // Keep scrolling if already at the bottom.
};

}