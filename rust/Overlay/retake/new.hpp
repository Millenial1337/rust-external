#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../Overlay.hpp"

namespace GUI
{
    bool News(const char* label, const char* text)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = ImGui::CalcItemSize(ImVec2{ 376, ImGui::CalcTextSize(label).y + ImGui::CalcTextSize(text).y + 31 }, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
        const ImRect bb(pos, { pos.x + size.x , pos.y + size.y });

        ImGui::ItemSize(size, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

        ImGui::RenderFrame(bb.Min, bb.Max, ImColor(60, 60, 60), true, 2);
        window->DrawList->AddRect(bb.Min, bb.Max, ImColor(193.f / 255.f, 193.f / 255.f, 193.f / 255.f, 75.f / 255.f), 2); //193.f / 255.f, 193.f / 255.f, 193.f / 255.f, 75.f / 255.f), 2

        window->DrawList->AddText({ bb.Min.x + 10,bb.Min.y + 10 }, ImColor(240 / 255.f, 240 / 255.f, 240 / 255.f, 200 / 255.f), label);

        window->DrawList->AddText({ bb.Min.x + 10,bb.Min.y + 20 + ImGui::CalcTextSize(label).y }, ImColor(240 / 255.f, 240 / 255.f, 240 / 255.f, 200 / 255.f), text);

        return pressed;
    }
}