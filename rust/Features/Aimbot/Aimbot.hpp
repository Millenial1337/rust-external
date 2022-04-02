#pragma once
#include "../../SDK/Classes.hpp"
#include "../../Overlay/Menu/Settings.hpp"
#include "../../SDK/BasePlayer.hpp"

namespace Aimbot {
	std::map<std::string, float> BulletSpeeds = {
		{ std::string("ammo.rifle"), 1.0f },
		{ std::string("ammo.rifle.hv"), 1.2f },
		{ std::string("ammo.rifle.explosive"), 0.6f },
		{ std::string("ammo.rifle.incendiary"), 0.6f },

		{ std::string("ammo.pistol"), 1.0f },
		{ std::string("ammo.pistol.hv"), 1.33333f },
		{ std::string("ammo.pistol.incendiary"), 0.75f },

		{ std::string("arrow.wooden"), 1.0f },
		{ std::string("arrow.hv"), 1.6f },
		{ std::string("arrow.fire"), 0.8f },
		{ std::string("arrow.bone"), 0.9f },

		{ std::string("ammo.handmade.shell"), 1.0f },
		{ std::string("ammo.shotgun.slug"), 2.25f },
		{ std::string("ammo.shotgun.fire"), 1.0f },
		{ std::string("ammo.shotgun"), 2.25f },

		{ std::string("ammo.nailgun.nails"), 1.0f }
	};


	float ProjectileSpeed_Normal() {
		std::string held_item = localPlayer->Player->getHeldItem().GetItemName();
		float Ammunition_Multiplier = BulletSpeeds[localPlayer->Player->getHeldItem().GetAmmoType()];

		if (held_item == "No Item")                 return 300.0f;

		if (held_item == "rifle.ak")                return 375.0f * Ammunition_Multiplier;
		if (held_item == "rifle.lr300")             return 375.0f * Ammunition_Multiplier;
		if (held_item == "rifle.bolt")              return 656.0f * Ammunition_Multiplier;
		if (held_item == "rifle.l96")               return 1125.0f * Ammunition_Multiplier;
		if (held_item == "rifle.m39")               return 469.0f * Ammunition_Multiplier;
		if (held_item == "rifle.semiauto")          return 375.0f * Ammunition_Multiplier;

		if (held_item == "lmg.m249")                return 488.0f * Ammunition_Multiplier;

		if (held_item == "smg.thompson")            return 300.0f * Ammunition_Multiplier;
		if (held_item == "smg.custom")              return 240.0f * Ammunition_Multiplier;
		if (held_item == "smg.mp5")                 return 240.0f * Ammunition_Multiplier;

		if (held_item == "pistol.python")           return 300.0f * Ammunition_Multiplier;
		if (held_item == "pistol.semi")             return 300.0f * Ammunition_Multiplier;
		if (held_item == "pistol.revolver")         return 300.0f * Ammunition_Multiplier;
		if (held_item == "pistol.m92")              return 300.0f * Ammunition_Multiplier;
		if (held_item == "pistol.eoka")             return 100.0f * Ammunition_Multiplier;
		if (held_item == "pistol.nailgun")          return 50.0f;

		if (held_item == "crossbow")               return 75.0f * Ammunition_Multiplier;
		if (held_item == "bow.compound")            return 100.0f * Ammunition_Multiplier;
		if (held_item == "bow.hunting")             return 50.0f * Ammunition_Multiplier;

		if (held_item == "shotgun.pump")            return 100.0f * Ammunition_Multiplier;
		if (held_item == "shotgun.spas12")          return 100.0f * Ammunition_Multiplier;
		if (held_item == "shotgun.waterpipe")       return 100.0f * Ammunition_Multiplier;
		if (held_item == "shotgun.doublebarrel")    return 100.0f * Ammunition_Multiplier;

		return 300.0f;
	}

	float AimFov(std::unique_ptr<BaseEntity>& BPlayer, BonesList bone)
	{
		Vector2 ScreenPos;
		if (!Utils::WorldToScreen(Utils::GetBonePosition(BPlayer->player, bone), ScreenPos)) return 1000.f;
		return Math::Calc2D_Dist(Vector2(screenWidth / 2, screenHeight / 2), ScreenPos);
	}

	/*Vector3 Prediction(const Vector3& LP_Pos, std::unique_ptr<BaseEntity>& Player, BonesList Bone) {
		Vector3 BonePos = Utils::GetBonePosition(Player->player, Bone);
		float Dist = Math::Calc3D_Dist(LP_Pos, BonePos);

		if (Dist > 0.001f) {
			float BulletTime = Dist / ProjectileSpeed_Normal();
			Vector3 vel = Player->getNewVelocity() * 0.75f;
			Vector3 PredictVel = vel * BulletTime;
			BonePos += PredictVel; BonePos.y += (4.905f * BulletTime * BulletTime);
		} return BonePos;
	}*/

	Vector3 Prediction(const Vector3& LP_Pos, std::unique_ptr<BaseEntity>& Player, BonesList Bone)
	{
		Vector3 BonePos = Utils::GetBonePosition(Player->player, Bone);
		float Dist = Math::Calc3D_Dist(LP_Pos, BonePos);

		if (Dist > 0.001f) {
			float BulletTime = Dist / ProjectileSpeed_Normal();
			//    std::cout << GetBulletSpeed() << endl;
			Vector3 vel = Player->getNewVelocity();
			Vector3 PredictVel;
			PredictVel.x = vel.x * BulletTime * 0.75f;
			PredictVel.y = vel.y * BulletTime * 0.75f;
			PredictVel.z = vel.z * BulletTime * 0.75f;

			BonePos.x += PredictVel.x;
			BonePos.y += PredictVel.y;
			BonePos.z += PredictVel.z;
			BonePos.y += (4.905f * BulletTime * BulletTime);
			//BonePos += PredictVel; BonePos.y += (4.905f * BulletTime * BulletTime);
		} return BonePos;
	}

	void Normalize(float& Yaw, float& Pitch) {
		if (Pitch < -89) Pitch = -89;
		else if (Pitch > 89) Pitch = 89;
		if (Yaw < -360) Yaw += 360;
		else if (Yaw > 360) Yaw -= 360;
	}

	void SmoothAim(Vector2& Angle) {
		Angle.x /= Settings::aimbotSmoothing;
		Angle.y /= Settings::aimbotSmoothing;
	}


	void newSmoothing(Vector2& Angle, float smooth)
	{
		Angle.x /= smooth;
		Angle.y /= smooth;
	}

	void AimbotTarget(std::unique_ptr<BaseEntity>& BPlayer, BonesList Bone) {
		Vector3 Local = Utils::GetBonePosition(localPlayer->Player->player, BonesList::neck);
		Vector3 PlayerPos = Prediction(Local, BPlayer, Bone);


		Vector2 recoil_angles = Vector2{ localPlayer->Player->getRecoilAngles().x, localPlayer->Player->getRecoilAngles().y };



		Vector2 AngleToAim = Math::CalcAngle(Local, PlayerPos);
		Normalize(AngleToAim.y, AngleToAim.x);
		if (isnan(AngleToAim.x) || isnan(AngleToAim.y))
			return;



		if (Settings::enableSmoothing) {
			AngleToAim -= Vector2{ localPlayer->Player->getViewAngles().x, localPlayer->Player->getViewAngles().y };
			newSmoothing(AngleToAim, Settings::aimSmoothing);
			AngleToAim += Vector2{ localPlayer->Player->getViewAngles().x, localPlayer->Player->getViewAngles().y };
		}

		localPlayer->Player->setViewAngles(AngleToAim);
	}
}
