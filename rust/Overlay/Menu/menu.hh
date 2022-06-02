#pragma once
#include "../SDK/Imports.hpp"
#include "Settings.hpp"
#include "../imgui/customfont.h"
#include "../imgui/customgui.h"
#include "../../globals.h"
#include "../../AuthLib/AutherLibrary.h"
#include "../Overlay.hpp"

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
    ImGui::SetNextWindowSize(ImVec2(screenWidth + 15, screenHeight + 15));
    ImGui::SetNextWindowPos(ImVec2(-10, -10));
    ImGui::SetNextWindowBgAlpha(255.f);

    //Window Size
    ImGui::SetNextWindowSize(ImVec2(620, 600)); //800, 550
    ImGui::SetNextWindowPos(ImVec2((1920 - 840) * .5, (1080 - 500) * .5), ImGuiCond_Once);

    //ImGui::Begin(safe_str("main"), (bool*)true, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    {
        ImGui::SetScrollY(0);

        ImVec2 p = ImGui::GetCursorScreenPos();
        ImColor barColors = ImColor(88, 0, 255, 255);

        // FLAGS
        auto window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar;

        // ATRIBUTES
        ImGui::SetNextWindowSize({ 800,550 });

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

        draw->AddRectFilled(ImVec2{ position.x + 180,position.y + 50 }, ImVec2{ position.x + 620,position.y + 600 }, ImColor(20 / 255.f, 20 / 255.f, 20 / 255.f, 255 / 255.f), 4, ImDrawCornerFlags_BotRight);
        draw->AddLine(ImVec2{ position.x + 180,position.y }, ImVec2{ position.x + 180,position.y + 600 }, ImColor(120 / 255.f, 120 / 255.f, 120 / 255.f, 70.f / 255.f));
        draw->AddLine(ImVec2{ position.x,position.y + 50 }, ImVec2{ position.x + 620,position.y + 50 }, ImColor(120 / 255.f, 120 / 255.f, 120 / 255.f, 70.f / 255.f));


        draw->AddLine(ImVec2{ position.x + 200,position.y + 90 }, ImVec2{ position.x + 550,position.y + 90 }, ImColor(120 / 255.f, 120 / 255.f, 120 / 255.f, 100.f / 255.f));

        draw->AddText({ position.x + 20,position.y + 70 }, ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), "FEATURES");
        draw->AddText({ position.x + 20,position.y + 210 }, ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), "INFORMATION");

        ImGui::PushFont(CustomGUI::fonts::SFUIbold_bigger);
        draw->AddText({ position.x + 20,position.y + 50 / 2 - ImGui::CalcTextSize("AnarchyProject").y / 2 }, ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), "AnarchyProject ");
        ImGui::PopFont();

        static int page = 0;
        static int subtab = 0;
        ImGui::PushFont(Overlay::fontMenu);
        ImGui::SetCursorPos({ 20, 90 });
        if (CustomGUI::Tab("Aimbot", "1", page == 0, { 140,25 }))
            page = 0;

        ImGui::SetCursorPos({ 20, 120 });
        if (CustomGUI::Tab("Visuals", "2", page == 1, { 140,25 }))
            page = 1;

        ImGui::SetCursorPos({ 20, 150 });
        if (CustomGUI::Tab("Misc", "3", page == 2, { 140,25 }))
            page = 2;

        ImGui::SetCursorPos({ 20, 180 });
        if (CustomGUI::Tab("Settings", "4", page == 3, { 140,25 }))
            page = 3;

        ImGui::SetCursorPos({ 20, 230 });
        if (CustomGUI::Tab("Dashboard", "a", page == 4, { 140,25 }))
            page = 4;

        if (page == 0)
        {
            ImGui::SetCursorPos({ 200, 66 });
            if (CustomGUI::SubTab("AIMBOT", subtab == 0, { 63,25 }))
                subtab = 0;
        }
        if (page == 1)
        {
            ImGui::SetCursorPos({ 200, 66 });
            if (CustomGUI::SubTab("ESP", subtab == 0, { 41,25 }))
                subtab = 0;

            ImGui::SetCursorPos({ 246, 66 });
            if (CustomGUI::SubTab("ESP Object List", subtab == 1, { 91,25 }))
                subtab = 1;

            ImGui::SetCursorPos({ 330, 66 });
            if (CustomGUI::SubTab("COLORS", subtab == 2, { 62,25 }))
                subtab = 2;
        }
        if (page == 2)
        {
            ImGui::SetCursorPos({ 200, 66 });
            if (CustomGUI::SubTab("Weapon Options", subtab == 0, { 100,25 }))
                subtab = 0;

            ImGui::SetCursorPos({ 300, 66 });
            if (CustomGUI::SubTab("Player Options", subtab == 1, { 100,25 }))
                subtab = 1;
        }
        if (page == 4) {
            ImGui::SetCursorPos({ 200, 66 });
            if (CustomGUI::SubTab("NEWS", subtab == 0, { 55,25 }))
                subtab = 0;
        }
        {
            ImGui::SetCursorPos({ 200, 100 });
            ImGui::BeginChild("", ImVec2(580, 500));
            {
                if (page == 0)
                {
                    if (subtab == 0)
                    {
                        CustomGUI::Checkbox("Enable Aimbot", &Settings::enableAimbot);
                        ImGui::Text("Aimbot Key"); ImGui::SameLine(); ImGui::Hotkey("##Aimbot Key", &Settings::aimbotKey, ImVec2(80, 15));

                        ImGui::Spacing();
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 18);
                        ImGui::Spacing();
                        CustomGUI::SliderInt("Aimbot FOV", &Settings::aimbotFov, 0, 360, "%.1f");

                        CustomGUI::Checkbox("Enable Distance", &Settings::enableAimbotDistance);
                        CustomGUI::SliderInt("Aimbot Distance", &Settings::aimbotDistance, 0, 300, "%.1f");

                        ImGui::PushItemWidth(ImGui::GetWindowWidth() - 340);
                        ImGui::Spacing();
                        const char* listbox_items[] = { "Head", "Chest", "Pevlis" };
                        ImGui::ListBox("##Hitbox", &Settings::aimbotHitbox, listbox_items, IM_ARRAYSIZE(listbox_items));
                        CustomGUI::Checkbox("ThickBullet", &Settings::thickBullettt);

                    }
                }
                if (page == 1)
                {
                    if (subtab == 0)
                    {
                        CustomGUI::Checkbox("Enable Visuals", &Settings::enableVisuals);
                        ImGui::Spacing();

                        CustomGUI::Checkbox(("Player Box"), &Settings::drawBox);
                        if (Settings::drawBox) {
                            CustomGUI::Combo(("Box Type"), &Settings::typeBox, boxTypes, 3);
                            CustomGUI::SliderInt(("Box Type distance"), &Settings::boxDistance, 100, 300, "%.1f");
                        }

                        CustomGUI::Checkbox(("Weapon ESP"), &Settings::drawWeapon);
                        if (Settings::drawWeapon)
                            CustomGUI::SliderInt(("Weapon Distance"), &Settings::weaponDistance, 100, 300, "%.1f");

                        CustomGUI::Checkbox(("Skeleton"), &Settings::drawSkeleton);
                        if (Settings::drawSkeleton)
                            CustomGUI::SliderInt(("Skeleton distance"), &Settings::skeletonDistance, 100, 300, "%.1f");


                        CustomGUI::Checkbox(("Name"), &Settings::drawName);
                        if (Settings::drawName)
                            CustomGUI::SliderInt(("Name distance"), &Settings::nameDistance, 100, 300, "%.1f");

                        CustomGUI::Checkbox(("Health Bar"), &Settings::drawHealthBar);
                        if (Settings::drawHealthBar)
                            CustomGUI::SliderInt(("Health Bar distance"), &Settings::healthDistance, 100, 300, "%.1f");

                        CustomGUI::Checkbox(("Dropped Items"), &Settings::enableDroppedItem);
                        if (Settings::enableDroppedItem)
                            CustomGUI::SliderInt(("Dropped Items distance"), &Settings::enableDroppedItemDistance, 100, 300, "%.1f");

                        CustomGUI::Checkbox(("Crosshair"), &Settings::drawCrosshair);
                        if (Settings::drawCrosshair)
                        {
                            CustomGUI::Checkbox("while scoped", &Settings::crosshairScoped);
                            CustomGUI::SliderInt("Length", &Settings::CrosshairLength, 1, 24, "%.1f");
                            CustomGUI::SliderInt("Gap", &Settings::CrosshairGap, 0, 24, "%.1f");
                            CustomGUI::SliderInt("Thickness", &Settings::CrosshairThickness, 1, 24, "%.1f");
                        }

                        CustomGUI::SliderInt(("Fov Changer"), &Settings::FovSlider, 75, 150, "%.1f");

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
                        CustomGUI::Checkbox(("Rapid Fire"), &Settings::rapidFire);
                        if (Settings::rapidFire)
                        {
                            CustomGUI::SliderFloat(("Rapid Fire Value"), &Settings::rapidfirevalue, 0.01, 0.09, safe_str("%.2f"), 1);
                        }
                        CustomGUI::Checkbox(("Enable RCS"), &Settings::enableRCS);
                        if (Settings::enableRCS)
                        {
                            CustomGUI::SliderInt(("RCS Percentage X"), &Settings::RCSyaw, 0, -50, "%.0f");
                            CustomGUI::SliderInt(("RCS Percentage Y"), &Settings::RCSpitch, 0, -50, "%.0f");
                        }
                        CustomGUI::Checkbox(("No Spread"), &Settings::noSpread);
                        CustomGUI::Checkbox(("Instant Compound"), &Settings::instantCompound);
                        CustomGUI::Checkbox(("Instant Switch"), &Settings::fastSwitchWeapons);
                        CustomGUI::Checkbox(("instant eoka"), &Settings::tapeoka);

                        ImGui::Spacing();
                    }
                    if (subtab == 1)
                    {
                        CustomGUI::Checkbox(("Spider Climb"), &Settings::spiderClimb);
                        CustomGUI::Checkbox(("ar"), &Settings::fly);

                        CustomGUI::Checkbox(("Fast Kill"), &Settings::fastKill);
                        if (Settings::fastKill)
                        {
                           // ImGui::SameLine();
                            ImGui::Hotkey(("##fast Kill Key"), &Settings::fastKillKey, ImVec2(80, 15));
                        }

                        CustomGUI::Checkbox(("admin flag"), &Settings::adminFlag);
                        CustomGUI::Checkbox(("Time Changer"), &Settings::night_mode);
                        if (Settings::night_mode)
                            ImGui::SliderFloat(("Time"), &Settings::time, 0, 24);

                        CustomGUI::Checkbox("Sky Color", &Settings::skyColorBool);
                        if (Settings::skyColorBool)
                            ImGui::SliderFloat("color", &Settings::SkyColor, 0, 100);


                        CustomGUI::Checkbox(("Long Hit"), &Settings::longhit);
                        CustomGUI::Checkbox(("third person"), &Settings::thirdperson);
                        CustomGUI::Checkbox(("Long Neck"), &Settings::shootInAir);
                        if (Settings::shootInAir)
                        {
                            // ImGui::SameLine();
                            ImGui::Hotkey(("##Long Neck Key"), &Settings::LongNeckKey, ImVec2(80, 15));
                        }
                        CustomGUI::Checkbox("High Jump", &Settings::SuperJump);
                        if (Settings::SuperJump)
                        {
                            CustomGUI::SliderFloat("value", &Settings::GravitySlider, 2.8, 0, "%.1f", 1);
                        }
                        CustomGUI::Checkbox("Hold Items While Mounted", &Settings::ShootMounted);
                        CustomGUI::Checkbox("Speed Hack", &Settings::SpeedHack);
                        if (Settings::SpeedHack)
                        {
                            ImGui::Hotkey(("##Speed Hack Key"), &Settings::SpeedHackKey, ImVec2(80, 15));
                            CustomGUI::SliderFloat("Speed", &Settings::SpeedHackSpeed, 10, -10, "%.2f", 0.47);
                        }
                        CustomGUI::Checkbox(("Bright Night"), &Settings::nightSky);
                        CustomGUI::Checkbox(("Run Hit"), &Settings::runhit);
                        CustomGUI::Checkbox(("Zoom"), &Settings::zoom);
                        if (Settings::zoom)
                        {
                            ImGui::Hotkey(("##Zoom Key"), &Settings::zoomKey, ImVec2(80, 15));
                        }
                        CustomGUI::Checkbox("FlyHack", &Settings::flyHackkk);
                        if (Settings::flyHackkk)
                        {
                            ImGui::Hotkey("##Flyhack Key", &Settings::flyhackKey, ImVec2(80, 15));
                            CustomGUI::SliderFloat(("speed"), &Settings::flyhackSpeed, 6, -5, "%.0f", 1);
                        }
                        CustomGUI::Checkbox(("Jesus mode"), &Settings::walkOnWater);
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
                        if (ImGui::Button("EXIT CHEAT"))
                            exit(-1);
                        if (ImGui::Button("Load admin Config"))
                            configSam();
                    }
                }
                if (page == 4)
                {
                    static int subtab = 0;
                    if (subtab == 0)
                    {
                        CustomGUI::News("Release", AutherLibrary::GetFullJsonResponse().c_str());
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
    ImGui::SetNextWindowSize(ImVec2(screenWidth + 15, screenHeight + 15));
    ImGui::SetNextWindowPos(ImVec2(-10, -10));
    ImGui::SetNextWindowBgAlpha(255.f);

    //Window Size
    ImGui::SetNextWindowSize(ImVec2(300, 200)); //800, 550
    ImGui::SetNextWindowPos(ImVec2((1920 - 840) * .5, (1080 - 500) * .5), ImGuiCond_Once);

    ImGui::Text("Enter your key:");
    ImGui::InputText("Key: ",globals.key ,IM_ARRAYSIZE(globals.key));
    if (ImGui::Button("Login")) {
        if (AutherLibrary::Auth(globals.key, AutherLibrary::GetHwid()))
        {
            MessageBox(NULL, "uspeshno", "Logged", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
            globals.auth = true;
        }
        else
        {
            exit(0);
        }
    }
}
