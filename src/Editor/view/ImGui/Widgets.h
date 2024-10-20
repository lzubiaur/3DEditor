#pragma once

#include <editor/presenter/Bindings.h>

#include <imgui.h>

namespace Engine::View::Widget
{

inline bool InputText(const char* label, Presenter::StringBinding& binding)
{
    if (ImGui::InputText(label, binding.getBuffer(), binding.getBufferCapacity()))
    {
        binding.notifyChanges();

        return true;
    }

    return false;
}

}