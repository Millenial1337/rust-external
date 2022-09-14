#ifndef QUARCCHECKBOX
#define QUARCCHECKBOX

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 
#include "../imgui/imgui_internal.h"

#include "imgui_tricks.hpp"

namespace Retake
{

	bool checkbox(const char* label, bool* v)
	{
		IM_USE;
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		const float square_sz = ImGui::GetFrameHeight();
		const ImVec2 pos = window->DC.CursorPos;
		const ImRect total_bb(pos, pos + ImVec2(square_sz + (style.ItemInnerSpacing.x + label_size.x + 0), 0 + label_size.y + style.FramePadding.y * 2));
		ItemSize(total_bb, style.FramePadding.y);
		ItemAdd(total_bb, id);

		bool hovered, held;
		bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);

		if (hovered || held)
			ImGui::SetMouseCursor(0);

		if (pressed)
			*v = !(*v);

		float lerpFloat = ImTricks::Animations::FastFloatLerp(label, *v, 0.f, 1.f, 0.05f);

		window->DrawList->AddRectFilled(total_bb.Min, total_bb.Min + ImVec2{ 12, 12 }, ImTricks::Animations::FastColorLerp(ImColor(55, 55, 56), ImColor(172, 142, 184), lerpFloat), 0, 0);
		window->DrawList->AddRect(total_bb.Min, total_bb.Min + ImVec2{ 12, 12 }, ImTricks::Animations::FastColorLerp(ImColor(20, 20, 20, 255), ImColor(20, 20, 20, 140), lerpFloat), 0, 0);

		RenderCheckMark(total_bb.Min + ImVec2{ 3, 3 }, ImTricks::Animations::FastColorLerp(ImColor(255, 255, 255, 0), ImColor(255, 255, 255, 255), lerpFloat), 6.f);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, 230 / 255.f));
		ImGui::RenderText(ImVec2(total_bb.Min.x + style.ItemInnerSpacing.x + 14, total_bb.Min.y - 1), label);
		ImGui::PopStyleColor();
		return pressed;
	}

}

#endif