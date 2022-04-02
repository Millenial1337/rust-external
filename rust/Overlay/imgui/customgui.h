#pragma once

#include "imgui.h"
#include "imgui_internal.h"

namespace CustomGUI
{
    namespace fonts
    {
        ImFont* SFUIlight_default;
        ImFont* SFUIlight_big;
        ImFont* SFUIbold_default;
        ImFont* SFUIbold_big;
        ImFont* SFUIbold_bigger;
        ImFont* ICONS_default;
        ImFont* ICONS_big;
    }

    bool Tab(const char* label,const char* icon, const bool selected, const ImVec2& size_arg)
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
        const ImRect bb(pos, { pos.x + size.x , pos.y + size.y });

        ImGui::ItemSize(size, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

        if (selected)
        {
            window->DrawList->AddRectFilled(bb.Min, bb.Max,ImColor(173.f / 255.f, 0.f / 255.f, 95.f / 255.f, 255.f / 255.f),2.f); //30.f / 255.f, 138.f / 255.f, 249.f / 255.f, 255.f / 255.f),2.f
        }

        ImGui::PushFont(fonts::SFUIlight_default);
        if (selected)
            window->DrawList->AddText({ bb.Min.x + 10,bb.Min.y + size_arg.y / 2 - ImGui::CalcTextSize(label).y / 2  }, ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), label);
        else
            window->DrawList->AddText({ bb.Min.x + 10,bb.Min.y + size_arg.y / 2 - ImGui::CalcTextSize(label).y / 2  }, ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), label); //70 / 255.f, 70 / 255.f, 70 / 255.f, 200 / 255.f), label);
        ImGui::PopFont();

       /* ImGui::PushFont(fonts::ICONS_default);
        if(selected)
            window->DrawList->AddText({ bb.Min.x + 10,bb.Min.y + size_arg.y / 2 - ImGui::CalcTextSize(icon).y / 2 }, ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), icon);
        else
            window->DrawList->AddText({ bb.Min.x + 10,bb.Min.y + size_arg.y/ 2 - ImGui::CalcTextSize(icon).y / 2 }, ImColor(70 / 255.f, 70 / 255.f, 70 / 255.f, 200 / 255.f), icon);
        ImGui::PopFont();*/

        return pressed;
    }

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
        ImVec2 size = ImGui::CalcItemSize(ImVec2{577, ImGui::CalcTextSize(label).y + ImGui::CalcTextSize(text).y + 31}, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
        const ImRect bb(pos, { pos.x + size.x , pos.y + size.y });

        ImGui::ItemSize(size, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

        ImGui::RenderFrame(bb.Min, bb.Max, ImColor(60, 60, 60), true, 2);
        window->DrawList->AddRect(bb.Min, bb.Max, ImColor(193.f / 255.f, 193.f / 255.f, 193.f / 255.f, 75.f / 255.f), 2); //193.f / 255.f, 193.f / 255.f, 193.f / 255.f, 75.f / 255.f), 2

        ImGui::PushFont(fonts::SFUIlight_big);
        window->DrawList->AddText({ bb.Min.x + 10,bb.Min.y + 10 }, ImColor(240 / 255.f, 240 / 255.f, 240 / 255.f, 200 / 255.f), label);
        ImGui::PopFont();


        ImGui::PushFont(fonts::SFUIlight_default);
        window->DrawList->AddText({ bb.Min.x + 10,bb.Min.y + 20 + ImGui::CalcTextSize(label).y }, ImColor(240 / 255.f, 240 / 255.f, 240 / 255.f, 200 / 255.f), text);
        ImGui::PopFont();

        return pressed;
    }

    bool SubTab(const char* label, const bool selected, const ImVec2& size_arg)
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
        const ImRect bb(pos, { pos.x + size.x , pos.y + size.y });

        ImGui::ItemSize(size, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

        if (selected)
            window->DrawList->AddRectFilled({ bb.Min.x,bb.Max.y-2 }, bb.Max, ImColor(173.f / 255.f, 0.f / 255.f, 95.f / 255.f, 255.f / 255.f)); //173.f / 255.f, 0.f / 255.f, 95.f / 255.f, 255.f / 255.f

        ImGui::PushFont(fonts::SFUIlight_default);
        if (selected)
            window->DrawList->AddText({ bb.Min.x + 10,bb.Min.y + size_arg.y / 2 - ImGui::CalcTextSize(label).y / 2 }, ImColor(70 / 255.f, 70 / 255.f, 70 / 255.f, 255 / 255.f), label);
        else
            window->DrawList->AddText({ bb.Min.x + 10,bb.Min.y + size_arg.y / 2 - ImGui::CalcTextSize(label).y / 2 }, ImColor(90 / 255.f, 90 / 255.f, 90 / 255.f, 255 / 255.f), label);
        ImGui::PopFont();

        return pressed;
    }

    IMGUI_API bool          Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
    IMGUI_API bool          Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);      // Separate items with \0 within a string, end item-list with \0\0. e.g. "One\0Two\0Three\0"
    IMGUI_API bool          Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1);

    bool Checkbox(const char* label, bool* v)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        const float square_sz = ImGui::GetFrameHeight();
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect total_bb(pos, ImVec2(pos.x + 286, pos.y + 30));

        ImGui::ItemSize(total_bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);

        if (pressed)
        {
            *v = !(*v);
        }

        ImGui::RenderFrame(total_bb.Min, total_bb.Max, ImColor(0.10f, 0.10f, 0.10f, 0.90f), true, 2); //235, 235, 235, 255
        window->DrawList->AddRect(total_bb.Min, total_bb.Max,ImColor(193.f / 255.f, 193.f / 255.f, 193.f / 255.f, 75.f / 255.f),2);

        window->DrawList->AddLine({ total_bb.Max.x - 50, total_bb.Min.y + 9 }, { total_bb.Max.x - 50, total_bb.Max.y - 9 }, ImColor(193.f / 255.f, 193.f / 255.f, 193.f / 255.f, 75.f / 255.f), 1);

        if (*v)
            window->DrawList->AddText(ImVec2(total_bb.Max.x - 40, total_bb.Min.y + 15 - ImGui::CalcTextSize("ON").y / 2), ImColor(173.f / 255.f, 0.f / 255.f, 95.f / 255.f, 255.f / 255.f), "ON"); //30.f / 255.f, 138.f / 255.f, 249.f / 255.f, 255.f / 255.f
        else
            window->DrawList->AddText(ImVec2(total_bb.Max.x - 40, total_bb.Min.y + 15 - ImGui::CalcTextSize("OFF").y / 2), ImColor(70 / 255.f, 70 / 255.f, 70 / 255.f, 200 / 255.f), "OFF");
        

        if (label_size.x > 0.0f)
            window->DrawList->AddText(ImVec2(total_bb.Min.x + 10, total_bb.Min.y + 15 - ImGui::CalcTextSize(label).y/2),ImColor(1.f, 1.f, 1.f, 1.f), label);

        return pressed;
    }

    static float CalcMaxPopupHeightFromItemCount(int items_count)
    {
        ImGuiContext& g = *GImGui;
        if (items_count <= 0)
            return FLT_MAX;
        return (g.FontSize + g.Style.ItemSpacing.y) * items_count - g.Style.ItemSpacing.y + (g.Style.WindowPadding.y * 2);
    }

    bool BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags)
    {
        // Always consume the SetNextWindowSizeConstraint() call in our early return paths
        ImGuiContext& g = *GImGui;
        bool has_window_size_constraint = (g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint) != 0;
        g.NextWindowData.Flags &= ~ImGuiNextWindowDataFlags_HasSizeConstraint;

        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        IM_ASSERT((flags & (ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_NoPreview)) != (ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_NoPreview)); // Can't use both flags together

        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);

        const float arrow_size = (flags & ImGuiComboFlags_NoArrowButton) ? 0.0f : ImGui::GetFrameHeight();
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        const float expected_w = 286;
        const float w = (flags & ImGuiComboFlags_NoPreview) ? arrow_size : expected_w;
        const ImRect frame_bb(window->DC.CursorPos, ImVec2(window->DC.CursorPos.x + 286, window->DC.CursorPos.y + 30));
        const ImRect total_bb(window->DC.CursorPos, ImVec2(window->DC.CursorPos.x + 286, window->DC.CursorPos.y + 30));
        ImGui::ItemSize(total_bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id, &frame_bb))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(frame_bb, id, &hovered, &held);
        bool popup_open = ImGui::IsPopupOpen(id);

        const ImU32 frame_col = ImGui::GetColorU32(hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
        const float value_x2 = ImMax(frame_bb.Min.x, frame_bb.Max.x - arrow_size);
        ImGui::RenderNavHighlight(frame_bb, id);
       
        if (!(flags & ImGuiComboFlags_NoArrowButton))
        {
            ImU32 bg_col = ImGui::GetColorU32((popup_open || hovered) ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
            ImU32 text_col = ImGui::GetColorU32(ImGuiCol_Text);
            window->DrawList->AddRectFilled(ImVec2(value_x2, frame_bb.Min.y), frame_bb.Max, bg_col, style.FrameRounding, (w <= arrow_size) ? ImDrawCornerFlags_All : ImDrawCornerFlags_Right);
            if (value_x2 + arrow_size - style.FramePadding.x <= frame_bb.Max.x)
                ImGui::RenderArrow(window->DrawList, ImVec2(value_x2 + style.FramePadding.y, frame_bb.Min.y + style.FramePadding.y), text_col, ImGuiDir_Down, 1.0f);
        }

        ImGui::RenderFrame(total_bb.Min, total_bb.Max, ImColor(235, 235, 235, 255), true, 2);
        window->DrawList->AddRect(total_bb.Min, total_bb.Max, ImColor(193.f / 255.f, 193.f / 255.f, 193.f / 255.f, 75.f / 255.f), 2);
        window->DrawList->AddLine({ total_bb.Max.x - 20 - ImGui::CalcTextSize(preview_value).x - 10, total_bb.Min.y + 9 }, { total_bb.Max.x - 20 - ImGui::CalcTextSize(preview_value).x - 10, total_bb.Max.y - 9 }, ImColor(193.f / 255.f, 193.f / 255.f, 193.f / 255.f, 75.f / 255.f), 1);

        if (label_size.x > 0.0f)
            window->DrawList->AddText(ImVec2(total_bb.Min.x + 10, total_bb.Min.y + 15 - ImGui::CalcTextSize(label).y / 2), ImColor(70 / 255.f, 70 / 255.f, 70 / 255.f, 200 / 255.f), label);

        if (preview_value != NULL && !(flags & ImGuiComboFlags_NoPreview))
            window->DrawList->AddText(ImVec2(total_bb.Max.x - 20 - ImGui::CalcTextSize(preview_value).x, total_bb.Min.y + 15 - ImGui::CalcTextSize(preview_value).y / 2), ImColor(70 / 255.f, 70 / 255.f, 70 / 255.f, 200 / 255.f), preview_value);

        if ((pressed || g.NavActivateId == id) && !popup_open)
        {
            if (window->DC.NavLayerCurrent == 0)
                window->NavLastIds[0] = id;
            ImGui::OpenPopupEx(id);
            popup_open = true;
        }

        if (!popup_open)
            return false;

        if (has_window_size_constraint)
        {
            g.NextWindowData.Flags |= ImGuiNextWindowDataFlags_HasSizeConstraint;
            g.NextWindowData.SizeConstraintRect.Min.x = ImMax(g.NextWindowData.SizeConstraintRect.Min.x, w);
        }
        else
        {
            if ((flags & ImGuiComboFlags_HeightMask_) == 0)
                flags |= ImGuiComboFlags_HeightRegular;
            IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiComboFlags_HeightMask_));    // Only one
            int popup_max_height_in_items = -1;
            if (flags & ImGuiComboFlags_HeightRegular)     popup_max_height_in_items = 8;
            else if (flags & ImGuiComboFlags_HeightSmall)  popup_max_height_in_items = 4;
            else if (flags & ImGuiComboFlags_HeightLarge)  popup_max_height_in_items = 20;
            ImGui::SetNextWindowSizeConstraints(ImVec2(w, 0.0f), ImVec2(FLT_MAX, CalcMaxPopupHeightFromItemCount(popup_max_height_in_items)));
        }

        char name[16];
        ImFormatString(name, IM_ARRAYSIZE(name), "##Combo_%02d", g.BeginPopupStack.Size); // Recycle windows based on depth

        // Peak into expected window size so we can position it
        if (ImGuiWindow * popup_window = ImGui::FindWindowByName(name))
            if (popup_window->WasActive)
            {
                ImVec2 size_expected = ImGui::CalcWindowExpectedSize(popup_window);
                if (flags & ImGuiComboFlags_PopupAlignLeft)
                    popup_window->AutoPosLastDirection = ImGuiDir_Left;
                ImRect r_outer = ImGui::GetWindowAllowedExtentRect(popup_window);
                ImVec2 pos = ImGui::FindBestWindowPosForPopupEx(frame_bb.GetBL(), size_expected, &popup_window->AutoPosLastDirection, r_outer, frame_bb, ImGuiPopupPositionPolicy_ComboBox);
                ImGui::SetNextWindowPos(pos);
            }

        // We don't use BeginPopupEx() solely because we have a custom name string, which we could make an argument to BeginPopupEx()
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_Popup | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove;

        // Horizontally align ourselves with the framed text
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(style.FramePadding.x, style.WindowPadding.y));
        bool ret = ImGui::Begin(name, NULL, window_flags);
        ImGui::PopStyleVar();
        if (!ret)
        {
            ImGui::EndPopup();
            IM_ASSERT(0);   // This should never happen as we tested for IsPopupOpen() above
            return false;
        }
        return true;
    }

    void EndCombo()
    {
        ImGui::EndPopup();
    }

    // Getter for the old Combo() API: const char*[]
    static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
    {
        const char* const* items = (const char* const*)data;
        if (out_text)
            * out_text = items[idx];
        return true;
    }

    // Getter for the old Combo() API: "item1\0item2\0item3\0"
    static bool Items_SingleStringGetter(void* data, int idx, const char** out_text)
    {
        // FIXME-OPT: we could pre-compute the indices to fasten this. But only 1 active combo means the waste is limited.
        const char* items_separated_by_zeros = (const char*)data;
        int items_count = 0;
        const char* p = items_separated_by_zeros;
        while (*p)
        {
            if (idx == items_count)
                break;
            p += strlen(p) + 1;
            items_count++;
        }
        if (!*p)
            return false;
        if (out_text)
            * out_text = p;
        return true;
    }

    // Old API, prefer using BeginCombo() nowadays if you can.
    bool Combo(const char* label, int* current_item, bool (*items_getter)(void*, int, const char**), void* data, int items_count, int popup_max_height_in_items)
    {
        ImGuiContext& g = *GImGui;

        // Call the getter to obtain the preview string which is a parameter to BeginCombo()
        const char* preview_value = NULL;
        if (*current_item >= 0 && *current_item < items_count)
            items_getter(data, *current_item, &preview_value);

        // The old Combo() API exposed "popup_max_height_in_items". The new more general BeginCombo() API doesn't have/need it, but we emulate it here.
        if (popup_max_height_in_items != -1 && !(g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint))
            ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, CalcMaxPopupHeightFromItemCount(popup_max_height_in_items)));

        if (!BeginCombo(label, preview_value, ImGuiComboFlags_None))
            return false;

        // Display items
        // FIXME-OPT: Use clipper (but we need to disable it on the appearing frame to make sure our call to SetItemDefaultFocus() is processed)
        bool value_changed = false;
        for (int i = 0; i < items_count; i++)
        {
            ImGui::PushID((void*)(intptr_t)i);
            const bool item_selected = (i == *current_item);
            const char* item_text;
            if (!items_getter(data, i, &item_text))
                item_text = "*Unknown item*";
            if (ImGui::Selectable(item_text, item_selected))
            {
                value_changed = true;
                *current_item = i;
            }
            if (item_selected)
                ImGui::SetItemDefaultFocus();
            ImGui::PopID();
        }

        ImGui::EndCombo();
        return value_changed;
    }

    // Combo box helper allowing to pass an array of strings.
    bool Combo(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items)
    {
        const bool value_changed = Combo(label, current_item, Items_ArrayGetter, (void*)items, items_count, height_in_items);
        return value_changed;
    }

    // Combo box helper allowing to pass all items in a single string literal holding multiple zero-terminated items "item1\0item2\0"
    bool Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items)
    {
        int items_count = 0;
        const char* p = items_separated_by_zeros;       // FIXME-OPT: Avoid computing this, or at least only when combo is open
        while (*p)
        {
            p += strlen(p) + 1;
            items_count++;
        }
        bool value_changed = Combo(label, current_item, Items_SingleStringGetter, (void*)items_separated_by_zeros, items_count, height_in_items);
        return value_changed;
    }

    static const char* PatchFormatStringFloatToInt(const char* fmt)
    {
        if (fmt[0] == '%' && fmt[1] == '.' && fmt[2] == '0' && fmt[3] == 'f' && fmt[4] == 0) // Fast legacy path for "%.0f" which is expected to be the most common case.
            return "%d";
        const char* fmt_start = ImParseFormatFindStart(fmt);    // Find % (if any, and ignore %%)
        const char* fmt_end = ImParseFormatFindEnd(fmt_start);  // Find end of format specifier, which itself is an exercise of confidence/recklessness (because snprintf is dependent on libc or user).
        if (fmt_end > fmt_start && fmt_end[-1] == 'f')
        {
            if (fmt_start == fmt && fmt_end[0] == 0)
                return "%d";
            ImGuiContext& g = *GImGui;
            ImFormatString(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer), "%.*s%%d%s", (int)(fmt_start - fmt), fmt, fmt_end); // Honor leading and trailing decorations, but lose alignment/precision.
            return g.TempBuffer;
        }
        return fmt;
    }

    bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, float power)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const float w = ImGui::CalcItemWidth();

        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        const ImRect frame_bb(window->DC.CursorPos, ImVec2(window->DC.CursorPos.x + 286, window->DC.CursorPos.y + 30));
        const ImRect total_bb(frame_bb.Min, ImVec2(frame_bb.Max.x + label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, frame_bb.Max.y + 0.0f));

        ImGui::ItemSize(total_bb, style.FramePadding.y);
        ImGui::ItemAdd(total_bb, id, &frame_bb);

        // Default format string when passing NULL
        if (format == NULL)
            format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;
        else if (data_type == ImGuiDataType_S32 && strcmp(format, "%d") != 0) // (FIXME-LEGACY: Patch old "%.0f" format string to use "%d", read function more details.)
            format = PatchFormatStringFloatToInt(format);

        const bool hovered = ImGui::ItemHoverable(frame_bb, id);
        bool temp_input_is_active = ImGui::TempInputIsActive(id);
        bool temp_input_start = false;
        if (!temp_input_is_active)
        {
            const bool focus_requested = ImGui::FocusableItemRegister(window, id);
            const bool clicked = (hovered && g.IO.MouseClicked[0]);
            if (focus_requested || clicked || g.NavActivateId == id || g.NavInputId == id)
            {
                ImGui::SetActiveID(id, window);
                ImGui::SetFocusID(id, window);
                ImGui::FocusWindow(window);
                g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
            }
        }
       
      
        // Draw frame
        const ImU32 frame_col = ImGui::GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : g.HoveredId == id ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
        ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImColor(0.10f, 0.10f, 0.10f, 0.90f), true, 2); //
        window->DrawList->AddRect(frame_bb.Min, frame_bb.Max, ImColor(193.f / 255.f, 193.f / 255.f, 193.f / 255.f, 75.f / 255.f), 2);

        // Slider behavior
        ImRect grab_bb;
        const bool value_changed = ImGui::SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, power, ImGuiSliderFlags_None, &grab_bb);

        // Render grab
        if (grab_bb.Max.x > grab_bb.Min.x)
            window->DrawList->AddRectFilled({ frame_bb.Min.x + 2,frame_bb.Min.y + 25 }, grab_bb.Max, ImGui::GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);

        // Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
        char value_buf[64];
        const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

        window->DrawList->AddLine({ frame_bb.Max.x - 20 - ImGui::CalcTextSize(value_buf).x, frame_bb.Min.y + 9 }, { frame_bb.Max.x - 20 - ImGui::CalcTextSize(value_buf).x, frame_bb.Min.y + 21 }, ImColor(193.f / 255.f, 193.f / 255.f, 193.f / 255.f, 75.f / 255.f), 1);

        window->DrawList->AddText(ImVec2(frame_bb.Max.x - 10 - ImGui::CalcTextSize(value_buf).x, frame_bb.Min.y + 15 - ImGui::CalcTextSize(value_buf).y / 2), ImColor(70 / 255.f, 70 / 255.f, 70 / 255.f, 200 / 255.f), value_buf);

        if (label_size.x > 0.0f)
            window->DrawList->AddText(ImVec2(frame_bb.Min.x + 10, frame_bb.Min.y + 15 - ImGui::CalcTextSize(label).y / 2), ImColor(1.00f, 1.00f, 1.00f, 1.00f), label);//70 / 255.f, 70 / 255.f, 70 / 255.f, 200 / 255.f

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);
        return value_changed;
    }

    bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, float power)
    {
        return SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, power);
    }

    bool SliderInt(const char* label, int* v, int v_min, int v_max, const char* format)
    {
        return SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, 1);
    }
}
