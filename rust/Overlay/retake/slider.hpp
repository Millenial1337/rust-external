/////////////////////////////////////////////////////
//                                                   
//    Generated with Retake Design. (ex. ImGui Editor) 
//    Retake Design is designed with love by pers0na2. 
//    All rights to Retake Design belong to pers0na2.  
//                                                   
/////////////////////////////////////////////////////


#ifndef QUARCSLIDER
#define QUARCSLIDER

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 
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
		const float w = 222 - 48;

		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		const ImRect frame_bb(window->DC.CursorPos + ImVec2(0, 16), window->DC.CursorPos + ImVec2(w, 29));
		const ImRect total_bb(frame_bb.Min - ImVec2(0, 16), frame_bb.Max);

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

		window->DrawList->AddRectFilledMultiColor(frame_bb.Min, frame_bb.Max - ImVec2(0, 2), ImColor(40, 40, 46), ImColor(40, 40, 46), ImColor(30, 30, 30), ImColor(30, 30, 30));
		window->DrawList->AddRect(frame_bb.Min, frame_bb.Max - ImVec2(0,2), ImColor(20, 20, 20, 255), 0, 0);

		window->DrawList->AddRectFilledMultiColor(ImVec2(frame_bb.Min.x + 1, frame_bb.Min.y + 1), ImVec2(grab_bb.Max.x + 1, grab_bb.Max.y + 1 - 2), ImColor(30, 30, 35, 0), ImColor(180, 68, 124, 200), ImColor(180, 68, 124, 200), ImColor(30, 30, 35, 0));

		char value_buf[64];
		const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

		float grab_w = grab_bb.Max.x - grab_bb.Min.x;
		auto const moved_pos_of_prev_rect = 1;
		auto const preview_w = ImGui::CalcTextSize((std::stringstream{ } << value_buf).str().c_str()).x;
		ImVec2 text_pos = grab_bb.Min + ImVec2(grab_w, moved_pos_of_prev_rect);

		ImGui::GetOverlayDrawList()->AddText(text_pos - ImVec2(preview_w / 2, 0), ImColor(229 / 255.f, 229 / 255.f, 229 / 255.f, 230 / 255.f), value_buf);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, 230 / 255.f));
		ImGui::RenderText(ImVec2(frame_bb.Min.x, frame_bb.Min.y - 16), label);
		ImGui::PopStyleColor();

		return value_changed;
	}

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