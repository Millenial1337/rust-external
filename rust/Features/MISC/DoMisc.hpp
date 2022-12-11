#pragma once
#include "Misc.hpp"
#include "../../SDK/BasePlayer.hpp"
struct recoilProperties
{
	float recoilYawMin = 1.0f; // 0x18
	float recoilYawMax = 1.0f; // 0x1C
	float recoilPitchMin = 1.0f; // 0x20
	float recoilPitchMax = 1.0f; // 0x24
};

recoilProperties getRecoilProperties() {
	std::string held_item = localPlayer->Player->getHeldItem().GetItemName();
	recoilProperties RP;
	#pragma region rifles
	if (held_item == "rifle.ak") {
		RP.recoilYawMin = -2.0f;	RP.recoilYawMax = 8.0f;		RP.recoilPitchMin = -4.0f;	RP.recoilPitchMax = -30.0f;	return RP;
	}
	if (held_item == "rifle.lr300") {
		RP.recoilYawMin = -1.0f;	RP.recoilYawMax = 5.0f;		RP.recoilPitchMin = -2.50f;	RP.recoilPitchMax = -12.0f;	return RP;
	}
	if (held_item == "rifle.bolt") {
		RP.recoilYawMin = -4.0f;	RP.recoilYawMax = 4.0f;		RP.recoilPitchMin = -2.0f;	RP.recoilPitchMax = -3.0f;	return RP;
	}
	if (held_item == "rifle.l96") {
		RP.recoilYawMin = -2.0f;	RP.recoilYawMax = 2.0f;		RP.recoilPitchMin = -1.0f;	RP.recoilPitchMax = -1.5f;	return RP;
	}
	if (held_item == "rifle.m39") {
		RP.recoilYawMin = -1.5f;	RP.recoilYawMax = -1.5f;	RP.recoilPitchMin = -5.0f;	RP.recoilPitchMax = -7.0f;	return RP;
	}
	if (held_item == "rifle.semiauto") {
		RP.recoilYawMin = -1.0f;	RP.recoilYawMax = 1.0f;		RP.recoilPitchMin = -5.0f;	RP.recoilPitchMax = -6.0f;	return RP;
	}
	#pragma endregion

	#pragma region LMG
	if (held_item == "lmg.m249") {
		RP.recoilYawMin = -1.0f;	RP.recoilYawMax = 1.0f;		RP.recoilPitchMin = -5.0f;	RP.recoilPitchMax = -6.0f;	return RP;
	}
	#pragma endregion
	
	#pragma region SMG
	if (held_item == "smg.thompson") {
		RP.recoilYawMin = -1.5f;	RP.recoilYawMax = 10.0f;		RP.recoilPitchMin = -2.0f;	RP.recoilPitchMax = -15.0f;	return RP;
	}
	if (held_item == "smg.custom") {
		RP.recoilYawMin = -1.5f;	RP.recoilYawMax = 10.0f;	RP.recoilPitchMin = -2.0f;	RP.recoilPitchMax = -15.0f;	return RP;
	}
	if (held_item == "smg.mp5") {//REDO
		RP.recoilYawMin = -1.25f;	RP.recoilYawMax = 6.0f;		RP.recoilPitchMin = -2.0f;	RP.recoilPitchMax = 10.0f;	return RP;//redo
	}
	#pragma endregion

	#pragma region pistol
	if (held_item == "pistol.python") {
		RP.recoilYawMin = -2.0f;	RP.recoilYawMax = 2.0f;		RP.recoilPitchMin = -15.0f;	RP.recoilPitchMax = -16.0f;	return RP;
	}
	if (held_item == "pistol.semi") {//REDO
		RP.recoilYawMin = -2.0f;	RP.recoilYawMax = 2.0f;		RP.recoilPitchMin = -6.0f;	RP.recoilPitchMax = -8.0f;	return RP;
	}
	if (held_item == "pistol.revolver") {
		RP.recoilYawMin = -1.0f;	RP.recoilYawMax = 1.0f;		RP.recoilPitchMin = -5.0f;	RP.recoilPitchMax = -6.0f;	return RP;
	}
	if (held_item == "pistol.m92") {
		RP.recoilYawMin = -1.0f;	RP.recoilYawMax = 1.0f;		RP.recoilPitchMin = -3.0f;	RP.recoilPitchMax = -6.0f;	return RP;
	}
	if (held_item == "pistol.eoka") {
		RP.recoilYawMin = 0.0f;	RP.recoilYawMax = 0.0f;			RP.recoilPitchMin = 0.0f;	RP.recoilPitchMax = 0.0f;	return RP;
	}
	if (held_item == "pistol.nailgun") {
		RP.recoilYawMin = -1.0f;	RP.recoilYawMax = 1.0f;		RP.recoilPitchMin = -3.0f;	RP.recoilPitchMax = -6.0f;	return RP;
	}
	#pragma endregion

	#pragma region bows
	if (held_item == "crossbow") {
		RP.recoilYawMin = -3.25f;	RP.recoilYawMax = 3.0f;		RP.recoilPitchMin = -3.0f;	RP.recoilPitchMax = -6.0f;	return RP;
	}
	if (held_item == "bow.compound") {
		RP.recoilYawMin = -3.25f;	RP.recoilYawMax = 3.0f;		RP.recoilPitchMin = -3.0f;	RP.recoilPitchMax = -6.0f;	return RP;
	}
	if (held_item == "bow.hunting") {
		RP.recoilYawMin = -3.25f;	RP.recoilYawMax = 3.0f;		RP.recoilPitchMin = -3.0f;	RP.recoilPitchMax = -6.0f;	return RP;
	}
	#pragma endregion

	#pragma region shotguns
	if (held_item == "shotgun.pump") {//redo
		RP.recoilYawMin = 4.0f;	RP.recoilYawMax = 8.0f;		RP.recoilPitchMin = -10.0f;	RP.recoilPitchMax = -14.0f;	return RP;
	}
	if (held_item == "shotgun.spas12") {
		RP.recoilYawMin = 4.0f;	RP.recoilYawMax = 8.0f;		RP.recoilPitchMin = -10.0f;	RP.recoilPitchMax = -14.0f;	return RP;
	}
	if (held_item == "shotgun.waterpipe") {
		RP.recoilYawMin = 4.0f;	RP.recoilYawMax = 8.0f;		RP.recoilPitchMin = -10.0f;	RP.recoilPitchMax = -14.0f;	return RP;
	}
	if (held_item == "shotgun.doublebarrel") {//redo
		RP.recoilYawMin = 8.0f;	RP.recoilYawMax = 15.0f;	RP.recoilPitchMin = -10.0f;	RP.recoilPitchMax = -15.0f;	return RP;
	}
	#pragma endregion

	return RP;
}
namespace Misc {

	void doRecoil(uintptr_t recoilProp)
	{
		if (Settings::enableRCS)
		{
			Write<float>(recoilProp + 0x18, Settings::RCSyaw / 12 * 1.35);
			Write<float>(recoilProp + 0x1C, Settings::RCSyaw / 12 * 1.35);
			Write<float>(recoilProp + 0x20, Settings::RCSpitch / 12 * 1.35);
			Write<float>(recoilProp + 0x24, Settings::RCSpitch / 12 * 1.35);
		}
		else
		{
			#pragma region debug
			/*static bool showRecoil = 0;
			if (showRecoil)
			{
				std::cout << localPlayer->Player->getHeldItem().GetItemName() << std::endl;
				std::cout << "yawMin " << Read<float>(recoilProp + 0x18) << std::endl;
				std::cout << "yawMax " << Read<float>(recoilProp + 0x1C) << std::endl;
				std::cout << "pitchMin " << Read<float>(recoilProp + 0x20) << std::endl;
				std::cout << "pitchMax " << Read<float>(recoilProp + 0x24) << std::endl;
			}
			else
			{
				Write<float>(recoilProp + 0x20, getRecoilProperties().recoilPitchMin);
				Write<float>(recoilProp + 0x24, getRecoilProperties().recoilPitchMax);
				Write<float>(recoilProp + 0x18, getRecoilProperties().recoilYawMin);
				Write<float>(recoilProp + 0x1C, getRecoilProperties().recoilYawMax);
			}*/
#pragma endregion
			Write<float>(recoilProp + 0x20, getRecoilProperties().recoilPitchMin);
			Write<float>(recoilProp + 0x24, getRecoilProperties().recoilPitchMax);
			Write<float>(recoilProp + 0x18, getRecoilProperties().recoilYawMin);
			Write<float>(recoilProp + 0x1C, getRecoilProperties().recoilYawMax);

		}
	}

	void DoMisc() {
		while (true) {
				std::unique_ptr<std::vector<BaseEntity>> local_players = std::make_unique<std::vector<BaseEntity>>();
				std::unique_ptr<HeldItem> heldItem = std::make_unique<HeldItem>();

				Mutex->PlayerSync->lock();
				*local_players = *entityList;
				Mutex->PlayerSync->unlock();

			for (unsigned long i = 0; i < local_players->size(); ++i)	{
				if (Settings::SpeedHack && GetAsyncKeyState(Settings::SpeedHackKey))
					Write<float>(localPlayer->Player->player + O::clothingMoveSpeedReduction, Settings::SpeedHackSpeed);
				else
					Write<float>(localPlayer->Player->player + O::clothingMoveSpeedReduction, 0);

				#pragma region Features

				*heldItem = localPlayer->Player->getHeldItem();

				if (Settings::fastKill && GetAsyncKeyState(Settings::fastKillKey))
					localPlayer->Movement->KillHack();

				if (Settings::shootInAir)
				{
					//localPlayer->Player->LongNeck();
					localPlayer->Player->setModelFlag(MStateFlags::OnGround);
					// localPlayer->Movement->alwaysShoot();
				}

				if (Settings::thirdperson) localPlayer->Player->setPlayerFlag(BPlayerFlags::ThirdPersonViewmode);
				if (Settings::adminFlag) localPlayer->Player->setPlayerFlag(BPlayerFlags::IsAdmin);


						// localPlayer->Movement->natak();
				if (Settings::freeze) localPlayer->Player->isFrozen();
				if (Settings::SuperJump) localPlayer->Movement->Gravity();
				//if (Settings::infinateJump) localPlayer->Movement->infiniteJump();
				if (Settings::walkOnWater) localPlayer->Movement->walkOnWater();
				if (Settings::spiderClimb) localPlayer->Movement->spiderClimb();

				localPlayer->Movement->FlyHack();

				if (Settings::ShootMounted) localPlayer->Player->AutoShit();

				//Sky Shit
				localPlayer->Player->TODCycle();

				if (Settings::FovSlider >= 75) localPlayer->Movement->setFov();
				if (Settings::zoom) localPlayer->Movement->zoom();


				if (heldItem->IsWeapon())
				{
					doRecoil(heldItem->getRecoilProp());
					if (Settings::noAimcone) heldItem->setNoAimCone();
					if (Settings::noSpread) heldItem->AntiSpread();
					if (Settings::noSway) heldItem->setNoSway();
					if (Settings::rapidFire) heldItem->rapidFire();
					if (Settings::instantCompound) heldItem->instantCompound();
					//if (Settings::fastSwitchWeapons) heldItem->fastSwitch();
					if (Settings::tapeoka) heldItem->instantEoka();
					if (Settings::longhit) heldItem->setLonghit(5.f);
					if (Settings::runhit) heldItem->RunHit();
					if (Settings::thickBullettt) heldItem->fatBullet();
					//if (Settings::fly)  heldItem->FastMed(20.f);
				}
				#pragma endregion
				
			}
		}
	}
}
