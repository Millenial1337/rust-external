#pragma once
#include "imgui/imgui.h"
#include <string>
#include "color.hpp"

namespace ESP
{
	void __fastcall Run();
}

namespace Overlay
{
	void __fastcall Loop();
	void __fastcall start(HWND hwnd);
	void Style(ImGuiStyle& style);
	inline ImFont* fontTitle;
	inline ImFont* fontMenu;
	inline ImFont* playerName;
	inline ImFont* weaponName;
	inline ImFont* menuIcon;
}

namespace Render
{
	void __fastcall Line(ImVec2 pos, ImVec2 size, ImU32 color, float thickness);
	void __fastcall Line2(const ImVec2& Start, const ImVec2& End, const ImColor color, float Thickk);
	void __fastcall DrawLootBox(const ImVec2& Start, const ImVec2& Sz, const ImColor color, float Thick);
	void __fastcall DrawBox(ImVec2 pos, ImVec2 size, ImColor color);
	void __fastcall DrawFilledBox(ImVec2 pos, ImVec2 size, ImColor color);
	void __fastcall DrawFilledRect(float x, float y, float w, float h, ImVec4 color);
	void __fastcall DrawHealthbarVertical(float x, float y, float w, float h, float value, float max);
	void __fastcall DrawCornerBox(ImVec2 pos, ImVec2 size, ImColor color);
	void __fastcall Text(ImVec2 pos, std::string strText, ImColor color, bool outline, ImFont* font, float fontSize = 0.f);
	void __fastcall Circle(ImVec2 point, float radius, ImColor color);
	void __fastcall DrawHealthBar(ImVec2 pos, ImVec2 size, ImColor color);
	void __fastcall DrawString(int x, int y, const char* str, Color* color);
	ImU32 __fastcall FtIM(float* a_value);
}