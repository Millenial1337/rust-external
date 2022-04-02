#pragma once
#include "Aimbot.hpp"
BonesList bone;
namespace Aimbot {
	uintptr_t getTarget()
	{
		float LastFov = FLT_MAX;
		std::unique_ptr<std::vector<BaseEntity>> local_players = std::make_unique<std::vector<BaseEntity>>();
		uintptr_t Target;

		Mutex->PlayerSync->lock();
		*local_players = *entityList;
		Mutex->PlayerSync->unlock();
		for (unsigned long i = 0; i < local_players->size(); ++i) {
			std::unique_ptr<BaseEntity> curEntity = std::make_unique<BaseEntity>(local_players->at(i));

			if (curEntity->isLocalPlayer()) continue;

			if (curEntity->isSameTeam(localPlayer->Player)) continue;

			if (!curEntity->IsInView()) continue;

			if (curEntity->health < 0.00f) continue;

			switch (Settings::aimbotHitbox)
			{
			case 0: bone = BonesList::neck; break;
			case 1: bone = BonesList::spine1; break;
			case 2: bone = BonesList::pelvis; break;
			}
			auto CrosshairDistanceToPlayer = AimFov(curEntity, bone);
			if (CrosshairDistanceToPlayer < LastFov && CrosshairDistanceToPlayer > 0.0f && CrosshairDistanceToPlayer <= Settings::aimbotFov)
			{
				LastFov = CrosshairDistanceToPlayer;
				Target = curEntity->player;
			}
		}
		return Target;
	}

	void DoAimbot() {
		while (true) {
			if (Settings::enableAimbot) {
				uintptr_t target = getTarget();

				std::unique_ptr<std::vector<BaseEntity>> local_players = std::make_unique<std::vector<BaseEntity>>();

				Mutex->PlayerSync->lock();
				*local_players = *entityList;
				Mutex->PlayerSync->unlock();

				for (unsigned long i = 0; i < local_players->size(); ++i) {
					std::unique_ptr<BaseEntity> curEntity = std::make_unique<BaseEntity>(local_players->at(i));

					if (curEntity->player != target)
						continue;

					if (GetAsyncKeyState(Settings::aimbotKey) && target) {
						auto distance = (int)Math::Distance(&localPlayer->Player->position, &curEntity->position);
						if (Settings::enableAimbotDistance)
						{
							if (curEntity->player && distance <= Settings::aimbotDistance)
								AimbotTarget(curEntity, bone);
						}
						else
						{
							if (curEntity->player)
								AimbotTarget(curEntity, bone);
						}
					}
				}
			}
			else SleepEx(20, false);
		}
	}
}