#pragma once
#pragma region Includes
#include "Imports.hpp"
#include "Driver.hpp"
#include "Utils.hpp"
#include "HeldItem.hpp"
#pragma endregion

#pragma region BPFlags

enum class BCameraMode {
	FirstPerson = 0,
	ThirdPerson = 1,
	Eyes = 2,
	FirstPersonWithArms = 3,
	Last = 3
};

enum class BPlayerFlags {
	Unused1 = 1,
	Unused2 = 2,
	IsAdmin = 4,
	ReceivingSnapshot = 8,
	Sleeping = 16,
	Spectating = 32,
	Wounded = 64,
	IsDeveloper = 128,
	Connected = 256,
	ThirdPersonViewmode = 1024,
	EyesViewmode = 2048,
	ChatMute = 4096,
	NoSprint = 8192,
	Aiming = 16384,
	DisplaySash = 32768,
	Relaxed = 65536,
	SafeZone = 131072,
	ServerFall = 262144,
	Workbench1 = 1048576,
	Workbench2 = 2097152,
	Workbench3 = 4194304,
	DebugCamera = 260
};


enum class BMapNoteType {
	Death = 0,
	PointOfInterest = 1
};

enum class BTimeCategory {
	Wilderness = 1,
	Monument = 2,
	Base = 4,
	Flying = 8,
	Boating = 16,
	Swimming = 32,
	Driving = 64
};

#pragma endregion

#pragma region OffsetStuff

constexpr auto ConVar_Graphics_c = 56959168; //0x32732A0
#pragma endregion

#pragma region BList

enum BonesList : int
{
	pelvis = 0,
	l_hip = 1,
	l_knee = 2,
	l_foot = 3,
	l_toe = 4,
	l_ankle_scale = 5,
	penis = 6,
	GenitalCensor = 7,
	GenitalCensor_LOD0 = 8,
	Inner_LOD0 = 9,
	GenitalCensor_LOD1 = 11,
	GenitalCensor_LOD2 = 12,
	r_hip = 13,
	r_knee = 14,
	r_foot = 15,
	r_toe = 16,
	r_ankle_scale = 17,
	spine1 = 18,
	spine1_scale = 19,
	spine2 = 20,
	spine3 = 21,
	spine4 = 22,
	l_clavicle = 23,
	l_upperarm = 24,
	l_forearm = 25,
	l_hand = 26,
	l_index1 = 27,
	l_index2 = 28,
	l_index3 = 29,
	l_little1 = 30,
	l_little2 = 31,
	l_little3 = 32,
	l_middle1 = 33,
	l_middle2 = 34,
	l_middle3 = 35,
	l_prop = 36,
	l_ring1 = 37,
	l_ring2 = 38,
	l_ring3 = 39,
	l_thumb1 = 40,
	l_thumb2 = 41,
	l_thumb3 = 42,
	IKtarget_righthand_min = 43,
	IKtarget_righthand_max = 44,
	l_ulna = 45,
	neck = 46,
	head = 47,
	jaw = 48,
	eyeTranform = 49,
	l_eye = 50,
	l_Eyelid = 51,
	r_eye = 52,
	r_Eyelid = 53,
	r_clavicle = 54,
	r_upperarm = 55,
	r_forearm = 56,
	r_hand = 57,
	r_index1 = 58,
	r_index2 = 59,
	r_index3 = 60,
	r_little1 = 61,
	r_little2 = 62,
	r_little3 = 63,
	r_middle2 = 65,
	r_middle3 = 66,
	r_prop = 67,
	r_ring1 = 68,
	r_ring2 = 69,
	r_ring3 = 70,
	r_thumb1 = 71,
	r_thumb2 = 72,
	r_thumb3 = 73,
	IKtarget_lefthand_min = 74,
	IKtarget_lefthand_max = 75,
	r_ulna = 76,
	l_breast = 77,
	r_breast = 78,
	BoobCensor = 79,
	BreastCensor_LOD0 = 80,
	BreastCensor_LOD1 = 83,
	BreastCensor_LOD2 = 84
};

#pragma endregion

#pragma region MSFlags

enum class MStateFlags {
	Ducked = 1,
	Jumped = 2,
	OnGround = 4,
	Sleeping = 8,
	Sprinting = 16,
	OnLadder = 32,
	Flying = 64,
	Aiming = 128,
	Prone = 256,
	Mounted = 512,
	Relaxed = 1024,
};

enum class BaseEntityFlag
{
	stash = 2048,
};

#pragma endregion

#pragma region BPClass

class Utility
{
public:
	std::string wstring_to_string(const std::wstring& wstring);

}; Utility* utils;



std::string Utility::wstring_to_string(const std::wstring& wstring)
{
	int slength = (int)wstring.length() + 1;
	int len = WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), slength, 0, 0, 0, 0);
	std::string r(len, '\0');
	WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), slength, &r[0], len, 0, 0);
	return r;
}
class BaseEntity {
public:

	BaseEntity() {}

	//where i find this

	// Namespace: 
	//private struct RuntimeStructs.MonoError // TypeDefIndex: 18

	BaseEntity(uintptr_t _ent, uintptr_t _trans, uintptr_t _obj) {

		this->player = Read<uintptr_t>(_ent + 0x28); // public class BasePlayer (0x20 baseentity)
		this->visualState = Read<uintptr_t>(_trans + 0x38); // public class Transform : Component, IEnumerable

		this->playerFlags = Read<int32_t>(_ent + 0x7C8); //public BasePlayer.PlayerFlags playerFlags;
		this->name = ReadNative(_obj + 0x40);//public abstract class BaseNetworkable _prefabname
		this->entityFlags = Read<int32_t>(_ent + 0xC0); //public BaseEntity.Flags flags

		this->playerModel = Read<uintptr_t>(this->player + 0x598); //public PlayerModel playerModel;
		this->modelState = Read<uintptr_t>(this->player + 0x718); //public ModelState modelState

		this->position = Read<Vector3>(this->visualState + 0x90); //public Vector3 position { get; set; } i don't know what the fuck is this...
		this->health = Read<float>(this->player + 0x23C);//protected float _health;
	}

public:

	//public PlayerInput input; + private Vector3 bodyAngles;

	void setViewAngles(Vector3 angles) {
		Write<Vector3>(Read<uint64_t>(this->player + 0x5B8) + 0x3C, angles);
	}

	void setViewAngles(Vector2 angles) {
		Write<Vector2>(Read<uint64_t>(this->player + 0x5B8) + 0x3C, angles);
	}

	void set_aim_angles(Vector3 aim_angle) {
		auto current = Read<uintptr_t>((uintptr_t)(this + 0x10)); //public class PlayerTick
		Read<Vector3>(current + 0x14) = aim_angle; //InputMessage -> public Vector3 aimAngles
	}

	void setPlayerFlag(BPlayerFlags flag) {
		Write(this->player + 0x7C8, flag);//public BasePlayer.PlayerFlags playerFlags;
	}

	void remove_flag(MStateFlags flag)
	{
		int flags = *reinterpret_cast<int*>((uintptr_t)this + 0x20);// ModelState -> public int flags;
		flags &= ~(int)flags;

		*reinterpret_cast<int*>((uintptr_t)this + 0x20) = flags;// ModelState -> public int flags;
	}

	void setModelFlag(MStateFlags flag) {
		Write(this->modelState + 0x20, flag);// 	public int flags;
	}

	void setBaseFlag(BaseEntityFlag flag) {
		Write(this->entityFlags + 0xC0, flag);// BaseEntity -> public BaseEntity.Flags flags;
	}

	void speedHack(int speed) {
		Write<float>(this->player + 0x89C, speed); // clothingMoveSpeedReduction
	}

public:

	bool IsInView() {
		Vector2 screen_pos;
		if (!Utils::WorldToScreen(this->getPosition(), screen_pos))
			return false;

		return true;
	}


	bool isLocalPlayer() {
		return Read<bool>(this->playerModel + 0x239); //internal bool isLocalPlayer;
	}
	
	bool isVisible()
	{
		return Read<bool>(this->playerModel + 0x228); // internal bool visible //0x268
	}

	bool iSMenu()
	{
		if (!this) return true;
		DWORD64 Input = Read<DWORD64>(this->player + 0x5B8);//public PlayerInput input;
		return !(Read<bool>(Input + 0xAC)); // private bool hasKeyFocus;
	}

	bool isSameTeam(std::unique_ptr<BaseEntity>& localPlayer) {
		auto localTeam = Read<uint32_t>(localPlayer->player + 0x6B0); //public ulong currentTeam; 
		auto playerTeam = Read<uint32_t>(this->player + 0x6B0);

		if (localTeam == 0 || playerTeam == 0)
			return false;

		return (localTeam == playerTeam);
	}

	bool isConnected() {
		return this->getPlayerFlag(BPlayerFlags::Connected);
	}

	bool isSleeping() {
		return this->getPlayerFlag(BPlayerFlags::Sleeping);
	}

	bool isWounded() {
		return this->getPlayerFlag(BPlayerFlags::Wounded);
	}

	bool isAiming() {
		return this->getPlayerFlag(BPlayerFlags::Aiming);
	}

	bool isFrozen() {
		if (GetAsyncKeyState(Settings::flyKey))
		{
			return Read<bool>(this->player + 0x5A0); //public bool Frozen;
		}
	}

	bool mounted() {
		return Read<bool>(this->player + 0x720);// BasePlayer -> mounted
	}

	bool isDead() {
		return (this->health <= 0);
	}

public:

	uint64_t getUserID()
	{
		return Read<uint64_t>(this->player + 0x810); //BasePlayer -> public ulong userID; 
	}

	int getDistance(std::unique_ptr<BaseEntity>& player) {
		return this->getPosition().Distance(player->position);
	}

	std::string getDistanceStr(std::unique_ptr<BaseEntity>& player) {
		return std::to_string(this->getDistance(player));
	}

	uint64_t getMountedEntity() {
		return Read<uint64_t>(this->player + 0x720); //BasePlayer -> mounted
	}

	bool getModelFlag(MStateFlags flag) {
		return (this->playerModel & static_cast<int32_t>(flag)) == static_cast<int32_t>(flag);
	}

	bool getPlayerFlag(BPlayerFlags flag) {
		return (this->playerFlags & static_cast<int32_t>(flag)) == static_cast<int32_t>(flag);
	}

	std::string getASCIIName(std::wstring name) {
		return std::string(name.begin(), name.end());
	}

	Vector3 getNewVelocity() {
		return Read<Vector3>(this->playerModel + 0x1DC); //private Vector3 newVelocity;
	}

	//public class Transform : Component, IEnumerable // TypeDefIndex: 3572
	
	

	Vector3 getPosition() {
		return Read<Vector3>(this->visualState + 0x90); //public Vector3 position { get; set; }
	}

	Vector3 getRecoilAngles() {
		return ReadChain<Vector3>(this->player, { (uint64_t)0x5B8, (uint64_t)0x64 }); //public PlayerInput input, public Vector3 recoilAngles
	}

	Vector3 getViewAngles() {
		return ReadChain<Vector3>(this->player, { (uint64_t)0x5B8, (uint64_t)0x3C });// public PlayerInput input, private Vector3 bodyAngles;
	}

	std::string getName() {
		return this->getASCIIName(this->getPlayerName());
	}


	void AntiHeavy()
	{
		float Reduction = Read<float>(this->player + 0x734);
		if (Reduction == 0.f) { Write<float>(this->player, -0.1f); }
		else if ((Reduction > 0.15f) && (Reduction < 0.35f))
		{
			Write<float>(this->player + 0x734, 0.15f);
		}
		else if (Reduction > 0.39f)
		{
			Write<float>(this->player + 0x734, 0.15f);
		}
	}

	void AutoShit()
	{
		auto mountable = Read<uint64_t>(this->player + 0x720);
		if (mountable)
			Write<bool>(mountable + O::canWieldItems, true); // canWieldItems
	}

#pragma region SkyClass+World
	
	void TODCycle()
	{
		//TODO: Fix that, man...
		//DWORD64 ObjManager = Read<DWORD64>(uBase + 0x17C1F18); if (!ObjManager) return;
		DWORD64 ObjManager = Read<DWORD64>(uBase + 0x1A572B8); if (!ObjManager) return;
		//DWORD64 ObjManager = Read<DWORD64>(uBase + 0x17C1F18); if (!ObjManager) return;
		DWORD64 Obj = Read<DWORD64>(ObjManager + 0x8); (Obj && (Obj) != Read<DWORD64>(ObjManager)); Obj = Read<DWORD64>(Obj + 0x8);
		DWORD64 GameObject = Read<DWORD64>(Obj + 0x10); //tagged object
		DWORD64 ObjClass = Read<DWORD64>(GameObject + 0x30);
		DWORD64 Entity1 = Read<DWORD64>(ObjClass + 0x18);
		DWORD64 Dome = Read<DWORD64>(Entity1 + 0x28);
		DWORD64 TodCycle = Read<DWORD64>(Dome + 0x38);


		uint64_t test1 = Read<uint64_t>(GameObject + 0x30);//night
		uint64_t test2 = Read<uint64_t>(test1 + 0x18); //world
		uint64_t test3 = Read<uint64_t>(test2 + 0x28); //day
		uint64_t AtmosphereParameters = Read<uint64_t>(test3 + 0x48); //light
		uint64_t CycleParameters = Read<uint64_t>(test3 + 0x38); //sun

		uint64_t TOD_CycleParameters = Read<uint64_t>(test3 + 0x38);
		uint64_t TOD_DayParameters = Read<uint64_t>(test3 + 0x50);
		uint64_t TOD_NightParameters = Read<uint64_t>(test3 + 0x58);
		uint64_t TOD_CloudParamaters = Read<uint64_t>(test3 + 0x78);
		uint64_t TOD_AmbientParameters = Read<uint64_t>(test3 + 0x90);

		if (Settings::nightSky)
		{
			//public class TOD_NightParameters
			Write<float>(TOD_AmbientParameters + 0x28, 1.f);//public EnvironmentMultiplier[] AmbientMultipliers;
			Write<float>(TOD_NightParameters + 0x50, 6.f);//AmbientMultiplier
			Write<float>(TOD_NightParameters + 0x54, 1.f);//ReflectionMultiplier 0x54
			Write<float>(TOD_DayParameters + 0x50, 1.f);//AmbientMultiplier
			Write<float>(TOD_DayParameters + 0x54, 1.f);//ReflectionMultiplier
		}
		if (Settings::skyColorBool)
			Write<float>(AtmosphereParameters + 0x10, Settings::SkyColor);
		if (Settings::night_mode)
			Write<float>(TodCycle + 0x10, Settings::time);
	}
#pragma endregion

	void LongNeck()
	{
		if (GetAsyncKeyState(Settings::LongNeckKey))
		{
			DWORD64 eyes = Read<DWORD64>(this->player + 0x7D0); //public PlayerEyes eyes;
			Write<Vector3>(eyes + 0x38, Vector3(0, (0.8f), 0));
		}
	}

HeldItem getHeldItem()
{
	int active_weapon_id = Read<int>(this->player + 0x6E8); // public struct ItemId--private uint clActiveItem;
	//							               public PlayerInventory inventory   BasePlayer
	uint64_t items = ReadChain<uint64_t>(this->player, { (uint64_t)0x7D8, (uint64_t)0x28, (uint64_t)0x38, 0x10 }); //public PlayerInventory inventory;

	//if (Settings::debuglog)
	//	std::cout << "Held weapon: " <<  items << std::endl;

	for (int items_on_belt = 0; items_on_belt <= 6; items_on_belt++)
	{
		uint64_t item = Read<uint64_t>(items + 0x20 + (items_on_belt * 0x8));

		int active_weapon = Read<uint32_t>(item + 0x28);

		if (active_weapon_id == active_weapon)
		{
			HeldItem item_obj = HeldItem(item);

			return item_obj;
		}
	}

	return 0;
}

std::wstring getPlayerName() {
	std::wstring name = ReadUnicode(Read<uint64_t>(this->player + 0x828) + 0x14); //BasePlayer -> protected string _displayName

	if (name.find(safe_strW(L"Scientist")) == 0)
		return safe_strW(L"Scientist");

	return name;
}

public:

	uintptr_t player{};
	uintptr_t visualState{};
	std::string name{};
	bool isCalled{};
	std::wstring nameW{};
	Vector3 position{};
	int32_t playerFlags{};
	int entityFlags{};
	uint64_t playerModel{};
	uint64_t modelState{};
	float health{};

}; std::unique_ptr<std::vector<BaseEntity>> entityList;

#pragma endregion

class EntityCorpse {
public:

	EntityCorpse() {}

	EntityCorpse(uintptr_t _ent, uintptr_t _trans, uintptr_t _obj) {
		this->ent = Read<uintptr_t>(_ent + 0x28);
		this->trans = Read<uintptr_t>(_trans + 0x38);

		this->name = ReadNative(_obj + 0x60);
	}

public:

	uintptr_t ent{};
	uintptr_t trans{};
	std::string name{};
}; std::unique_ptr<std::vector<EntityCorpse>> corpseList;

#pragma region PMClass

class EntityMovment : public BaseEntity, EntityCorpse {
public:

	EntityMovment() {}

	EntityMovment(uintptr_t player) {        //0x4D0
		this->playerMovement = Read<uintptr_t>(player + O::BaseMovement); 
	}

	void alwaysShoot() {
		Write<float>(this->playerMovement + 0x48, 1);  // mb --public uint hitBone; ? //HitInfo 
	}

	void setFov() {
		auto klass = Read<DWORD64>(gBase + ConVar_Graphics_c); //ConVar.Graphics_TypeInfo
		auto staticFields = Read<DWORD64>(klass + 0xB8);
		Write<float>(staticFields + 0x18, Settings::FovSlider);//0x18 => m_camera
	}

	void zoom()
	{
		if (GetAsyncKeyState(Settings::zoomKey))
		{
			auto klass = Read<DWORD64>(gBase + ConVar_Graphics_c); //ConVar.Graphics_TypeInfo
			auto staticFields = Read<DWORD64>(klass + 0xB8);
			Write<float>(staticFields + 0x18, 20.f);//0x18 => m_camera
		}
	}
	
	void infiniteJump()
	{
		if (GetAsyncKeyState(Settings::jumpKey))
		{
			Write<float>(this->playerMovement + 0xC0, 0); // maxvelocity
			Write<Vector3>(this->playerMovement + 0xBC, Vector3(99999, 99999, 99999));	
		}
	}

	void FlyHack()
	{
		if (Settings::flyHackkk)
		{
			if (GetAsyncKeyState(Settings::flyhackKey))
			{
				Write<float>(this->modelState + O::waterLevel, 2);
				Write<float>(this->playerMovement + O::gravityTestRadius, -2);
				Write<float>(this->playerMovement + O::groundAngle, 0);
				Write<float>(this->playerMovement + O::groundAngleNew, 0);
				Write<float>(this->playerMovement + O::capsuleHeight, -300);
				Write<float>(this->playerMovement + O::capsuleCenter, -300);

				if(GetAsyncKeyState(VK_SPACE))
					Write<float>(this->playerMovement + O::gravityMultiplier, Settings::flyhackSpeed);
				else
					Write<float>(this->playerMovement + O::gravityMultiplier, 0.1);
			}
			else
			{
				Write<float>(this->playerMovement + O::groundAngle, 0);
				Write<float>(this->playerMovement + O::groundAngleNew, 50);
				Write<float>(this->playerMovement + O::gravityMultiplier, 2.5f);
				Write<float>(this->playerMovement + O::capsuleHeight, 1.79f);
				Write<float>(this->playerMovement + O::capsuleCenter, 0.899f);
			}
		}
	}

	void spiderClimb() {
		Write<float>(this->playerMovement + O::groundAngle, 0.f);
		Write<float>(this->playerMovement + O::groundAngleNew, 0.f);
	}

	void KillHack()
	{
		Write<bool>(this->playerMovement + O::wasFalling, true);
		Write<Vector3>(this->playerMovement + O::previousVelocity, Vector3(0, -20, 0));
		Write<float>(this->playerMovement + O::groundTime, 0.f);
	}

	void Gravity()
	{
		Write<float>(this->playerMovement + O::gravityMultiplier, Settings::GravitySlider);
	}

	void walkOnWater() {
		if (GetAsyncKeyState(Settings::walkWaterKEY)) {
			Write<float>(this->playerMovement + O::groundAngle, 0.f);//groundAngle
			Write<float>(this->playerMovement + O::groundAngleNew, 0.f);//groundAngleNew
			Write<float>(this->playerMovement + O::gravityMultiplier, 1.f);//gravityMultiplier
		}
		else {
			Write<float>(this->playerMovement + O::gravityMultiplier, 2.5f);//gravityMultiplier
		}
	}

public:

	uint64_t playerMovement{};
	uint64_t playerModelFlags{};
	uint64_t Mounted{};
};

#pragma endregion

class BaseMiscEntity {
public:
	BaseMiscEntity() {}

	BaseMiscEntity(uintptr_t _ent, uintptr_t _trans, uintptr_t _obj) {
		this->ent = Read<uintptr_t>(_ent + 0x28);
		this->trans = Read<uintptr_t>(_trans + 0x38);
		this->name = ReadNative(_obj + 0x60);

		if (this->name.find(safe_str("stone-ore")) != std::string::npos)
			this->name = safe_str("STONE");
		else if (this->name.find(safe_str("metal-ore")) != std::string::npos)
			this->name = safe_str("METAL");
		else if (this->name.find(safe_str("sulfur-ore")) != std::string::npos)
			this->name = safe_str("SULFUR");
		else if (this->name.find(safe_str("stone-collectable")) != std::string::npos)
			this->name = safe_str("STONE");
		else if (this->name.find(safe_str("metal-collectable")) != std::string::npos)
			this->name = safe_str("METAL");
		else if (this->name.find(safe_str("sulfur-collectable")) != std::string::npos)
			this->name = safe_str("SULFUR");
		else if (this->name.find(safe_str("wood-collectable")) != std::string::npos)
			this->name = safe_str("WOOD");
		else if (this->name.find(safe_str("hemp-collectable")) != std::string::npos || this->name.find(safe_str("hemp.entity.prefab")) != std::string::npos)
			this->name = safe_str("HEMP");
		else if (this->name.find(safe_str("small_stash_deployed")) != std::string::npos)
			this->name = safe_str("STASH");
		else if (this->name.find(safe_str("loot_barrel_1.prefab")) != std::string::npos || this->name.find(safe_str("loot_barrel_2.prefab")) != std::string::npos || this->name.find(safe_str("loot-barrel-1.prefab")) != std::string::npos || this->name.find(safe_str("loot-barrel-2.prefab")) != std::string::npos)
			this->name = safe_str("BARREL");
		else if (this->name.find(safe_str("oil_barrel.prefab")) != std::string::npos)
			this->name = safe_str("OIL BARREL");
		else if (this->name.find(safe_str("crate_elite.prefab")) != std::string::npos)
			this->name = safe_str("ELITE CRATE");
		else if (this->name.find(safe_str("crate_normal.prefab")) != std::string::npos)
			this->name = safe_str("MILITARY CRATE");
		else if (this->name.find(safe_str("crate_normal_2_medical.prefab")) != std::string::npos)
			this->name = safe_str("MEDICAL CRATE");
		else if (this->name.find(safe_str("crate_normal_2.prefab")) != std::string::npos)
			this->name = safe_str("REGULAR CRATE");
		else if (this->name.find(safe_str("crate_normal_2_food.prefab")) != std::string::npos)
			this->name = safe_str("FOOD CRATE");
		else if (this->name.find(safe_str("crate_tools.prefab")) != std::string::npos)
			this->name = safe_str("TOOL CRATE");
		else if (this->name.find(safe_str("rowboat.prefab")) != std::string::npos)
			this->name = safe_str("BOAT");
		else if (this->name.find(safe_str("rhib.prefab")) != std::string::npos)
			this->name = safe_str("RHIB");
		else if (this->name.find(safe_str("kayak.prefab")) != std::string::npos)
			this->name = safe_str("KAYAK");
		else if (this->name.find(safe_str("minicopter.entity.prefab")) != std::string::npos)
			this->name = safe_str("MINICOPTER");
		else if (this->name.find(safe_str("bradleyapc.prefab")) != std::string::npos)
			this->name = safe_str("BRADLEY");

		else
			this->name = safe_str("Error");

	}

public:
	uintptr_t ent{};
	uintptr_t trans{};
	std::string name{};
}; std::unique_ptr<std::vector<BaseMiscEntity>> oreList;//scans for ores

class BaseWeaponESP {
public:
	BaseWeaponESP() {}

	BaseWeaponESP(uintptr_t _ent, uintptr_t _trans, std::string _name) {
		this->ent = Read<uintptr_t>(_ent + 0x28);
		this->trans = Read<uintptr_t>(_trans + 0x38);
		this->name = _name;
	}

public:
	uintptr_t ent{};
	uintptr_t trans{};
	std::string name{};
}; std::unique_ptr<std::vector<BaseWeaponESP>> weaponList;

#pragma region LPClass

class LocalPlayer {
public:
	std::unique_ptr<BaseEntity> Player;
	std::unique_ptr<EntityMovment> Movement;
}; std::unique_ptr<LocalPlayer> localPlayer;

#pragma endregion