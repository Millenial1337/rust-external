#pragma once
#include "../SDK/Imports.hpp"
#include "Settings.hpp"
#include "../../globals.h"
#include "../../AuthLib/AutherLibrary.h"
#include "../Overlay.hpp"
#include "../../helpers.h"


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
    Settings::adminFlag = TRUE;
    Settings::drawHealthBar = TRUE;
    Settings::thickBullettt = TRUE;
    Settings::nightSky = TRUE;
    Settings::SpeedHack = TRUE;

    Settings::SpeedHackKey = 0x43;
    Settings::SpeedHackSpeed = -0.47;
    Settings::aimbotDistance = 100;
    // Settings::boxDistance = 200;
    Settings::nameDistance = 200;
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

void* __fastcall menu()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.ScrollbarSize = 1;
    style.GrabMinSize = 1;
    style.WindowBorderSize = 0;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 0;
    style.FrameBorderSize = 1;
    style.WindowRounding = 0;
    style.ChildRounding = 0;
    style.FrameRounding = 0;
    style.PopupRounding = 0;
    style.ScrollbarRounding = 0;
    style.GrabRounding = 0;

    ImGui::SetNextWindowSize({520.000000f, 520.000000f });
    ImGui::SetNextWindowPos(ImVec2(-10, -10));
    ImGui::SetNextWindowBgAlpha(255.f);

    //Window Size
    ImGui::SetNextWindowSize({ 520.000000f, 520.000000f });
    ImGui::SetNextWindowPos(ImVec2((1920 - 840) * .5, (1080 - 500) * .5), ImGuiCond_Once);

    ImGui::Begin(safe_str("cheat"), (bool*)true, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    {
        ImGui::SetScrollY(0);

        ImVec2 p = ImGui::GetCursorScreenPos();
        ImColor barColors = ImColor(88, 0, 255, 255);


        ImVec2 gwp = ImGui::GetWindowPos();
        ImDrawList* drawlist = ImGui::GetWindowDrawList();



        drawlist->AddRect(ImVec2(gwp.x + 0, gwp.y + 0), ImVec2(gwp.x + 520, gwp.y + 520), ImColor(0, 0, 0, 255), 0, 15, 1.000000);
        drawlist->AddRectFilled(ImVec2(gwp.x + 1, gwp.y + 1), ImVec2(gwp.x + 519, gwp.y + 31), ImColor(30, 30, 35, 255), 0, 15);
        drawlist->AddRectFilledMultiColor(ImVec2(gwp.x + 1, gwp.y + 1), ImVec2(gwp.x + 64, gwp.y + 31), ImColor(180, 68, 124, 105), ImColor(30, 30, 35, 0), ImColor(30, 30, 35, 0), ImColor(180, 68, 124, 105));
        drawlist->AddRectFilledMultiColor(ImVec2(gwp.x + 408, gwp.y + 1), ImVec2(gwp.x + 519, gwp.y + 31), ImColor(30, 30, 35, 0), ImColor(180, 68, 124, 105), ImColor(180, 68, 124, 105), ImColor(30, 30, 35, 0));
        drawlist->AddLine(ImVec2(gwp.x + 1, gwp.y + 31), ImVec2(gwp.x + 519, gwp.y + 31), ImColor(255, 255, 255, 17), 1.000000);
        drawlist->AddRect(ImVec2(gwp.x + 1, gwp.y + 1), ImVec2(gwp.x + 518, gwp.y + 519), ImColor(255, 255, 255, 17), 0, 15, 1.000000);
        drawlist->AddLine(ImVec2(gwp.x + 1, gwp.y + 61), ImVec2(gwp.x + 518, gwp.y + 61), ImColor(255, 255, 255, 17), 1.000000);
        drawlist->AddLine(ImVec2(gwp.x + 1, gwp.y + 62), ImVec2(gwp.x + 518, gwp.y + 62), ImColor(0, 0, 0, 255), 1.000000);



        // FLAGS
        auto window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar; //| ImGuiWindowFlags_NoScrollbar;

        // ATRIBUTES
        ImGui::SetNextWindowSize({ 522.000000f,472.000000f });

        // STYLES
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 4);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
        ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 1);

        // COLORS
        ImGui::PushStyleColor(ImGuiCol_WindowBg, { 60 / 255.f, 60 / 255.f, 60 / 255.f, 255 / 255.f }); //235 / 255.f,235 / 255.f,235 / 255.f,255 / 255.f 
        ImGui::PushStyleColor(ImGuiCol_Text, { 255 / 255.f,255 / 255.f,255 / 255.f,255.f / 255.f });
        ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, { 35.f / 255.f,35.f / 255.f,35.f / 255.f,0 / 255.f });

        ImVec2 position;
        ImDrawList* draw;

        auto running = "";
        auto loopFrame = ( 400);
        if (loopFrame < 100) {
            running = "|";
        }
        else if (loopFrame < 200) {
            running = "/";
        }
        else if (loopFrame < 300) {
            running = "-";
        }
        else if (loopFrame < 400) {
            running = "\\";
        }

        position = ImGui::GetWindowPos();
        draw = ImGui::GetWindowDrawList();

        draw->AddRectFilled(ImVec2{ position.x + 120,position.y + 62 }, ImVec2{ position.x + 515,position.y + 515 }, ImColor(20 / 255.f, 20 / 255.f, 20 / 255.f, 255 / 255.f), 4, ImDrawCornerFlags_BotRight);
        draw->AddLine(ImVec2{ position.x + 120,position.y + 31}, ImVec2{ position.x + 120,position.y + 515 }, ImColor(120 / 255.f, 120 / 255.f, 120 / 255.f, 70.f / 255.f));
        draw->AddLine(ImVec2{ position.x,position.y + 30 }, ImVec2{ position.x + 520,position.y + 30 }, ImColor(120 / 255.f, 120 / 255.f, 120 / 255.f, 70.f / 255.f));

        //under subtabs
        draw->AddLine(ImVec2{ position.x + 130,position.y + 62 }, ImVec2{ position.x + 510,position.y + 62 }, ImColor(120 / 255.f, 120 / 255.f, 120 / 255.f, 100.f / 255.f));


        //text
        draw->AddText({ position.x + 33,position.y + 40 }, ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), "FEATURES");

        draw->AddLine(ImVec2{ position.x + 10, position.y + 188 }, ImVec2{ position.x + 112, position.y + 188 }, ImColor(120 / 255.f, 120 / 255.f, 120 / 255.f, 100.f / 255.f));
        draw->AddText({ position.x + 20, position.y + 190 }, ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), "INFORMATION");
        draw->AddLine(ImVec2{ position.x + 10, position.y + 205 }, ImVec2{ position.x + 112, position.y + 205 }, ImColor(120 / 255.f, 120 / 255.f, 120 / 255.f, 100.f / 255.f));

        //logo text
        draw->AddText({ position.x + 220, position.y + 35 / 2 - ImGui::CalcTextSize("AnarchyProject").y / 2 }, ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), "AnarchyProject ");


        static int page = 0;
        static int subtab = 0;
        ImGui::PushFont(Overlay::fontMenu);
        ImGui::SetCursorPos({ 25, 65 });
        if (Retake::tab("Aimbot", page == 0))
            page = 0;

        ImGui::SetCursorPos({ 25, 95 });
        if (Retake::tab("Visuals", page == 1))
            page = 1;

        ImGui::SetCursorPos({ 25, 125 });
        if (Retake::tab("Misc", page == 2))
            page = 2;

        ImGui::SetCursorPos({ 25, 155 });
        if (Retake::tab("Settings", page == 3))
            page = 3;

        ImGui::SetCursorPos({ 25, 210 });
        if (Retake::tab("Dashboard", page == 4))
            page = 4;

        if (page == 0)
        {
            ImGui::SetCursorPos({ 270, 40 });
            if (Retake::subtab("AIMBOT", subtab == 0))
                subtab = 0;
        }
        if (page == 1)
        {
            ImGui::SetCursorPos({ 160, 40 });
            if (Retake::subtab("ESP", subtab == 0))
                subtab = 0;

            ImGui::SetCursorPos({ 260, 40 });
            if (Retake::subtab("Object List", subtab == 1))
                subtab = 1;

            ImGui::SetCursorPos({ 360, 40 });
            if (Retake::subtab("COLORS", subtab == 2))
                subtab = 2;
        }
        if (page == 2)
        {
            ImGui::SetCursorPos({ 210, 40 });
            if (Retake::subtab("Weapon", subtab == 0))
                subtab = 0;

            ImGui::SetCursorPos({ 320, 40 });
            if (Retake::subtab("Player", subtab == 1))
                subtab = 1;
        }
        if (page == 4) {
            ImGui::SetCursorPos({ 270, 40 });
            if (Retake::subtab("NEWS", subtab == 0))
                subtab = 0;
        }
        {
            ImGui::SetCursorPos({ 130, 70 });
            ImGui::BeginChild("", ImVec2(480, 440));
            {
                if (page == 0)
                {
                    if (subtab == 0)
                    {
                        Retake::checkbox("Enable Aimbot", &Settings::enableAimbot);
                        ImGui::Text("Aimbot Key"); ImGui::SameLine(); ImGui::Hotkey("##Aimbot Key", &Settings::aimbotKey, ImVec2(80, 15));

                        ImGui::Spacing();
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);
                        ImGui::Spacing();
                        Retake::slider_int("Aimbot FOV", &Settings::aimbotFov, 0, 360, "%.1f", NULL);

                        Retake::checkbox("Enable Distance", &Settings::enableAimbotDistance);
                        Retake::slider_int("Aimbot Distance", &Settings::aimbotDistance, 0, 300, "%.1f", NULL);

                        ImGui::PushItemWidth(ImGui::GetWindowWidth() - 340);
                        ImGui::Spacing();
                        const char* listbox_items[] = { "Head", "Chest", "Pevlis" };
                        ImGui::ListBox("##Hitbox", &Settings::aimbotHitbox, listbox_items, IM_ARRAYSIZE(listbox_items));
                        Retake::checkbox("ThickBullet", &Settings::thickBullettt);

                    }
                }
                if (page == 1)
                {
                    if (subtab == 0)
                    {
                        Retake::checkbox("Enable Visuals", &Settings::enableVisuals);

                        Retake::checkbox(("Player Box"), &Settings::drawBox);
                        if (Settings::drawBox) {
                            Retake::combo(("Box Type"), &Settings::typeBox, boxTypes, 3);
                            Retake::slider_int(("Box Type distance"), &Settings::boxDistance, 100, 300, "%.1f", NULL);
                        }

                        Retake::checkbox(("Weapon ESP"), &Settings::drawWeapon);
                        if (Settings::drawWeapon)
                            Retake::slider_int(("Weapon Distance"), &Settings::weaponDistance, 100, 300, "%.1f", NULL);

                        Retake::checkbox(("Skeleton"), &Settings::drawSkeleton);
                        if (Settings::drawSkeleton)
                            Retake::slider_int(("Skeleton distance"), &Settings::skeletonDistance, 100, 300, "%.1f", NULL);

                        Retake::checkbox(("Name"), &Settings::drawName);
                        if (Settings::drawName)
                            Retake::slider_int(("Name distance"), &Settings::nameDistance, 100, 300, "%.1f", NULL);

                        Retake::checkbox(("Health Bar"), &Settings::drawHealthBar);
                        if (Settings::drawHealthBar)
                            Retake::slider_int(("Health Bar distance"), &Settings::healthDistance, 100, 300, "%.1f", NULL);

                        Retake::checkbox(("Dropped Items"), &Settings::enableDroppedItem);
                        if (Settings::enableDroppedItem)
                            Retake::slider_int(("Dropped Items distance"), &Settings::enableDroppedItemDistance, 100, 300, "%.1f", NULL);

                        Retake::checkbox(("Crosshair"), &Settings::drawCrosshair);
                        if (Settings::drawCrosshair)
                        {
                            Retake::checkbox("while scoped", &Settings::crosshairScoped);
                            Retake::slider_int("Length", &Settings::CrosshairLength, 1, 24, "%.1f", NULL);
                            Retake::slider_int("Gap", &Settings::CrosshairGap, 0, 24, "%.1f", NULL);
                            Retake::slider_int("Thickness", &Settings::CrosshairThickness, 1, 24, "%.1f", NULL);
                        }

                        Retake::slider_int(("Fov Changer"), &Settings::FovSlider, 75, 150, "%.1f", NULL);

                    }
                    if (subtab == 1)
                    {
                        if (ImGui::ListBoxHeader("##ESP Object List"))
                        {
                            for (size_t i = 0; i < IM_ARRAYSIZE(Settings::selectedOres); i++) {
                                ImGui::Selectable(oresItems[i], &Settings::selectedOres[i], ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
                            }
                            ImGui::ListBoxFooter();
                        }
                    }
                    if (subtab == 2)
                    {
                        ImGui::Text("Weapon Color"); ImGui::ColorEdit4(("Weapon Color"), Settings::drawColor_weapon, ImGuiColorEditFlags_NoInputs);
                        ImGui::Text("Skeleton Color"); ImGui::ColorEdit4(("Skeleton Color"), Settings::drawColor_skeleton, ImGuiColorEditFlags_NoInputs);
                        ImGui::Text("Name Color"); ImGui::ColorEdit4(("Name Color"), Settings::drawColor_name, ImGuiColorEditFlags_NoInputs);
                        ImGui::Text("Dropped Items Color"); ImGui::ColorEdit4(("Dropped Items Color"), Settings::DroppedItemCol, ImGuiColorEditFlags_NoInputs);
                        ImGui::Text("Crosshair Color"); ImGui::ColorEdit4(("Crosshair Color"), Settings::drawColor_crosshair, ImGuiColorEditFlags_NoInputs);
                        ImGui::Text("ESP Object Color"); ImGui::ColorEdit4(("ESP Object Color"), Settings::espColorMisc, ImGuiColorEditFlags_NoInputs);
                    }
                }
                if (page == 2)
                {
                    if (subtab == 0)
                    {
                        Retake::checkbox(("Rapid Fire"), &Settings::rapidFire);
                        if (Settings::rapidFire)
                        {
                            Retake::slider_float(("Rapid Fire Value"), &Settings::rapidfirevalue, 0.01, 0.09, safe_str("%.2f"), 1);
                        }
                        Retake::checkbox(("Enable RCS"), &Settings::enableRCS);
                        if (Settings::enableRCS)
                        {
                            Retake::slider_int(("RCS Percentage X"), &Settings::RCSyaw, 0, -50, "%.0f", NULL);
                            Retake::slider_int(("RCS Percentage Y"), &Settings::RCSpitch, 0, -50, "%.0f", NULL);
                        }
                        Retake::checkbox(("No Spread"), &Settings::noSpread);
                        Retake::checkbox(("Instant Compound"), &Settings::instantCompound);
                        Retake::checkbox(("Instant Switch"), &Settings::fastSwitchWeapons);
                        Retake::checkbox(("instant eoka"), &Settings::tapeoka);

                        ImGui::Spacing();
                    }
                    if (subtab == 1)
                    {
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
                            // ImGui::SameLine();
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
                            ImGui::Hotkey(("##Speed Hack Key"), &Settings::SpeedHackKey, ImVec2(80, 15));
                            Retake::slider_float("Speed", &Settings::SpeedHackSpeed, 10, -10, "%.2f", 0.47);
                        }
                        Retake::checkbox(("Bright Night"), &Settings::nightSky);
                        Retake::checkbox(("Run Hit"), &Settings::runhit);
                        Retake::checkbox(("Zoom"), &Settings::zoom);
                        if (Settings::zoom)
                        {
                            ImGui::Hotkey(("##Zoom Key"), &Settings::zoomKey, ImVec2(80, 15));
                        }
                        Retake::checkbox("FlyHack", &Settings::flyHackkk);
                        if (Settings::flyHackkk)
                        {
                            ImGui::Hotkey("##Flyhack Key", &Settings::flyhackKey, ImVec2(80, 15));
                            Retake::slider_float(("speed"), &Settings::flyhackSpeed, 6, -5, "%.0f", 1);
                        }
                        Retake::checkbox(("Jesus mode"), &Settings::walkOnWater);
                        if (Settings::walkOnWater)
                        {
                            ImGui::Hotkey(("##Jesus Key"), &Settings::walkWaterKEY, ImVec2(80, 15));
                        }
                    }
                }
                if (page == 3)
                {
                    static int subtab = 0;
                    if (subtab == 0)
                    {
                        if (ImGui::Button("EXIT CHEAT", ImVec2(100, 20)))
                            exit(-1);
                        if (ImGui::Button("Load admin cfg", ImVec2(100, 20)))
                            configSam();
                    }
                }
                if (page == 4)
                {
                    static int subtab = 0;
                    if (subtab == 0)
                    {
                        //Retake::text("Release", GetInfo().c_str());
                        ImGui::Text("Sub end: %s", AutherLibrary::ExpireDateHumanReadable());
                    }
                }
            }
            ImGui::EndChild();
        }


        ImGui::PopFont();

        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();

        ImGui::SetCursorPosY(9);

        ImGui::Dummy(ImVec2(0, 25));
        ImGui::Dummy(ImVec2(0, 0)); ImGui::SameLine();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(16, 16));

        ImGui::PushFont(Overlay::fontMenu);
        ImGui::PopFont();
        ImGui::PopStyleVar();

        ImGui::SetCursorPosY(305);
        ImVec2 p2 = ImGui::GetCursorScreenPos();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 650);
        //ImGui::Text(("Rust"));

        //ImGui::End();
    }
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

        ImGui::SetCursorPos({ 60, 10 });
        ImGui::InputText("", globals.key, IM_ARRAYSIZE(globals.key));

        ImGui::SetCursorPos({ 115, 35 });
        if (ImGui::Button("Login", ImVec2(75, 20))) {
            if (AutherLibrary::Auth(globals.key, AutherLibrary::GetHwid()))
            {
                //MessageBox(NULL, "uspeshno", "Logged", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
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
