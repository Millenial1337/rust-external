#pragma once
#include "Settings.hpp"

namespace Settings {

	float espColorMisc[4] = { 1.f, 1.f, 1.f, 1.f };
	//Aimbot:
	int aimbotSmoothingValue = 10;
	int aimbotKey = 0x05;
	int zoomKey = 0;
	bool fly = false;
	bool zoom = false;
	bool enableAimbot = false;
	bool enableAimbotDistance = false;
	bool aimbotSmoothing = false;
	float aimSmoothing = 100;
	int aimbotFov = 10;
	int aimbotHitbox = 0;
	int aimbotDistance = 50;

	bool enableRCS = false;
	int RCSpitch = -50;
	int RCSyaw = -50;

	bool enableDroppedItem = false;

	bool enableVisuals = false;
	bool drawSkeleton = false;
	bool drawBox = false;
	bool drawCrosshair = false;
	bool drawHealthBar = false;
	bool healthNiggers = false;
	bool drawName = false;
	bool waterLevel = false;
	bool drawWeapon = false;
	bool drawSnaplines = false;

	bool freeze = false;

	bool bradleyESP = true;
	bool shootAnywhere = false;
	bool noSpread = false;
	bool rapidFire = false;
	bool instantCompound = false;
	bool snapLinez = false;
	bool SuperJump = false;
	
	int flyhackKey = 0;
	float flyhackSpeed = 0.f;
	bool flyHackkk = false;


	float FiledVIEWW = 90;

	float rapidfirevalue = 0.01; //0.09

	bool enableSmoothing = false;

	bool enableCompensateRecoil = false;

	int playerDistance = 100;
	int weaponDistance = 100;
	int droppedDistance = 100;

	int FovSlider = 90;

	float GravitySlider = 2.8;


	int jumpKey = 0;
	int LongNeckKey = 0;
	int flyKey = 0;
	int walkWaterKEY = 0;
	bool walkOnWater = false;

	int aimBone = 0;

	bool spiderClimb = false;
	bool corpseESP = false;

	bool flyHack = false;
	bool infinateJump = false;

	bool adminFlag = false;
	bool SpeedHack = false;
	float SpeedHackSpeed = 0;
	int SpeedHackKey = 0;

	bool longhit;
	bool runhit;
	bool thickBullettt = false;
	bool longmed;

	float time = 12.f;

	bool shootInAir = false;
	bool fastKill = false;
	int corpseESPdistance = 100;
	int fastKillKey = 0;
	bool thirdperson = false;

	bool fastSwitchWeapons = false;

	bool tapeoka = false;
	int fov;
	int fov_changer_key;

	int typeBox = 0;
	bool pistol = true;

	bool selectedOres[23]{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

	float DroppedItemCol[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_box[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_skeleton[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_crosshair[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_name[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_weapon[4] = { 1.f, 1.f, 1.f, 1.f };

	float drawColor_friendly[4] = { 0.332143, 0.779874, 0.2011, 1 };

	bool stoneESP = false;
	bool crosshairScoped = false;
	int CrosshairLength = 17;
	int CrosshairGap = 6;
	int CrosshairThickness = 1;

	bool metalOreESP = false;
	bool sulfurOreESP = false;
	bool stoneOreESP = false;

	bool patrolHeliESP = false;
	bool HempESP = false;

	bool day_changer = false;
	bool night_mode = false;
	bool sky_changer = false;
	float day_time = 12;
	float sky_color = 1;
	float cloud_color = 1;
	float cloud_brightness = 1;

	bool thickBullet = false;

	float SkyColor = 1;
	bool skyColorBool = false;
	bool nightSky = false;
	bool testingBool = false;

	bool ShootMounted = false;
	bool watermark = true;
	bool debuglog = false;
}