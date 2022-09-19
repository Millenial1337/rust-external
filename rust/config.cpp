#include <string>
#include <vector>
#include <Windows.h>
#include "Overlay/Menu/Settings.hpp"

template <typename T>
class VarType
{
public:
	VarType(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};

class CConfig
{
public:
	CConfig()
	{
		ints = std::vector<VarType<int>*>();
		bools = std::vector<VarType<bool>*>();
		floats = std::vector<VarType<float>*>();
	}

	void Initialize()
	{
		szPath = "%APPDATA%";
		Setup();
	}

	void Save()
	{
		std::string file;

		file = szPath + "cfg.v";

		CreateDirectoryA(szPath.c_str(), NULL);

		for (VarType<int>* pValue : ints)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<float>* pValue : floats)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<bool>* pValue : bools)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), *pValue->value ? "1" : "0", file.c_str());
	}

	void Load()
	{
		std::string file;

		file = szPath + "cfg.v";

		CreateDirectoryA(szPath.c_str(), NULL);

		char value_l[32] = { '\0' };

		for (VarType<int>* pValue : ints)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = atoi(value_l);
		}

		for (VarType<float>* pValue : floats)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = (float)atof(value_l);
		}

		for (VarType<bool>* pValue : bools)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = !strcmp(value_l, "1");
		}
	}

private:
	void SetupValue(int& value, int def, std::string category, std::string name)
	{
		value = def;
		ints.push_back(new VarType<int>(category, name, &value));
	}

	void SetupValue(bool& value, bool def, std::string category, std::string name)
	{
		value = def;
		bools.push_back(new VarType<bool>(category, name, &value));
	}

	void SetupValue(float& value, float def, std::string category, std::string name)
	{
		value = def;
		floats.push_back(new VarType<float>(category, name, &value));
	}

	void Setup()
	{
		//aim
		//SetupValue(Settings::aimBone, 1, "aim", "aimBone");
		//SetupValue(Settings::aimbotDistance, 200.f, "aim", "Distance");
		//SetupValue(Settings::aimbotFov, 30.f, "aim", "Fov");
		//SetupValue(Vars::AimBot::Standalone, false, "Misc", "Standalone");
		//SetupValue(Vars::AimBot::RightMouseAiming, false, "AimBot", "RightMouseAiming");
		//SetupValue(Vars::AimBot::VisibleCheck, false, "AimBot", "VisibleCheck");
		//SetupValue(Vars::AimBot::DrawFov, false, "AimBot", "DrawFov");
		//SetupValue(Vars::AimBot::IgnoreTeam, false, "AimBot", "IgnoreTeam");
		//SetupValue(Vars::AimBot::Range, 250.f, "AimBot", "Range");
		//SetupValue(Vars::AimBot::Fov, 30.f, "AimBot", "Fov");

		////visuals
		//SetupValue(Vars::Visuals::ShowPlayerBox, false, "Visuals", "ShowPlayerBox");
		//SetupValue(Vars::Visuals::ShowPlayerName, false, "Visuals", "ShowPlayerName");
		//SetupValue(Vars::Visuals::ShowPlayerHealth, false, "Visuals", "ShowPlayerHealth");
		//SetupValue(Vars::Visuals::ShowPlayerWeapon, false, "Visuals", "ShowPlayerWeapon");
		//SetupValue(Vars::Visuals::ShowPlayerDist, false, "Visuals", "ShowPlayerDist");
		//SetupValue(Vars::Visuals::AlwaysDay, false, "Visuals", "AlwaysDay");
		//SetupValue(Vars::Visuals::IgnoreSleepers, false, "Visuals", "IgnoreSleepers");
		//SetupValue(Vars::Visuals::Skeleton, false, "Visuals", "Skeleton");
		//SetupValue(Vars::Visuals::Crosshair, false, "Visuals", "Crosshair");

		////misc
		//SetupValue(Vars::Misc::SpiderMan, false, "Misc", "SpiderMan");
		//SetupValue(Vars::Misc::AntiSpread, false, "Misc", "AntiSpread");
		//SetupValue(Vars::Misc::FastReload, false, "Misc", "FastReload");
		//SetupValue(Vars::Misc::Automatic, false, "Misc", "Automatic");
		//SetupValue(Vars::Misc::SuperEoka, false, "Misc", "SuperEoka");
		//SetupValue(Vars::Misc::SkinChanger, false, "Misc", "SkinChanger");
		//SetupValue(Vars::Misc::NoSway, false, "Misc", "NoSway");
		//SetupValue(Vars::Misc::SuperBow, false, "Misc", "SuperBow");
		//SetupValue(Vars::Misc::LongHand, false, "Misc", "LongHand");
		//SetupValue(Vars::Misc::FatHand, false, "Misc", "FatHand");
		//SetupValue(Vars::Misc::RunOnHit, false, "Misc", "RunOnHit");
		//SetupValue(Vars::Misc::FakeAdmin, false, "Misc", "FakeAdmin");
		//SetupValue(Vars::Misc::HighJump, false, "Misc", "HighJump");
		//SetupValue(Vars::Misc::JumpValue, 1.2f, "Misc", "Jump Multipler");
		//SetupValue(Vars::Misc::WaterBoost, false, "Misc", "Fast Swim");
		//SetupValue(Vars::Misc::NoHeavyReduct, false, "Misc", "Fast Run");
		//SetupValue(Vars::Misc::AirStuck, false, "Misc", "AirStuck");
		//SetupValue(Vars::Misc::AntiKastrulya, false, "Misc", "AntiKastrulya");
		//SetupValue(Vars::Misc::BuildAsUWant, false, "Misc", "BuildAsUWant");
	}

	std::string szPath = "";

protected:
	std::vector<VarType<int>*> ints;
	std::vector<VarType<bool>*> bools;
	std::vector<VarType<float>*> floats;
};

CConfig config;