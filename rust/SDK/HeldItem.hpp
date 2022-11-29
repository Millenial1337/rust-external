#pragma once
#include "Imports.hpp"
#include "Driver.hpp"
#include "Utils.hpp"

namespace O {
	uintptr_t waterLevel = 0x478;// WaterWell -> public float waterLevelObjFullOffset;

		// PlayerWalkMovement
	uintptr_t gravityTestRadius = 0x80;// public float gravityTestRadius
	uintptr_t groundAngle = 0xC4;// groundAngle
	uintptr_t groundAngleNew = 0xC8;// groundAngleNew
	uintptr_t capsuleHeight = 0x68;// public float capsuleHeight
	uintptr_t capsuleCenter = 0x6C;// public float capsuleCenter
	uintptr_t gravityMultiplier = 0x84;// public float gravityMultiplier;
	uintptr_t wasFalling = 0x148;// private bool wasFalling 0x00
	uintptr_t previousVelocity = 0xE4;// private Vector3 previousVelocity
	uintptr_t groundTime = 0xCC;// private float groundTime

	uintptr_t clothingMoveSpeedReduction = 0x764;// public float clothingMoveSpeedReduction;

	uintptr_t heldEntity = 0xA0;// Item -> private EntityRef heldEntity;

		// BaseProjectile
	uintptr_t recoil = 0x2E0;// public RecoilProperties recoil;
	uintptr_t primaryMagazine = 0x2C0;//0x2A0 = public BaseProjectile.Magazine primaryMagazine;
	uintptr_t aimSway = 0x2D8;// public float aimSway;
	uintptr_t aimSwaySpeed = 0x2DC;// public float aimSwaySpeed;
	uintptr_t aimCone = 0x2F0;// public float aimCone;
	uintptr_t hipAimCone = 0x2F4;// public float hipAimCone;
	uintptr_t aimconePenaltyPerShot = 0x2F8;// public float aimconePenaltyPerShot;
	uintptr_t aimConePenaltyMax = 0x2FC;// public float aimConePenaltyMax;

		//BasePlayer
	uintptr_t BaseMovement = 0x4F8;// public BaseMovement movement;
	uintptr_t stancepenalty = 0x324; //private float stancePenalty;
	uintptr_t ClothingAccuracyBonus = 0x76C; // public float clothingAccuracyBonus;
	uintptr_t aimconePenalty = 0x328; //private float aimconePenalty;

	uintptr_t canWieldItems = 0x2B8; // BaseMountable -> public bool canWieldItems;
}

typedef void(__fastcall* hitsound_fn)(DWORD64);
inline hitsound_fn original_sound;

class HeldItem {
public:

	HeldItem() {}

	HeldItem(uint64_t _ent) {
		this->ent = _ent;

		this->name = GetItemName();

		this->bp = Read<uintptr_t>(this->ent + O::heldEntity);

		this->recoil_properties = Read<uintptr_t>(this->bp + O::recoil);

		this->primary_mag = Read<uint64_t>(this->bp + O::primaryMagazine);
	}

	std::string GetItemName()
	{
		uint64_t info = Read<uint64_t>(this->ent + 0x20);// 0x30

		uint64_t display_name = Read<uint64_t>(info + 0x20);

		std::wstring wide_name = ReadUnicode(display_name + 0x14);

		if (!wide_name.empty())
			return std::string(wide_name.begin(), wide_name.end()).c_str();
		if (Settings::debuglog)
		{
			std::cout << "Display name: " << display_name << std::endl;
		}

		return safe_str("No Item");
	}

	std::string GetActiveWeaponName(uint64_t myWeapon)
	{
		uint64_t itemDefinition = Read<uint64_t>(myWeapon + 0x20);
		uint64_t display_name = Read<uint64_t>(itemDefinition + 0x28);
		uint64_t english = Read<uint64_t>(display_name + 0x18);
		if (!english)
			return std::string();
		else
			return safe_str("nothing");
	}

	void setNoAimCone() {
		Write<float>(this->bp + O::aimCone, 0.f);
		Write<float>(this->bp + O::aimConePenaltyMax, 0.f);
		Write<float>(this->bp + O::aimconePenaltyPerShot, 0.f);
		Write<float>(this->bp + O::aimSway, 0.f);
		Write<float>(this->bp + O::aimSwaySpeed, 0.f);
		Write<float>(this->bp + O::hipAimCone, 0.f);
	}

	void AntiSpread()   // reworked
	{
		//DWORD64 Held = Read(this + oHeldEntity, DWORD64);
		Write<float>(this->bp + O::stancepenalty, 0.f);
		Write<float>(this->bp + O::aimconePenalty, 0.f);
		Write<float>(this->bp + O::aimCone, 0.f);
		Write<float>(this->bp + O::hipAimCone, 0.f);
		Write<float>(this->bp + O::aimconePenaltyPerShot, 0.f);
	}

	void setNoSway() {   // reworked
		Write<float>(this->bp + O::ClothingAccuracyBonus, 1.f);
	}

	void RunHit() { // rework
		Write<int>(this->bp + 0x299, 0);
	}

	uintptr_t getRecoilProp() {
		const auto recoil_properties = Read<uintptr_t>(this->bp + O::recoil);
		if (recoil_properties)
			return recoil_properties;
	}

	void fatBullet()
	{
		auto List = Read<DWORD64>(this->bp + 0x370); //private List<Projectile> createdProjectiles;
		List = Read<DWORD64>(List + 0x10);
		for (int i = 0; i < 8; ++i)
		{
			UINT64 Item = Read<UINT64>(List + 0x20 + (i * 0x8));
			Write<float>(Item + 0x2C, 1.5f);
		}
	}
	
	void rapidFire() {
			Write<float>(this->bp + 0x1F4, Settings::rapidfirevalue);
			Write<bool>(this->bp + 0x298, true); //public bool automatic;
	}

	void instantCompound() {
		if (this->name.find(safe_str("bow.compound")) != std::string::npos)
		{
			Write<float>(bp + 0x390, 0);//stringHoldDurationMax
			Write<float>(bp + 0x394, 1000000);//stringBonusDamage
			Write<float>(bp + 0x3A0, 1000000);//movementPenaltyRampUpTime
		}
	}

	void setLonghit(float input)  // rework
	{
		Write(this->bp + 0x290, input);
	}

	void FastMed(float input)  // rework
	{
		Write(this->bp + 0x280, input);
	}

	void fastSwitch() {  // rework
			Write<float>(bp + 0x1F0, 0);//deployDelay | instant deploy > AttackEntity
	}


	//causes a crash if switched to another weapon (i will fix - johnn)
	void instantEoka() {
		if (this->name.find(safe_str("eoka")) != std::string::npos)
		{
			Write<bool>(this->bp + 0x388, true);//_didSparkThisFrame
			Write<float>(this->bp + 0x378, 100.f);//successFraction
		}
	}


	bool IsWeapon()
	{
		if (this->name.find(safe_str("rifle")) != std::string::npos)
		{
			return true;
		}
		if (this->name.find(safe_str("pistol")) != std::string::npos)
		{
			return true;
		}
		if (this->name.find(safe_str("bow")) != std::string::npos)
		{
			return true;
		}
		if (this->name.find(safe_str("lmg")) != std::string::npos)
		{
			return true;
		}
		if (this->name.find(safe_str("shotgun")) != std::string::npos)
		{
			return true;
		}
		if (this->name.find(safe_str("smg")) != std::string::npos)
		{
			return true;
		}
		else
			return false;
	}

	std::string GetAmmoType()
	{
		uint64_t item_def = Read<uint64_t>(this->primary_mag + 0x20);
		uint64_t short_name = Read<uint64_t>(item_def + 0x20);

		std::wstring wide_name = ReadUnicode(short_name + 0x14);

		if (!wide_name.empty())
			return std::string(wide_name.begin(), wide_name.end()).c_str();

		return safe_str("No Ammo");
	}

public:
	uint64_t ent;
	uintptr_t bp;
	uint64_t playerMovement2{};
	uintptr_t recoil_properties;
	uint64_t primary_mag;
	std::string name;
};