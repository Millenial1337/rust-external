/////////////////////////////////////////////////////
//                                                   
//    Generated with Retake Design. (ex. ImGui Editor) 
//    Retake Design is designed with love by pers0na2. 
//    All rights to Retake Design belong to pers0na2.  
//                                                   
/////////////////////////////////////////////////////


#ifndef QUARCBUTTON
#define QUARCBUTTON

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 
#include "../imgui/imgui_internal.h"

namespace Retake
{

	bool button(const char* label, const ImVec2& size_arg)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		if (hovered || held)
			ImGui::SetMouseCursor(0);


		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, 255 / 255.f));
		ImGui::RenderText(ImVec2(bb.Min.x + style.ItemInnerSpacing.x + 0, bb.Min.y + style.FramePadding.y + 0), label);
		ImGui::PopStyleColor();

		return pressed;
	}

	void SameLineCustom(float offset_from_start_x, float yaw)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGuiContext& g = *GImGui;
		if (offset_from_start_x != 0.0f)
		{

			window->DC.CursorPos.x = window->Pos.x - window->Scroll.x + offset_from_start_x + 2 + window->DC.GroupOffset.x + window->DC.ColumnsOffset.x;
			window->DC.CursorPos.y = window->DC.CursorPosPrevLine.y + yaw;
		}
		else
		{
			window->DC.CursorPos.x = window->DC.CursorPosPrevLine.x + 2;
			window->DC.CursorPos.y = window->DC.CursorPosPrevLine.y + yaw;
		}
	}

	void ColorPicker(const char* name, float color[4], bool alpha)
	{
		static float editing_color[4];

		editing_color[0] = color[0];
		editing_color[1] = color[1];
		editing_color[2] = color[2];
		editing_color[3] = color[3];

		ImGui::PushID(name);

		ImGui::TextColored({ 230 / 255.f, 230 / 255.f, 230 / 255.f, 230 / 255.f }, name);
		SameLineCustom(157, -2);
		bool openPopup = ImGui::ColorButton("##btn", ImVec4{ color[0], color[1], color[2], alpha ? color[3] : 1.0f }, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_AlphaPreview, { 15,15 });
		if (openPopup)
			ImGui::OpenPopup("##popup");
		ImGui::SetNextWindowSize({ alpha ? 225.f : 225.f,  alpha ? 185.f : 185.f });
		if (ImGui::BeginPopup("##popup", ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {

			ImGui::SetCursorPos({ 10, 10 });
			if (alpha) {
				if (ImGui::ColorPicker4("##picker", editing_color, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs))
				{
					color[0] = editing_color[0];
					color[1] = editing_color[1];
					color[2] = editing_color[2];
					color[3] = editing_color[3];
				}
			}
			else {
				if (ImGui::ColorPicker3("##picker", editing_color, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs))
				{
					color[0] = editing_color[0];
					color[1] = editing_color[1];
					color[2] = editing_color[2];
				}
			}

			ImGui::EndPopup();
		}
		ImGui::PopID();
	}
}

#endif