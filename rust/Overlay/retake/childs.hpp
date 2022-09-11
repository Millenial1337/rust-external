/////////////////////////////////////////////////////
//                                                   
//    Generated with Retake Design. (ex. ImGui Editor) 
//    Retake Design is designed with love by pers0na2. 
//    All rights to Retake Design belong to pers0na2.  
//                                                   
/////////////////////////////////////////////////////


#ifndef QUARCHILD
#define QUARCHILD

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 
#include "../imgui/imgui_internal.h"

namespace Retake
{

	bool BeginChildEx(const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags)
	{
		ImGuiContext& g = *GImGui;
		ImGuiWindow* parent_window = g.CurrentWindow;

		flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;
		flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);

		const ImVec2 content_avail = ImGui::GetContentRegionAvail();
		ImVec2 size = ImFloor(size_arg);
		const int auto_fit_axises = ((size.x == 0.0f) ? (1 << ImGuiAxis_X) : 0x00) | ((size.y == 0.0f) ? (1 << ImGuiAxis_Y) : 0x00);
		if (size.x <= 0.0f)
			size.x = ImMax(content_avail.x + size.x, 4.0f);
		if (size.y <= 0.0f)
			size.y = ImMax(content_avail.y + size.y, 4.0f);
		ImGui::SetNextWindowSize(size);

		char title[256];
		if (name)
			ImFormatString(title, IM_ARRAYSIZE(title), "%s/%s_%08X", parent_window->Name, name, id);
		else
			ImFormatString(title, IM_ARRAYSIZE(title), "%s/%08X", parent_window->Name, id);

		const float backup_border_size = g.Style.ChildBorderSize;
		if (!border)
			g.Style.ChildBorderSize = 0.0f;
		bool ret = ImGui::Begin(title, NULL, flags);
		g.Style.ChildBorderSize = backup_border_size;

		ImGuiWindow* child_window = g.CurrentWindow;
		child_window->ChildId = id;
		child_window->AutoFitChildAxises = (ImS8)auto_fit_axises;

		if (child_window->BeginCount == 1)
			parent_window->DC.CursorPos = child_window->Pos;

		if (g.NavActivateId == id && !(flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayerActiveMask != 0 || child_window->DC.NavHasScroll))
		{
			ImGui::FocusWindow(child_window);
			ImGui::NavInitWindow(child_window, false);
			ImGui::SetActiveID(id + 1, child_window);
			g.ActiveIdSource = ImGuiInputSource_Nav;
		}
		ImVec2 pos = ImGui::GetWindowPos();

		parent_window->DrawList->AddRectFilled(ImVec2(pos - 2), ImVec2(pos + size_arg), ImColor(43, 33, 47, 255), 6, 15);
		parent_window->DrawList->AddText(ImVec2(pos.x + 8, pos.y + 1), ImColor(91, 95, 130, 255), name);
		parent_window->DrawList->AddLine(ImVec2(pos.x, pos.y + 17), ImVec2(pos.x + size_arg.x, pos.y + 17), ImColor(35, 27, 38, 255));
		ImGui::SetCursorPosY(23);
		//parent_window->DrawList->AddRect(ImVec2(ImGui::GetWindowPos().x + 0, ImGui::GetWindowPos().y + 0), ImVec2(ImGui::GetWindowPos().x + size_arg.x + 0, ImGui::GetWindowPos().y + size_arg.y + 0), ImColor(0, 0, 0, 255), 0, 15, 1.000000);
		//parent_window->DrawList->AddRect(ImVec2(ImGui::GetWindowPos().x + 1, ImGui::GetWindowPos().y + 1), ImVec2(ImGui::GetWindowPos().x + size_arg.x + -1, ImGui::GetWindowPos().y + size_arg.y + -1), ImColor(255, 255, 255, 18), 0, 15, 1.000000);
		return ret;
	}

	bool BeginChild(const char* str_id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		return BeginChildEx(str_id, window->GetID(str_id), size_arg, border, extra_flags);
	}


	void RetakeBeginChild(const char* str_id, const ImVec2& size_arg)
	{

		BeginChild(str_id, size_arg, false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(ImGui::GetWindowPos().x + 2, ImGui::GetWindowPos().y + 2),
			ImVec2(ImGui::GetWindowPos().x + size_arg.x - 2, ImGui::GetWindowPos().y + 25), ImColor(43, 33, 47, 255), 0, 6);

		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x + 2, ImGui::GetWindowPos().y + 2),
			ImVec2(ImGui::GetWindowPos().x + 64, ImGui::GetWindowPos().y + 25), ImColor(180, 68, 124, 105), ImColor(30, 30, 35, 0), ImColor(30, 30, 35, 0), ImColor(180, 68, 124, 105));

		ImGui::GetWindowDrawList()->AddLine(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y - 40), ImVec2(ImGui::GetWindowPos().x + size_arg.x, ImGui::GetWindowPos().y + 40), ImColor(35, 27, 38, 255));

		ImGui::GetWindowDrawList()->AddText(ImGui::GetWindowPos() + ImVec2(10, 6), ImColor(255, 255, 255), str_id);

		ImGui::SetCursorPos({ 24, 40 });
		ImGui::BeginChild(std::string(str_id).append("123").c_str(), size_arg - ImVec2(48, 50));
	}

	void RetakeEndChild()
	{
		ImGui::EndChild();
		ImGui::EndChild();
	}
}

#endif