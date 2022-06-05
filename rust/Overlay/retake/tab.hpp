/////////////////////////////////////////////////////
//                                                   
//    Generated with Retake Design. (ex. ImGui Editor) 
//    Retake Design is designed with love by pers0na2. 
//    All rights to Retake Design belong to pers0na2.  
//                                                   
/////////////////////////////////////////////////////


#ifndef QUARCTAB
#define QUARCTAB

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 
#include "../imgui/imgui_internal.h"

#include "imgui_tricks.hpp"

namespace Retake
{

	bool tab(const char* label, bool selected)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize({ 72 + 0,26 + 0 }, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		if (hovered || held)
			ImGui::SetMouseCursor(0);

		int lerpAnim = ImTricks::Animations::FastIntLerp(label, selected, 0, 255, 20);

		window->DrawList->AddRectFilled(ImVec2(bb.Min.x, bb.Min.y), ImVec2(bb.Max.x - 70, bb.Max.y + 0), ImColor(180, 68, 124, lerpAnim), 6, 15);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4((165 + lerpAnim / 8) / 255.f, (165 + lerpAnim / 8) / 255.f, (165 + lerpAnim / 8) / 255.f, 255 / 255.f));
		ImGui::RenderText(ImVec2(bb.Min.x + 0 + (72 / 2 - label_size.x / 2), bb.Min.y + style.FramePadding.y + 2), label);
		ImGui::PopStyleColor();

		return pressed;
	}

}

#endif