#pragma once
#include "../SDK/Imports.hpp"
#include "Settings.hpp"
#include "../../globals.h"
#include "../../AuthLib/AutherLibrary.h"
#include "../Overlay.hpp"
#include "../../helpers/helpers.h"


#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 
#include "../imgui/imgui_internal.h"
#include "../retake/checkbox.hpp"
#include "../retake/slider.hpp"
#include "../retake/combo.hpp"
#include "../retake/tab.hpp"
#include "../retake/subtab.hpp"
#include "../retake/button.hpp"
#include "../retake/childs.hpp"
#include "../retake/new.hpp"

#include "../../DiscordRPC/discordrpc.h"

Discord* g_Discord;

void configSam()
{
    Settings::enableAimbot = TRUE;
    Settings::enableAimbotDistance = TRUE;
    // Settings::enableDroppedItem = TRUE;
    Settings::enableVisuals = TRUE;
    Settings::enableRCS = TRUE;
    //Settings::drawBox = TRUE;
    //Settings::drawWeapon = TRUE;
    Settings::drawName = TRUE;
    Settings::drawCrosshair = TRUE;
    //Settings::adminFlag = TRUE;
    Settings::drawHealthBar = TRUE;
    Settings::thickBullettt = TRUE;
    Settings::nightSky = TRUE;
    Settings::SpeedHack = TRUE;

    Settings::SpeedHackKey = 0x43;
    Settings::SpeedHackSpeed = -0.47;
    Settings::aimbotDistance = 100;
    // Settings::boxDistance = 200;
    Settings::playerDistance = 200;
    //Settings::weaponDistance = 200;
   // Settings::enableDroppedItemDistance = 100;

    Settings::RCSpitch = -10;
    Settings::RCSyaw = -10;
    Settings::aimbotFov = 60;

    Settings::CrosshairLength = 7;
    Settings::CrosshairGap = 3;
    Settings::CrosshairThickness = 2;


    //Settings::drawColor_box[0] = 1; Settings::drawColor_box[1] = 0; Settings::drawColor_box[2] = 0; Settings::drawColor_box[3] = 1;
    Settings::drawColor_name[0] = 1; Settings::drawColor_name[1] = 0; Settings::drawColor_name[2] = 0; Settings::drawColor_name[3] = 1;
    //Settings::drawColor_weapon[0] = 1;Settings::drawColor_weapon[1] = 1;Settings::drawColor_weapon[2] = 1;Settings::drawColor_weapon[3] = 1;
    //Settings::DroppedItemCol[0] = 1;Settings::DroppedItemCol[1] = 0.943396;Settings::DroppedItemCol[2] = 0;Settings::DroppedItemCol[3] = 1;
    Settings::espColorMisc[0] = 0.867925; Settings::espColorMisc[1] = 0; Settings::espColorMisc[2] = 1; Settings::espColorMisc[3] = 1;

}

const char* boxTypes[] = { ("Static Box"), ("Corner Box"), ("Filled Box") };
const char* oresItems[] = {
    "Stone Ore",
    "Metal Ore",
    "Sulfur Ore",
    "Stone Collectable",
    "Metal Collectable",
    "Sulfur Collectable",
    "Wood Collectable",
    "Hemp Fibers",
    "Stash",
    "Barrel",
    "Oil Barrel",
    "Elite Crate",
    "Military Crate",
    "Medical Crate",
    "Normal Crate",
    "Food Crate",
    "Tool Box",
    "Boat",
    "RHIB",
    "kayak",
    "Minicopter",
    "Bradley",
    "Corpse" };

static bool init = false;

void* __fastcall menu()
{
    ImGuiStyle& style = ImGui::GetStyle();
    if (init == false)
    {
        style.ScrollbarSize = 1;
        style.GrabMinSize = 1;
        style.WindowBorderSize = 0;
        style.ChildBorderSize = 1;
        style.PopupBorderSize = 0;
        style.FrameBorderSize = 1;
        style.WindowRounding = 6;
        style.ChildRounding = 6;
        style.FrameRounding = 6;
        style.PopupRounding = 6;
        style.ScrollbarRounding = 6;
        style.GrabRounding = 6;

        ImGui::SetNextWindowPos(ImVec2(-10, -10));
        ImGui::SetNextWindowBgAlpha(255.f);

        //Window Size
        ImGui::SetNextWindowSize({ 500.000000f, 345.000000f });
        ImGui::SetNextWindowPos(ImVec2((1920 - 840) * .5, (1080 - 500) * .5), ImGuiCond_Once);
        init = true;
    }

    style.Colors[ImGuiCol_WindowBg] = ImColor(55, 46, 58, 255);

    ImGui::Begin(safe_str("cheat"), (bool*)true, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
    {
        ImGui::SetScrollY(0);

        ImVec2 p = ImGui::GetCursorScreenPos();
        ImColor barColors = ImColor(88, 0, 255, 255);

        ImVec2 position = ImGui::GetWindowPos();
        ImDrawList* draw = ImGui::GetWindowDrawList();

        ImTricks::NotifyManager::HandleNotifies(ImGui::GetOverlayDrawList());

        ImGui::PushFont(Overlay::fontMenu);

        ImVec2 text = ImGui::CalcTextSize("vos.club");

        //logo text
        draw->AddText({ position.x + 11, position.y + 3}, ImColor( 97, 79, 104, 255 ), "vos.club");
        draw->AddLine(ImVec2(position.x, position.y + 21), ImVec2(position.x + 500, position.y + 21), ImColor(43, 33, 47, 255));

        draw->AddRectFilled(ImVec2(position.x, position.y + 21), ImVec2(position.x + 113, position.y + 345), ImColor(43, 33, 47, 255));
        ImGui::SetCursorPos(ImVec2(11 + text.x + 5, 3));
        ImGui::TextColored(ImColor( 97, 79, 104, 255 ), "%c", "|/-\\"[(int)(ImGui::GetTime() / 0.5f) & 3]);

        static int page = 0;
        static int esp = 0;

        ImGui::SetCursorPos({ 5, 26 });
        if (Retake::tab("Aimbot", page == 0))
        {
            page = 0;
        }

        ImGui::SetCursorPos({ 5, 51 });
        if (Retake::tab("Visual", page == 1))
        {
            page = 1;
        }

        ImGui::SetCursorPos({ 5, 126 });
        if (Retake::tab("Misc", page == 2))
        {
            page = 2;
        }

        ImGui::SetCursorPos({ 5, 151 });
        if (Retake::tab("Configs", page == 3))
        {
            page = 3;
        }

        ImGui::SetCursorPos({ 5, 320 });
        if (Retake::tab("Dashboard", page == 4))
        {
            page = 4;
        }

            ImGui::SetCursorPos({ 5, 71 });
            if (Retake::subtab("ESP", esp == 0))
            {
                page = 1;
                esp = 0;
            }

            ImGui::SetCursorPos({ 5, 91 });
            if (Retake::subtab("Items", esp == 1))
            {
                page = 1;
                esp = 1;
            }

            ImGui::SetCursorPos({ 5, 111 });
            if (Retake::subtab("Colors", esp == 2))
            {
                page = 1;
                esp = 2;
            }
        {

            ImGui::SetCursorPos({ 120, 30 });
            ImGui::BeginChild("", ImVec2(370, 280));
            {
                if (page == 0)
                {
                    Retake::RetakeBeginChild("Aim", ImVec2(370, 250));

                    Retake::checkbox("Enable Aimbot", &Settings::enableAimbot);
                    ImGui::Text("Aimbot Key"); ImGui::SameLine(); ImGui::Hotkey("##Aimbot Key", &Settings::aimbotKey, ImVec2(80, 18));

                    ImGui::Spacing();

                    Retake::slider_int("Aimbot FOV", &Settings::aimbotFov, 0, 360, "%.1f", NULL);

                    Retake::checkbox("Enable Distance", &Settings::enableAimbotDistance);
                    Retake::slider_int("Aimbot Distance", &Settings::aimbotDistance, 0, 300, "%.1f", NULL);

                    ImGui::PushItemWidth(ImGui::GetWindowWidth() - 220);
                    ImGui::Spacing();
                    const char* listbox_items[] = { "Head", "Chest", "Pevlis" };

                    ImGui::Combo("##Hitbox", &Settings::aimbotHitbox, listbox_items, IM_ARRAYSIZE(listbox_items));

                    //ImGui::ListBox("##Hitbox", &Settings::aimbotHitbox, listbox_items, IM_ARRAYSIZE(listbox_items));
                    Retake::checkbox("ThickBullet", &Settings::thickBullettt);

                    Retake::RetakeEndChild();
                }
                if (page == 1)
                {
                    if (esp == 0)
                    {
                        Retake::checkbox("Enable Visuals", &Settings::enableVisuals);
                        {
                            Retake::RetakeBeginChild("Players", ImVec2(175, 195));
                            {
                                Retake::checkbox(("Name"), &Settings::drawName);
                                Retake::checkbox(("Box"), &Settings::drawBox);
                                Retake::combo(("Box Type"), &Settings::typeBox, boxTypes, 3);
                                Retake::checkbox(("Skeleton"), &Settings::drawSkeleton);
                                Retake::checkbox(("Health Bar"), &Settings::drawHealthBar);
                                Retake::checkbox(("Weapon"), &Settings::drawWeapon);
                                Retake::slider_int(("Distance"), &Settings::playerDistance, 100, 300, "%.1f", NULL);
                            }
                            Retake::RetakeEndChild();

                            ImGui::SameLine();

                            Retake::RetakeBeginChild("Other", ImVec2(175, 210));
                            {
                                Retake::checkbox(("Crosshair"), &Settings::drawCrosshair);
                                Retake::checkbox("while scoped", &Settings::crosshairScoped);
                                Retake::slider_int("Length", &Settings::CrosshairLength, 1, 24, "%.1f", NULL);
                                Retake::slider_int("Gap", &Settings::CrosshairGap, 0, 24, "%.1f", NULL);
                                Retake::slider_int("Thickness", &Settings::CrosshairThickness, 1, 24, "%.1f", NULL);
                                Retake::slider_int(("Fov Changer"), &Settings::FovSlider, 75, 150, "%.1f", NULL);
                            }
                            Retake::RetakeEndChild();
                        }
                    }
                    if (esp == 1)
                    {
                        Retake::RetakeBeginChild("Items", ImVec2(175, 140));
                        {
                            Retake::checkbox(("Dropped Items"), &Settings::enableDroppedItem);
                            Retake::slider_int(("Dropped Items distance"), &Settings::droppedDistance, 100, 300, "%.1f", NULL);
                        }
                        Retake::RetakeEndChild();

                        ImGui::SameLine();

                        Retake::RetakeBeginChild("Object list", ImVec2(175, 280));
                        if (ImGui::ListBoxHeader("##ESP Object List", ImVec2(170, 245)))
                        {
                            for (size_t i = 0; i < IM_ARRAYSIZE(Settings::selectedOres); i++) {
                                ImGui::Selectable(oresItems[i], &Settings::selectedOres[i], ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
                            }
                            ImGui::ListBoxFooter();
                        }
                        Retake::RetakeEndChild();
                    }
                    if (esp == 2)
                    {
                        Retake::RetakeBeginChild(" ", ImVec2(350, 250));
                        //ImGui::Text("Weapon Color"); 
                        Retake::ColorPicker(("Weapon Color"), Settings::drawColor_weapon, ImGuiColorEditFlags_NoInputs);
                        //ImGui::Text("Skeleton Color"); 
                        Retake::ColorPicker(("Skeleton Color"), Settings::drawColor_skeleton, ImGuiColorEditFlags_NoInputs);
                        //ImGui::Text("Name Color"); 
                        Retake::ColorPicker(("Name Color"), Settings::drawColor_name, ImGuiColorEditFlags_NoInputs);
                        //ImGui::Text("Dropped Items Color"); 
                        Retake::ColorPicker(("Dropped Items Color"), Settings::DroppedItemCol, ImGuiColorEditFlags_NoInputs);
                        //ImGui::Text("Crosshair Color"); 
                        Retake::ColorPicker(("Crosshair Color"), Settings::drawColor_crosshair, ImGuiColorEditFlags_NoInputs);
                        //ImGui::Text("ESP Object Color"); 
                        Retake::ColorPicker(("ESP Object Color"), Settings::espColorMisc, ImGuiColorEditFlags_NoInputs);
                        Retake::RetakeEndChild();
                    }
                }
                if (page == 2)
                {
                    Retake::RetakeBeginChild(safe_str("Weapon"), ImVec2(160, 280));
                        Retake::checkbox(safe_str("Rapid Fire"), &Settings::rapidFire);
                        if (Settings::rapidFire)
                        {
                            Retake::slider_float(safe_str("Rapid Fire Value"), &Settings::rapidfirevalue, 0.01, 0.09, safe_str("%.2f"), 1);
                        }
                        Retake::checkbox(safe_str("Enable RCS"), &Settings::enableRCS);
                        if (Settings::enableRCS)
                        {
                            Retake::slider_int(safe_str("RCS X"), &Settings::RCSyaw, 0, -50, "%i", NULL);
                            Retake::slider_int(safe_str("RCS Y"), &Settings::RCSpitch, 0, -50, "%i", NULL);
                        }
                        Retake::checkbox(safe_str("No Spread"), &Settings::noSpread);
                        Retake::checkbox(safe_str("NoAimCone"), &Settings::noAimcone);
                        Retake::checkbox(safe_str("No Sway"), &Settings::noSway);
                        Retake::checkbox(safe_str("Instant Compound"), &Settings::instantCompound);
                        Retake::checkbox(safe_str("Instant Switch"), &Settings::fastSwitchWeapons);
                        Retake::checkbox(safe_str("instant eoka"), &Settings::tapeoka);
                	Retake::RetakeEndChild();

                    ImGui::SameLine();

                	Retake::RetakeBeginChild("Player", ImVec2(200, 280));

                        Retake::checkbox(("Spider Climb"), &Settings::spiderClimb);
                        Retake::checkbox(("ar"), &Settings::fly);

                        Retake::checkbox(("Fast Kill"), &Settings::fastKill);
                        if (Settings::fastKill)
                        {
                           // ImGui::SameLine();
                            ImGui::Hotkey(("##fast Kill Key"), &Settings::fastKillKey, ImVec2(80, 15));
                        }

                        Retake::checkbox(("admin flag"), &Settings::adminFlag);
                        Retake::checkbox(("Time Changer"), &Settings::night_mode);
                        if (Settings::night_mode)
                            ImGui::SliderFloat(("Time"), &Settings::time, 0, 24);

                        Retake::checkbox("Sky Color", &Settings::skyColorBool);
                        if (Settings::skyColorBool)
                            ImGui::SliderFloat("color", &Settings::SkyColor, 0, 100);


                        Retake::checkbox(("Long Hit"), &Settings::longhit);
                        Retake::checkbox(("third person"), &Settings::thirdperson);
                        Retake::checkbox(("Long Neck"), &Settings::shootInAir);
                        if (Settings::shootInAir)
                        {
                            ImGui::SameLine();
                            ImGui::Hotkey(("##Long Neck Key"), &Settings::LongNeckKey, ImVec2(80, 15));
                        }
                        Retake::checkbox("High Jump", &Settings::SuperJump);
                        if (Settings::SuperJump)
                        {
                            Retake::slider_float("value", &Settings::GravitySlider, 2.8, 0, "%.1f", 1);
                        }
                        Retake::checkbox("Hold Items While Mounted", &Settings::ShootMounted);
                        Retake::checkbox("Speed Hack", &Settings::SpeedHack);
                        if (Settings::SpeedHack)
                        {
                            ImGui::SameLine();
                            ImGui::Hotkey(("##Speed Hack Key"), &Settings::SpeedHackKey, ImVec2(80, 15));
                            Retake::slider_float("Speed", &Settings::SpeedHackSpeed, 0, -10, "%.2f", NULL);
                        }
                        Retake::checkbox(("Bright Night"), &Settings::nightSky);
                        Retake::checkbox(("Run Hit"), &Settings::runhit);
                        Retake::checkbox(("Zoom"), &Settings::zoom);
                        if (Settings::zoom)
                        {
                            ImGui::SameLine();
                            ImGui::Hotkey(("##Zoom Key"), &Settings::zoomKey, ImVec2(80, 15));
                        }
                        Retake::checkbox("FlyHack", &Settings::flyHackkk);
                        if (Settings::flyHackkk)
                        {
                            ImGui::SameLine();
                            ImGui::Hotkey("##Flyhack Key", &Settings::flyhackKey, ImVec2(80, 15));
                            Retake::slider_float(("speed"), &Settings::flyhackSpeed, 6, -5, "%.0f", 1);
                        }
                        Retake::checkbox(("Jesus mode"), &Settings::walkOnWater);
                        if (Settings::walkOnWater)
                        {
                            ImGui::SameLine();
                            ImGui::Hotkey(("##Jesus Key"), &Settings::walkWaterKEY, ImVec2(80, 15));
                        }

                	Retake::RetakeEndChild();
                }
                if (page == 3)
                {
                    Retake::RetakeBeginChild("Config", ImVec2(150, 200));
                    //Retake::RetakeBeginChild("Config", ImVec2(150, 200));
                    {
                        Retake::checkbox("Watermark", &Settings::watermark);
                        //if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                        //{
                        //    ImGui::SetTooltip("Watermark");
                        //}

                        if (Retake::button("Load admin cfg", ImVec2(120, 20))) {
                            configSam();
                            ImTricks::NotifyManager::AddNotify("Admin config loaded.", ImTrickNotify_Success);
                        }

                        if (Retake::button("Exit", ImVec2(50, 20)))
                            exit(1);
                    }
                    Retake::RetakeEndChild();

                    //ImGui::SameLine();

                    //Retake::RetakeBeginChild("Debug", ImVec2(120, 80));
                    //{
                    //    if (Retake::button("Print debug true", ImVec2(110, 20)))
                    //        Settings::debuglog = true;

                    //    if (Retake::button("Print debug false", ImVec2(110, 20)))
                    //        Settings::debuglog = false;
                    //}
                    //Retake::RetakeEndChild();
                }
                if (page == 4)
                {
                	GUI::News("Information", dls(safe_str("https://a-p.fun/info.php")).c_str());
                }
            }
            ImGui::EndChild();
        }


        ImGui::PopFont();
    }
    ImGui::End();
}

void* __fastcall login() {
    //ImGui::SetNextWindowBgAlpha(255.f);
    ImGui::SetNextWindowSize({ 300.000000f,60.000000f });
    
    ImGuiStyle& style = ImGui::GetStyle();

    style.IndentSpacing = 21;
    style.ScrollbarSize = 1;
    style.GrabMinSize = 1;
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 1;
    style.WindowRounding = 6;
    style.ChildRounding = 4;
    style.FrameRounding = 4;
    style.PopupRounding = 0;
    style.ScrollbarRounding = 0;
    style.GrabRounding = 0;

    ImGui::Begin(safe_str("log"), (bool*)true, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    {

        ImGui::SetCursorPos({ 30, 10 });
        ImGui::Text("key:");

        ImGui::SetCursorPos({ 60, 8 });
        ImGui::InputText("", globals.user_name, IM_ARRAYSIZE(globals.user_name));
        ImGui::SetCursorPos({ 60, 8 });
    	ImGui::InputText("", globals.pass_word, IM_ARRAYSIZE(globals.pass_word));

        ImGui::SetCursorPos({ 115, 33 });
        if (ImGui::Button("Login", ImVec2(75, 20))) 
        {
            if (globals.auth == false)
            {
                globals.auth = true;
            }
            else
            {
                exit(0);
            }
        }
    }
    ImGui::End();
}
