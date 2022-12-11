#ifndef QUARCSLIDER
#define QUARCSLIDER

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 
#include <map>

#include "../imgui/imgui_internal.h"
#include <sstream>

namespace Retake
{

	static const char* PatchFormatStringFloatToInt(const char* fmt)
	{
		if (fmt[0] == '%' && fmt[1] == '.' && fmt[2] == '0' && fmt[3] == 'f' && fmt[4] == 0)
			return "%d";

		const char* fmt_start = ImParseFormatFindStart(fmt);
		const char* fmt_end = ImParseFormatFindEnd(fmt_start);
		if (fmt_end > fmt_start && fmt_end[-1] == 'f')
		{
			if (fmt_start == fmt && fmt_end[0] == 0)
				return "%d";
			ImGuiContext& g = *GImGui;
			ImFormatString(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer), "%.*s%%d%s", (int)(fmt_start - fmt), fmt, fmt_end);
			return g.TempBuffer;
		}
		return fmt;
	}

	static inline int DataTypeFormatString(char* buf, int buf_size, ImGuiDataType data_type, const void* data_ptr, const char* format)
	{
		// Signedness doesn't matter when pushing integer arguments
		if (data_type == ImGuiDataType_S32 || data_type == ImGuiDataType_U32)
			return ImFormatString(buf, buf_size, format, *(const ImU32*)data_ptr);
		if (data_type == ImGuiDataType_S64 || data_type == ImGuiDataType_U64)
			return ImFormatString(buf, buf_size, format, *(const ImU64*)data_ptr);
		if (data_type == ImGuiDataType_Float)
			return ImFormatString(buf, buf_size, format, *(const float*)data_ptr);
		if (data_type == ImGuiDataType_Double)
			return ImFormatString(buf, buf_size, format, *(const double*)data_ptr);
		if (data_type == ImGuiDataType_S8)
			return ImFormatString(buf, buf_size, format, *(const ImS8*)data_ptr);
		if (data_type == ImGuiDataType_U8)
			return ImFormatString(buf, buf_size, format, *(const ImU8*)data_ptr);
		if (data_type == ImGuiDataType_S16)
			return ImFormatString(buf, buf_size, format, *(const ImS16*)data_ptr);
		if (data_type == ImGuiDataType_U16)
			return ImFormatString(buf, buf_size, format, *(const ImU16*)data_ptr);
		IM_ASSERT(0);
		return 0;
	}

	struct ImGuiDataTypeInfo
	{
		size_t      Size;
		const char* PrintFmt;   // Unused
		const char* ScanFmt;
	};

	static const ImGuiDataTypeInfo GDataTypeInfo[] =
	{
		{ sizeof(char),             "%d",   "%d"    },  // ImGuiDataType_S8
		{ sizeof(unsigned char),    "%u",   "%u"    },
		{ sizeof(short),            "%d",   "%d"    },  // ImGuiDataType_S16
		{ sizeof(unsigned short),   "%u",   "%u"    },
		{ sizeof(int),              "%d",   "%d"    },  // ImGuiDataType_S32
		{ sizeof(unsigned int),     "%u",   "%u"    },
	#ifdef _MSC_VER
		{ sizeof(ImS64),            "%I64d","%I64d" },  // ImGuiDataType_S64
		{ sizeof(ImU64),            "%I64u","%I64u" },
	#else
		{ sizeof(ImS64),            "%lld", "%lld"  },  // ImGuiDataType_S64
		{ sizeof(ImU64),            "%llu", "%llu"  },
	#endif
		{ sizeof(float),            "%f",   "%f"    },  // ImGuiDataType_Float (float are promoted to double in va_arg)
		{ sizeof(double),           "%f",   "%lf"   },  // ImGuiDataType_Double
	};
	IM_STATIC_ASSERT(IM_ARRAYSIZE(GDataTypeInfo) == ImGuiDataType_COUNT);

	bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const float w = ImGui::GetWindowWidth() - 0.1f;

		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		const ImRect frame_bb(window->DC.CursorPos + ImVec2(0, 10), window->DC.CursorPos + ImVec2(w, 19));
		const ImRect total_bb(frame_bb.Min - ImVec2(0, 6), frame_bb.Max + ImVec2(0, 5));

		ImGui::ItemSize(total_bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(total_bb, id, &frame_bb))
			return false;

		// Default format string when passing NULL
		// Patch old "%.0f" format string to use "%d", read function comments for more details.
		IM_ASSERT(data_type >= 0 && data_type < ImGuiDataType_COUNT);
		if (format == NULL)
			format = GDataTypeInfo[data_type].PrintFmt;
		else if (data_type == ImGuiDataType_S32 && strcmp(format, "%d") != 0)
			format = PatchFormatStringFloatToInt(format);

		// Tabbing or CTRL-clicking on Slider turns it into an input box
		bool start_text_input = false;
		const bool focus_requested = ImGui::FocusableItemRegister(window, id);
		const bool hovered = ImGui::ItemHoverable(frame_bb, id);
		if (focus_requested || (hovered && g.IO.MouseClicked[0]) || g.NavActivateId == id || (g.NavInputId == id && g.TempInputId != id))
		{
			ImGui::SetActiveID(id, window);
			ImGui::SetFocusID(id, window);
			ImGui::FocusWindow(window);
			g.ActiveIdUsingNavDirMask = (1 << ImGuiDir_Up) | (1 << ImGuiDir_Down);
			if (focus_requested || g.IO.KeyCtrl || g.NavInputId == id)
			{
				start_text_input = true;
				g.TempInputId = 0;
			}
		}

		ImRect grab_bb;
		const bool value_changed = ImGui::SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, 1, ImGuiSliderFlags_None, &grab_bb);

		window->DrawList->AddRectFilled(frame_bb.Min, frame_bb.Max - ImVec2(0, 2), ImColor(40, 40, 46), 6);

		window->DrawList->AddRectFilled(ImVec2(frame_bb.Min.x + 1, frame_bb.Min.y + 1), ImVec2(grab_bb.Max.x + 1, grab_bb.Max.y + 1 - 2), ImColor(97, 79, 104, 255), 6);

		char value_buf[64];
		const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

		float grab_w = grab_bb.Max.x - grab_bb.Min.x;
		auto const moved_pos_of_prev_rect = 1;
		auto const preview_w = ImGui::CalcTextSize((std::stringstream{ } << value_buf).str().c_str()).y;
		//ImVec2 text_pos = ImVec2(frame_bb.Max.x - 16, frame_bb.Min.y - 16);

		//ImGui::GetOverlayDrawList()->AddText(text_pos - preview_w / 2, ImColor(229 / 255.f, 229 / 255.f, 229 / 255.f, 230 / 255.f), value_buf);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(frame_bb.Min.x + ImGui::GetWindowSize().x - ImGui::CalcTextSize(value_buf).x, window->DC.CursorPos.y - 28), ImColor(229 / 255.f, 229 / 255.f, 229 / 255.f, 230 / 255.f), value_buf);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, 230 / 255.f));
		ImGui::RenderText(ImVec2(frame_bb.Min.x, frame_bb.Min.y - 16), label);
		ImGui::PopStyleColor();

		return value_changed;
	}

    //bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, float power)
    //{
    //    ImGuiWindow* window = ImGui::GetCurrentWindow();
    //    if (window->SkipItems)
    //        return false;

    //    if (window->DC.CurrLineTextBaseOffset != window->DC.PrevLineTextBaseOffset)
	   //     ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 1 * 8.f);

    //    ImGui::SetCursorPosX(ImGui::GetCursorPosX() +1 * 3.f);

    //    ImGuiContext& g = *GImGui;
    //    const ImGuiStyle& style = g.Style;
    //    const ImGuiID id = window->GetID(label);
    //    //const float w = ImGui::CalcItemWidth();
    //    const float w = ImGui::GetWindowWidth() - 2;

    //    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    //    const ImRect frame_bb(window->DC.CursorPos + ImVec2(0, 11 ), window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y * 2.0f * 0.5f));
    //    const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(style.ItemInnerSpacing.x + label_size.x , 0));

    //    ImGui::ItemSize(ImRect(total_bb.Min - ImVec2(0, 22 ), total_bb.Max), style.FramePadding.y);
    //    if (!ImGui::ItemAdd(ImRect(total_bb.Min - ImVec2(0, 22 ), total_bb.Max), id, &frame_bb))
    //        return false;

    //    // Default format string when passing NULL
    //    if (format == NULL)
    //        format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;
    //    else if (data_type == ImGuiDataType_S32 && strcmp(format, "%d") != 0) // (FIXME-LEGACY: Patch old "%.0f" format string to use "%d", read function more details.)
    //        format = PatchFormatStringFloatToInt(format);

    //    // Tabbing or CTRL-clicking on Slider turns it into an input box

    //    const bool hovered = ImGui::ItemHoverable(frame_bb, id);
    //    bool temp_input_is_active = ImGui::TempInputIsActive(id);
    //    bool temp_input_start = false;
    //    if (!temp_input_is_active)
    //    {
    //        const bool focus_requested = ImGui::FocusableItemRegister(window, id);
    //        const bool clicked = (hovered && g.IO.MouseClicked[0]);
    //        if (focus_requested || clicked || g.NavActivateId == id || g.NavInputId == id)
    //        {
	   //         ImGui::SetActiveID(id, window);
    //            ImGui::SetFocusID(id, window);
    //            ImGui::FocusWindow(window);
    //            g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
    //        }
    //    }

    //    // Our current specs do NOT clamp when using CTRL+Click manual input, but we should eventually add a flag for that..
    //    if (temp_input_is_active || temp_input_start)
    //        return ImGui::TempInputScalar(frame_bb, id, label, data_type, p_data, format);// , p_min, p_max);


    //    // Draw frame

    //    const ImU32 frame_col = ImGui::GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : g.HoveredId == id ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
    //    const ImVec4 hover_act = ImVec4(155 / 255.f, 155 / 255.f, 155 / 255.f, 1.f);
    //    const ImVec4 hover_dis = ImVec4(74 / 255.f, 79 / 255.f, 143 / 255.f, 1.f);
    //    const ImVec4 hover_off = ImVec4(74 / 255.f, 79 / 255.f, 143 / 255.f, 0.4f);


    //    float deltatime = 1.5f * ImGui::GetIO().DeltaTime;

    //    static std::map<ImGuiID, ImVec4> hover_animation;
    //    auto it_hover = hover_animation.find(id);
    //    if (it_hover == hover_animation.end())
    //    {
    //        hover_animation.insert({ id, hover_off });
    //        it_hover = hover_animation.find(id);
    //    }
    //    if (hovered || g.ActiveId == id)
    //    {
    //        ImVec4 to = hover_act;
    //        if (it_hover->second.x != to.x)
    //        {
    //            if (it_hover->second.x < to.x)
    //                it_hover->second.x = ImMin(it_hover->second.x + deltatime, to.x);
    //            else if (it_hover->second.x > to.x)
    //                it_hover->second.x = ImMax(to.x, it_hover->second.x - deltatime);
    //        }

    //        if (it_hover->second.y != to.y)
    //        {
    //            if (it_hover->second.y < to.y)
    //                it_hover->second.y = ImMin(it_hover->second.y + deltatime, to.y);
    //            else if (it_hover->second.y > to.y)
    //                it_hover->second.y = ImMax(to.y, it_hover->second.y - deltatime);
    //        }

    //        if (it_hover->second.z != to.z)
    //        {
    //            if (it_hover->second.z < to.z)
    //                it_hover->second.z = ImMin(it_hover->second.z + deltatime, to.z);
    //            else if (it_hover->second.z > to.z)
    //                it_hover->second.z = ImMax(to.z, it_hover->second.z - deltatime);
    //        }

    //        if (it_hover->second.w != to.w)
    //        {
    //            if (it_hover->second.w < to.w)
    //                it_hover->second.w = ImMin(it_hover->second.w + deltatime, to.w);
    //            else if (it_hover->second.w > to.w)
    //                it_hover->second.w = ImMax(to.w, it_hover->second.w - deltatime);
    //        }
    //    }
    //    else
    //    {
    //        ImVec4 to = hover_off;
    //        if (it_hover->second.x != to.x)
    //        {
    //            if (it_hover->second.x < to.x)
    //                it_hover->second.x = ImMin(it_hover->second.x + deltatime, to.x);
    //            else if (it_hover->second.x > to.x)
    //                it_hover->second.x = ImMax(to.x, it_hover->second.x - deltatime);
    //        }

    //        if (it_hover->second.y != to.y)
    //        {
    //            if (it_hover->second.y < to.y)
    //                it_hover->second.y = ImMin(it_hover->second.y + deltatime, to.y);
    //            else if (it_hover->second.y > to.y)
    //                it_hover->second.y = ImMax(to.y, it_hover->second.y - deltatime);
    //        }

    //        if (it_hover->second.z != to.z)
    //        {
    //            if (it_hover->second.z < to.z)
    //                it_hover->second.z = ImMin(it_hover->second.z + deltatime, to.z);
    //            else if (it_hover->second.z > to.z)
    //                it_hover->second.z = ImMax(to.z, it_hover->second.z - deltatime);
    //        }

    //        if (it_hover->second.w != to.w)
    //        {
    //            if (it_hover->second.w < to.w)
    //                it_hover->second.w = ImMin(it_hover->second.w + deltatime, to.w);
    //            else if (it_hover->second.w > to.w)
    //                it_hover->second.w = ImMax(to.w, it_hover->second.w - deltatime);
    //        }
    //    }


    //    static map<ImGuiID, ImVec4> grab_animation;
    //    auto it_grab = grab_animation.find(id);
    //    if (it_grab == grab_animation.end())
    //    {
    //        grab_animation.insert({ id, hover_dis });
    //        it_grab = grab_animation.find(id);
    //    }
    //    if (g.ActiveId == id)
    //    {
    //        ImVec4 to = hover_act;
    //        if (it_grab->second.x != to.x)
    //        {
    //            if (it_grab->second.x < to.x)
    //                it_grab->second.x = ImMin(it_grab->second.x + deltatime, to.x);
    //            else if (it_grab->second.x > to.x)
    //                it_grab->second.x = ImMax(to.x, it_grab->second.x - deltatime);
    //        }

    //        if (it_grab->second.y != to.y)
    //        {
    //            if (it_grab->second.y < to.y)
    //                it_grab->second.y = ImMin(it_grab->second.y + deltatime, to.y);
    //            else if (it_grab->second.y > to.y)
    //                it_grab->second.y = ImMax(to.y, it_grab->second.y - deltatime);
    //        }

    //        if (it_grab->second.z != to.z)
    //        {
    //            if (it_grab->second.z < to.z)
    //                it_grab->second.z = ImMin(it_grab->second.z + deltatime, to.z);
    //            else if (it_grab->second.z > to.z)
    //                it_grab->second.z = ImMax(to.z, it_grab->second.z - deltatime);
    //        }
    //    }
    //    else
    //    {
    //        ImVec4 to = hover_dis;
    //        if (it_grab->second.x != to.x)
    //        {
    //            if (it_grab->second.x < to.x)
    //                it_grab->second.x = ImMin(it_grab->second.x + deltatime, to.x);
    //            else if (it_grab->second.x > to.x)
    //                it_grab->second.x = ImMax(to.x, it_grab->second.x - deltatime);
    //        }

    //        if (it_grab->second.y != to.y)
    //        {
    //            if (it_grab->second.y < to.y)
    //                it_grab->second.y = ImMin(it_grab->second.y + deltatime, to.y);
    //            else if (it_grab->second.y > to.y)
    //                it_grab->second.y = ImMax(to.y, it_grab->second.y - deltatime);
    //        }

    //        if (it_grab->second.z != to.z)
    //        {
    //            if (it_grab->second.z < to.z)
    //                it_grab->second.z = ImMin(it_grab->second.z + deltatime, to.z);
    //            else if (it_grab->second.z > to.z)
    //                it_grab->second.z = ImMax(to.z, it_grab->second.z - deltatime);
    //        }
    //    }

    //    window->DrawList->AddRectFilled(frame_bb.Min + ImVec2(1.5f, 1.5f) - ImVec2(0, 2.5f), frame_bb.Max + ImVec2(0.2f, 0.2f) - ImVec2(2.2f, 0.0f), ImColor(33.f / 255.f, 33.f / 255.f, 33.f / 255.f, 1.f), 0.0f);
    //    // window->DrawList->AddRect(frame_bb.Min + ImVec2(1.5f, 1.5f) - ImVec2(0, 5), frame_bb.Max + ImVec2(0.2f, 2.2f), ImColor(20, 20, 20, 255), 3.f, 15, 1.0f);


    //     // Slider behavior
    //    ImRect grab_bb;
    //    ImRect hov_bb;
    //    const bool value_changed = ImGui::SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, power, ImGuiSliderFlags_None, &grab_bb);
    //    if (value_changed)
	   //     ImGui::MarkItemEdited(id);
    //    hov_bb = hov_bb;
    //    // Render grab
    //    if (grab_bb.Max.x > grab_bb.Min.x)
    //        window->DrawList->AddRectFilled(frame_bb.Min + ImVec2(1.5f, 1.5f) - ImVec2(0, 2.5f), grab_bb.Max + ImVec2(0.2f, 2.2f) + ImVec2(0, 0), ImColor(155, 155, 155, 255), 0.0f);


    //    // Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
    //    char value_buf[64];
    //    const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

    //    const bool clicked = (hovered && g.IO.MouseClicked[0]);
    //    static bool held = false;
    //    if (hovered && g.IO.MouseClicked[0] || clicked && g.IO.MouseClicked[0])
    //        held = true;
    //    else if (!g.IO.MouseClicked[0])
    //        held = false;


    //    window->DrawList->AddText(ImVec2(frame_bb.Max.x - ImGui::CalcTextSize(value_buf).x, frame_bb.Min.y - ImGui::CalcTextSize(value_buf).y - (4 * 1)), (*(int*)p_data > 1) ? ImColor(255, 255, 255) : ImColor(170, 170, 170, 200), value_buf, value_buf_end);

    //    if (label_size.x > 0.0f)
	   //     ImGui::RenderText(ImVec2(frame_bb.Min.x, frame_bb.Min.y - ImGui::CalcTextSize(label).y - (4 * 1)), label);



    //    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);
    //    return value_changed;
    //}
    
	bool slider_float(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
	{
		return SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
	}

	bool slider_int(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
	{
		return SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, flags);
	}

}

#endif