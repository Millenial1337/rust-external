#pragma once
#include "../../SDK/Classes.hpp"
#include "../../Overlay/Overlay.hpp"
#include "../../Overlay/Menu/Settings.hpp"
#include "../../SDK/BasePlayer.hpp"
#include "../Aimbot/DoAimbot.hpp"
#include "DrawESP.hpp"
#include <array>
#include <future>
#include <time.h>

using namespace std::string_literals;

namespace ESP {

	void __fastcall Run() {


		struct Colors
		{
			Color Red = D3DCOLOR_RGBA(255, 0, 0, 255);
			Color Orange = D3DCOLOR_RGBA(255, 100, 0, 255);
			Color Yellow = D3DCOLOR_RGBA(255, 255, 0, 255);
			Color Green = D3DCOLOR_RGBA(0, 255, 0, 255);
			Color Turquoise = D3DCOLOR_RGBA(0, 255, 255, 255);
			Color Blue = D3DCOLOR_RGBA(0, 130, 255, 255);
			Color Purple = D3DCOLOR_RGBA(130, 0, 255, 255);
			Color Pink = D3DCOLOR_RGBA(255, 0, 255, 255);
			Color Black = D3DCOLOR_RGBA(0, 0, 0, 255);
			Color Gray = D3DCOLOR_RGBA(69, 69, 69, 255);
			Color White = D3DCOLOR_RGBA(255, 255, 255, 255);
		};
		Colors ColorClass;

		//uintptr_t gomPtr = Read<uintptr_t>(uBase + 0x17C1F18); //game object manager | Chain + 0x17C1F18 -> 0x8 -> 0x10 -> 0x30 -> 0x18 -> 0x2E4
		//uintptr_t taggedObjects = Read<uintptr_t>(gomPtr + 0x8);
		//uintptr_t gameObject = Read<uintptr_t>(taggedObjects + 0x10);
		//uintptr_t objectClass = Read<uintptr_t>(gameObject + 0x30);
		//uintptr_t entity = Read<uintptr_t>(objectClass + 0x18);
		//Old, maybe broken

		//pViewMatrix = Read<Matrix4x4>(entity + 0x2E4); //camera

		uintptr_t cmptr = Read<uintptr_t>(uBase + 0x1762E80); //0x1762F40 qword_181762E80 qword_181762F40
		uintptr_t camera_manager = Read<uintptr_t>(cmptr);
		uintptr_t camera = Read<uintptr_t>(camera_manager);
		uintptr_t camera_object = Read<uintptr_t>(camera + 0x30);
		uintptr_t object_class = Read<uintptr_t>(camera_object + 0x30);
		uintptr_t entity = Read<uintptr_t>(object_class + 0x18);
		pViewMatrix = Read<Matrix4x4>(entity + 0x2E4);

		if (Settings::watermark)
		{
			//time_t current_time;
			//struct tm* time_info;
			//char timeString[9];  // space for "HH:MM:SS\0"

			//time(&current_time);
			//time_info = localtime(&current_time);

			//strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
			//puts(timeString);

			//Render::Text(ImVec2( 2, 2 ), timeString, ImColor(255, 204, 229, 255), false, Overlay::fontTitle, 13);

			ImDrawList* draw = ImGui::GetOverlayDrawList();

			draw->AddRectFilled(ImVec2(15, 10), ImVec2(20, 25), ImColor(172, 142, 184, 255));
			draw->AddRectFilled(ImVec2(20, 10), ImVec2(70, 25), ImColor(17, 18, 17, 255));
			draw->AddText(ImVec2(22, 10), ImColor(255, 255, 255, 255), "a-p.fun");
		}

		//Render::Text(ImVec2(2, 2), "AnarchyProject", ImColor(204, 153 ,255, 255), true, Overlay::fontMenu, 15);
		Render::Text(ImVec2(1, GetSystemMetrics(SM_CYSCREEN) - 10), "By anarchydev", ImColor(204, 153, 255, 255), false, Overlay::fontMenu, 10);
		if (Settings::enableVisuals)
		{
			if (Settings::drawCrosshair)
				DrawCrosshair();

			if (Settings::enableAimbot)
				Render::Circle(ImVec2(screenWidth / 2, screenHeight / 2), Settings::aimbotFov, ImColor(255, 255, 255));

			std::unique_ptr<std::vector<BaseEntity>> local_players = std::make_unique<std::vector<BaseEntity>>();
			std::unique_ptr<std::vector<EntityCorpse>> local_corpse = std::make_unique<std::vector<EntityCorpse>>();
			std::unique_ptr<std::vector<BaseMiscEntity>> local_ore = std::make_unique<std::vector<BaseMiscEntity>>();
			std::unique_ptr<std::vector<BaseWeaponESP>> local_weapon = std::make_unique<std::vector<BaseWeaponESP>>();

			Mutex->PlayerSync->lock();
			*local_players = *entityList;
			*local_corpse = *corpseList;
			*local_ore = *oreList;
			*local_weapon = *weaponList;
			Mutex->PlayerSync->unlock();

			for (unsigned long i = 0; i < local_ore->size(); ++i) {
				std::unique_ptr<BaseMiscEntity> curOre = std::make_unique<BaseMiscEntity>(local_ore->at(i));
				auto position = Read<Vector3>(curOre->trans + 0x90);//world position = 0x90
				auto distance = (int)Math::Distance(&localPlayer->Player->position, &position);
				if (distance < 200)
				{
					Vector2 pos;

					std::string nameStr = curOre->name;
					std::string distanceStr = std::to_string(distance) + "m";


					if (!Utils::WorldToScreen(position, pos)) continue;
					auto text_size = ImGui::CalcTextSize(nameStr.c_str());
					auto text_sizeDistance = ImGui::CalcTextSize(distanceStr.c_str());
					//auto text_sizeDistance = ImGui::CalcTextSize(distanceStr.c_str());


					static float screenX = GetSystemMetrics(SM_CXSCREEN);
					static float screenY = GetSystemMetrics(SM_CYSCREEN);
					ImU32 color = Render::FtIM(Settings::espColorMisc);
					//Render::DrawCornerBox(ImVec2(pos.x - 7, pos.y - 10), ImVec2(10, 10), color);
					Render::Text(ImVec2(pos.x - text_size.x / 2, pos.y + 12 - text_size.y), nameStr, color, true, Overlay::playerName, Overlay::playerName->FontSize);
					Render::Text(ImVec2(pos.x - text_sizeDistance.x / 2, pos.y + 21 - text_sizeDistance.y), distanceStr, color, true, Overlay::playerName, Overlay::playerName->FontSize);
				}
			}
			
			for (unsigned long i = 0; i < local_weapon->size(); ++i) {
				std::unique_ptr<BaseWeaponESP> curOre = std::make_unique<BaseWeaponESP>(local_weapon->at(i));
				auto position = Read<Vector3>(curOre->trans + 0x90);//world position = 0x90
				auto distance = (int)Math::Distance(&localPlayer->Player->position, &position);
				if (distance < Settings::enableDroppedItemDistance)
				{
					Vector2 pos;

					std::string nameStr = curOre->name;
					std::string distanceStr = std::to_string(distance) + "m";


					if (!Utils::WorldToScreen(position, pos)) continue;
					auto text_size = ImGui::CalcTextSize(nameStr.c_str());
					auto text_sizeDistance = ImGui::CalcTextSize(distanceStr.c_str());


					static float screenX = GetSystemMetrics(SM_CXSCREEN);
					static float screenY = GetSystemMetrics(SM_CYSCREEN);
					ImU32 color = Render::FtIM(Settings::DroppedItemCol);
					if (Settings::enableDroppedItem && distance <= Settings::weaponDistance)
					{
						Render::Text(ImVec2(pos.x - text_size.x / 2, pos.y + 12 - text_size.y), nameStr, color, true, Overlay::playerName, Overlay::playerName->FontSize);
						Render::Text(ImVec2(pos.x - text_sizeDistance.x / 2, pos.y + 21 - text_sizeDistance.y), distanceStr, color, true, Overlay::playerName, Overlay::playerName->FontSize);
					}
				}
			}

			for (unsigned long i = 0; i < local_corpse->size(); ++i) {
				std::unique_ptr<EntityCorpse> curCorpse = std::make_unique<EntityCorpse>(local_corpse->at(i));

				auto position = Read<Vector3>(curCorpse->trans + 0x90);//world position
				auto distance = (int)Math::Distance(&localPlayer->Player->position, &position);
				Vector2 pos;

				if (curCorpse->name.find("player/player_corpse") != std::string::npos || curCorpse->name.find("item drop/item_drop_backpack") != std::string::npos) {

					std::string nameStr = "CORPSE";
					std::string distanceStr = std::to_string(distance) + "m";

					if (!Utils::WorldToScreen(position, pos)) continue;

					auto text_size = ImGui::CalcTextSize(nameStr.c_str());
					ImU32 color = Render::FtIM(Settings::espColorMisc);
					if (Settings::selectedOres[22] && distance < 100)
					{
						static float screenX = GetSystemMetrics(SM_CXSCREEN);
						static float screenY = GetSystemMetrics(SM_CYSCREEN);
						//Render::DrawCornerBox(ImVec2(pos.x - 7, pos.y - 10), ImVec2(10, 10), ImColor(255, 255, 255));
						//Render::Line2(ImVec2(screenX / 2, screenY / 2), ImVec2(pos.x - 2, pos.y - 2), ImColor(255, 255, 255), 1.5f);
						Render::Text(ImVec2(pos.x - text_size.x / 2, pos.y + 12 - text_size.y), nameStr, color, true, Overlay::playerName, Overlay::playerName->FontSize);
					}
				}
			}

			Vector2 pos;
			for (unsigned long i = 0; i < local_players->size(); ++i)
			{
				std::unique_ptr<BaseEntity> curEntity = std::make_unique<BaseEntity>(local_players->at(i));

				Vector2 pos;
				auto position = Read<Vector3>(curEntity->visualState + 0x90);//world position
				if (!Utils::WorldToScreen(position, pos)) continue;
				if (Settings::snapLinez)
				{
					static float screenX = GetSystemMetrics(SM_CXSCREEN);
					static float screenY = GetSystemMetrics(SM_CYSCREEN);
					Render::Line2(ImVec2(screenX / 2, screenY / 2), ImVec2(pos.x - 2, pos.y - 2), ImColor(255, 255, 255), 1.5f);
				}

				auto distance = (int)Math::Distance(&localPlayer->Player->position, &curEntity->position);

				if (curEntity->isLocalPlayer()) continue;

				if (!curEntity->IsInView()) continue;

				if (curEntity->health < 0.00f) continue;

				if (curEntity->isDead()) continue;

				if (Settings::drawSkeleton && distance < Settings::skeletonDistance)
					DrawSkeleton(curEntity->player);

				

				if (Settings::drawBox && distance < Settings::boxDistance)
					DrawBox(curEntity->player, curEntity->isSameTeam(localPlayer->Player));

				if (Settings::drawName && distance < Settings::nameDistance)
					DrawPlayerName(curEntity->player, curEntity->getName(), distance, curEntity->isSameTeam(localPlayer->Player));

				if (Settings::drawWeapon && distance < Settings::weaponDistance && curEntity->getHeldItem().IsWeapon())
					DrawPlayerWeapon(curEntity->player, curEntity->getHeldItem().GetItemName());

				if (Settings::drawHealthBar && distance < Settings::healthDistance)
					DrawHealthBar(curEntity->player, curEntity->health);
			}
		}
	}
}