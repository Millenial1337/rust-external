#pragma once
#include "ESP.hpp"

namespace ESP {
	void __fastcall DrawSkeleton(uint64_t player) {
		std::array<BonesList, 15> Bones = {
			r_foot, l_knee, l_hip,
			l_foot, r_knee, r_hip,
			spine1, neck, head,
			l_upperarm, l_forearm, l_hand,
			r_upperarm, r_forearm, r_hand
		}; std::array<Vector2, Bones.size()> BonesPos;

		for (int i = 0; i < BonesPos.size(); ++i) {
			if (!(Utils::WorldToScreen(Utils::GetBonePosition(player, Bones[i]), BonesPos.at(i)))) continue;
		}

		for (int j = 0; j < BonesPos.size(); j += 3) {
			Render::Line({ BonesPos[j].x, BonesPos[j].y }, { BonesPos[j + 1].x, BonesPos[j + 1].y }, Render::FtIM(Settings::drawColor_skeleton), 1.0f);
			Render::Line({ BonesPos[j + 1].x, BonesPos[j + 1].y }, { BonesPos[j + 2].x, BonesPos[j + 2].y }, Render::FtIM(Settings::drawColor_skeleton), 1.0f);
		}

		Render::Line({ BonesPos[2].x, BonesPos[2].y }, { BonesPos[6].x, BonesPos[6].y }, Render::FtIM(Settings::drawColor_skeleton), 1.0f);
		Render::Line({ BonesPos[5].x, BonesPos[5].y }, { BonesPos[6].x, BonesPos[6].y }, Render::FtIM(Settings::drawColor_skeleton), 1.0f);
		Render::Line({ BonesPos[9].x, BonesPos[9].y }, { BonesPos[7].x, BonesPos[7].y }, Render::FtIM(Settings::drawColor_skeleton), 1.0f);
		Render::Line({ BonesPos[12].x, BonesPos[12].y }, { BonesPos[7].x, BonesPos[7].y }, Render::FtIM(Settings::drawColor_skeleton), 1.0f);
	}

	void __fastcall DrawBox(uint64_t player, bool isSameTeam) {
		Vector3 head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.2, 0));
		Vector3 feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
		Vector2 tempFeet, tempHead;

		ImU32 color = Render::FtIM(Settings::drawColor_box);

		if (Utils::WorldToScreen(head, tempHead) && Utils::WorldToScreen(feet, tempFeet)) {
			float height = (tempHead.y - tempFeet.y);
			float width = height / 4.0f;

			float Entity_x = tempFeet.x - width;
			float Entity_y = tempFeet.y;
			float Entity_w = height / 2;

			if (isSameTeam) color = Render::FtIM(Settings::drawColor_friendly);

			switch (Settings::typeBox) {
			case 0:	Render::DrawBox(ImVec2(Entity_x, Entity_y), ImVec2(Entity_w, height), color); break;
			case 1: Render::DrawCornerBox(ImVec2(Entity_x, Entity_y), ImVec2(Entity_w, height), color); break;
			case 2: Render::DrawFilledBox(ImVec2(Entity_x, Entity_y), ImVec2(Entity_w, height), color); break;
			}
		}
	}

	void _fastcall DrawHealthBar(uint64_t player, float health) {
		Vector3 head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.2, 0));
		Vector3 feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
		Vector2 tempFeet, tempHead;
		if (Utils::WorldToScreen(head, tempHead) && Utils::WorldToScreen(feet, tempFeet)) {
			float height = (tempHead.y - tempFeet.y);
			float width = height / 4.0f;

			float Entity_x = tempFeet.x - width;
			float Entity_y = tempFeet.y;
			float flBoxes = std::ceil(health / 10.f);
			float flX = Entity_x + 4; float flY = Entity_y;
			float flHeight = height / 10.f;
			float flMultiplier = 12 / 360.f; flMultiplier *= flBoxes - 1;
			Color ColHealth = Color::FromHSB(flMultiplier, 1, 1);

			Render::Text(ImVec2(flX, flY), std::to_string((int)health), ImColor(255, 255, 255, 255), true, Overlay::playerName);

			Render::DrawFilledRect(flX + 1, flY, 2, flHeight * flBoxes + 1, ImColor(ColHealth.R, ColHealth.G, ColHealth.B, ColHealth.A));
			Render::DrawFilledRect(flX, flY, 4, height + 2, ImColor(80, 80, 80, 160));
			for (int i = 0; i < 10; i++)
				Render::Line(ImVec2(flX, flY + i * flHeight), ImVec2(flX + 4, flY + i * flHeight), ImColor(0,0,0,255), 1.5f);
		}
	}

	void _fastcall DrawPlayerName(uint64_t player, std::string buffer, int distance, bool sameTeam) {
		Vector3 Head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.23, 0));
		Vector3 Feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
		Vector2 tempFeet;
		Vector2 tempHead;

		wchar_t res[256];
		std::string full_str = buffer + " - " + std::to_string(distance) + "m";

		if (Utils::WorldToScreen(Feet, tempFeet) && Utils::WorldToScreen(Head, tempHead)) {
			auto text_size = ImGui::CalcTextSize(full_str.c_str());
			if(sameTeam)
				Render::Text(ImVec2(tempFeet.x - text_size.x / 2, tempHead.y - text_size.y), full_str, Render::FtIM(Settings::drawColor_friendly), true, Overlay::playerName);
			else
			Render::Text(ImVec2(tempFeet.x - text_size.x / 2, tempHead.y - text_size.y), full_str, Render::FtIM(Settings::drawColor_name), true, Overlay::playerName);
		}
	}

	void _fastcall DrawPlayerWeapon(uint64_t player, std::string buffer)
	{
		Vector3 Head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.23, 0));
		Vector3 Feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
		Vector2 tempFeet;

		wchar_t res[256];
		if (Utils::WorldToScreen(Feet, tempFeet)) {
			auto text_size = ImGui::CalcTextSize(buffer.c_str());
			Render::Text(ImVec2(tempFeet.x - text_size.x / 2, (tempFeet.y + 15)- text_size.y), buffer, Render::FtIM(Settings::drawColor_weapon), true, Overlay::weaponName);
		}
	}

	void _fastcall DrawPlayerHealth(uint64_t player, float health) {
		Vector3 Head = (Utils::GetBonePosition(player, BonesList::l_foot) + Vector3(0, 0.23, 0));
		Vector3 Feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
		Vector2 tempFeet;
		Vector2 tempHead;

		std::string full_str = std::to_string(health) + "hp";

		if (Utils::WorldToScreen(Feet, tempFeet) && Utils::WorldToScreen(Head, tempHead)) {
			auto text_size = ImGui::CalcTextSize(full_str.c_str());

			Render::Text(ImVec2(tempFeet.x - text_size.x / 2, tempHead.y - text_size.y), full_str, Render::FtIM(Settings::drawColor_weapon), true, Overlay::playerName);
		}
	}

	void _fastcall DrawVerticalHealth(float x, float y, float w, float h, float value, float max)
	{
		Render::DrawFilledRect(x, y, w, h, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		if (value <= 225.0f) Render::DrawFilledRect(x, y, w, value / max * h, ImVec4(0.0f, 0.502f, 1.0f, 1.0f)); // player with shield
		if (value <= 100.0f) Render::DrawFilledRect(x, y, w, value / max * h, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // health only
	}

	void _fastcall DrawCurrentWeapon(uint64_t player, std::string buffer) {
		Vector3 Feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
		Vector2 tempFeet;

		if (Utils::WorldToScreen(Feet, tempFeet)) {
			auto text_size = ImGui::CalcTextSize(buffer.c_str());

			Render::Text(ImVec2(tempFeet.x - text_size.x / 2, tempFeet.y - text_size.y), buffer, ImColor(255, 255, 255), true, Overlay::playerName);
		}
	}

	void __fastcall DrawCrosshair() {
		float MidX = screenWidth / 2;
		float MidY = screenHeight / 2;
		Render::Line({ MidX - Settings::CrosshairLength, MidY }, { MidX - Settings::CrosshairGap, MidY }, Render::FtIM(Settings::drawColor_crosshair), Settings::CrosshairThickness);
		Render::Line({ MidX, MidY - Settings::CrosshairLength }, { MidX, MidY - Settings::CrosshairGap }, Render::FtIM(Settings::drawColor_crosshair), Settings::CrosshairThickness);
		Render::Line({ MidX + Settings::CrosshairLength, MidY }, { MidX + Settings::CrosshairGap, MidY }, Render::FtIM(Settings::drawColor_crosshair), Settings::CrosshairThickness);
		Render::Line({ MidX, MidY + Settings::CrosshairLength }, { MidX, MidY + Settings::CrosshairGap }, Render::FtIM(Settings::drawColor_crosshair), Settings::CrosshairThickness);
		
		/*
		if (Settings::crosshairScoped && Settings::drawCrosshair)
		{
			Render::Line({ MidX - Settings::CrosshairLength, MidY }, { MidX - Settings::CrosshairGap, MidY }, Render::FtIM(Settings::drawColor_crosshair), Settings::CrosshairThickness);
			Render::Line({ MidX, MidY - Settings::CrosshairLength }, { MidX, MidY - Settings::CrosshairGap }, Render::FtIM(Settings::drawColor_crosshair), Settings::CrosshairThickness);
			Render::Line({ MidX + Settings::CrosshairLength, MidY }, { MidX + Settings::CrosshairGap, MidY }, Render::FtIM(Settings::drawColor_crosshair), Settings::CrosshairThickness);
			Render::Line({ MidX, MidY + Settings::CrosshairLength }, { MidX, MidY + Settings::CrosshairGap }, Render::FtIM(Settings::drawColor_crosshair), Settings::CrosshairThickness);
		}
		else if (Settings::drawCrosshair && !Scoped)
		{
			Render::Line({ MidX - Settings::CrosshairLength, MidY }, { MidX - Settings::CrosshairGap, MidY }, Render::FtIM(Settings::drawColor_crosshair), Settings::CrosshairThickness);
			Render::Line({ MidX, MidY - Settings::CrosshairLength }, { MidX, MidY - Settings::CrosshairGap }, Render::FtIM(Settings::drawColor_crosshair), Settings::CrosshairThickness);
			Render::Line({ MidX + Settings::CrosshairLength, MidY }, { MidX + Settings::CrosshairGap, MidY }, Render::FtIM(Settings::drawColor_crosshair), Settings::CrosshairThickness);
			Render::Line({ MidX, MidY + Settings::CrosshairLength }, { MidX, MidY + Settings::CrosshairGap }, Render::FtIM(Settings::drawColor_crosshair), Settings::CrosshairThickness);
		}*/

	}
}