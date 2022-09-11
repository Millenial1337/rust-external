#pragma once

#pragma region Includes
#include "../SDK/Classes.hpp"
#include "../SDK/BasePlayer.hpp"
#include "../SDK/Imports.hpp"
#include "../SDK/Driver.hpp"
#pragma endregion
namespace Entity {
#pragma region PlayerChain
	void EntityLoop() {
		auto BaseNetworkable = IL2CPPScan(safe_str("BaseNetworkable"));

		/*{ 0xb8, 0x0, 0x10, 0x28 }*/

		while (true)
		{
			std::unique_ptr<std::vector<BaseEntity>> t_entList = std::make_unique<std::vector<BaseEntity>>();
			std::unique_ptr<std::vector<EntityCorpse>> t_corpseList = std::make_unique<std::vector<EntityCorpse>>();
			std::unique_ptr<std::vector<BaseMiscEntity>> t_oreList = std::make_unique<std::vector<BaseMiscEntity>>();
			std::unique_ptr<std::vector<BaseWeaponESP>> t_weaponList = std::make_unique<std::vector<BaseWeaponESP>>();

			auto unk1 = Read<uintptr_t>(BaseNetworkable + 0xB8);
			auto clientEntities = Read<uintptr_t>(unk1);
			auto entityRealm = Read<uintptr_t>(clientEntities + 0x10);
			auto bufferList = Read<uintptr_t>(entityRealm + 0x28);
			auto objectList = Read<uintptr_t>(bufferList + 0x18);
			auto objectListSize = Read<uint32_t>(bufferList + 0x10);

			if (Settings::debuglog)
			{
				std::cout << "unk: " << unk1 << std::endl;
				std::cout << "clientEntities " << clientEntities << std::endl;
				std::cout << "entityRealm: " << entityRealm << std::endl;
				std::cout << "bufferList: " << bufferList << std::endl;
				std::cout << "objectList: " << objectList << std::endl;
				std::cout << "objectListSize: " << objectListSize << std::endl;
			}

			for (auto i = 0; i < objectListSize; i++) {
				auto curObject = Read<uintptr_t>(objectList + (0x20 + (i * 8)));
				auto baseObject = Read<uintptr_t>(curObject + 0x10);
				auto object = Read<uintptr_t>(baseObject + 0x30);
				auto tag = Read<WORD>(object + 0x54);
				auto prefebName = ReadNative(object + 0x60);
			
				auto ukn01 = Read<uintptr_t>(baseObject + 0x28);


				auto ukn02 = Read<uintptr_t>(ukn01);

				if (Settings::debuglog)
				{
					std::cout << "curObject: " << curObject << std::endl;
					std::cout << "baseObject: " << baseObject << std::endl;
					std::cout << "object: " << object << std::endl;
					std::cout << "tag: " << tag << std::endl;
					std::cout << "prefebName: " << prefebName << std::endl;
					std::cout << "ukn01: " << ukn01 << std::endl;
				}

				if (!ukn02)
					continue;
				auto entityClass = ReadNative(ukn02 + 0x10);


				if (tag == player) { //6
					auto objectClass = Read<uintptr_t>(object + 0x30);
					auto entity = Read<uintptr_t>(objectClass + 0x18);
					auto transform = Read<uintptr_t>(objectClass + 0x8);

					std::unique_ptr<BaseEntity> BPlayer = std::make_unique<BaseEntity>(entity, transform, object);

					if (BPlayer->isLocalPlayer()) {
						localPlayer->Player = std::make_unique<BaseEntity>(entity, transform, object);
						localPlayer->Movement = std::make_unique<EntityMovment>(localPlayer->Player->player);
					}

					if (!BPlayer->isDead()) t_entList->push_back(*BPlayer); continue;
				}

				
				else if (prefebName.find(safe_str("assets/prefabs/misc/item drop/item_drop_backpack.prefab")) != std::string::npos || prefebName.find(safe_str("assets/prefabs/player/player_corpse.prefab")) != std::string::npos) {
					auto objectClass = Read<uintptr_t>(object + 0x30);
					auto entity = Read<uintptr_t>(objectClass + 0x18);
					auto transform = Read<uintptr_t>(objectClass + 0x8);

					std::unique_ptr<EntityCorpse> CEntity = std::make_unique<EntityCorpse>(entity, transform, object);
					t_corpseList->push_back(*CEntity); continue;
				}

				else if (prefebName.find(safe_str("assets/")) != std::string::npos) {
					if (prefebName.find(safe_str("stone-ore")) != std::string::npos) {
						if (Settings::selectedOres[0] == false) continue;
					}
					else if (prefebName.find(safe_str("metal-ore")) != std::string::npos) {
						if (Settings::selectedOres[1] == false) continue;
					}
					else if (prefebName.find(safe_str("sulfur-ore")) != std::string::npos) {
						if (Settings::selectedOres[2] == false) continue;
					}
					else if (prefebName.find(safe_str("stone-collectable")) != std::string::npos) {
						if (Settings::selectedOres[3] == false) continue;
					}
					else if (prefebName.find(safe_str("metal-collectable")) != std::string::npos) {
						if (Settings::selectedOres[4] == false) continue;
					}
					else if (prefebName.find(safe_str("sulfur-collectable")) != std::string::npos) {
						if (Settings::selectedOres[5] == false) continue;
					}
					else if (prefebName.find(safe_str("wood-collectable")) != std::string::npos) {
						if (Settings::selectedOres[6] == false) continue;
					}
					else if (prefebName.find(safe_str("hemp-collectable")) != std::string::npos || prefebName.find("hemp.entity.prefab") != std::string::npos) {
						if (Settings::selectedOres[7] == false) continue;
					}
					else if (prefebName.find(safe_str("small_stash_deployed")) != std::string::npos) {
						if (Settings::selectedOres[8] == true)
						{
							uintptr_t stashstatus = Read<uintptr_t>(curObject + 0x130);
							if (stashstatus != 2048) continue;
						}
						else continue;
					}
					else if (prefebName.find("loot_barrel_1.prefab") != std::string::npos || prefebName.find("loot_barrel_2.prefab") != std::string::npos || prefebName.find("loot-barrel-1.prefab") != std::string::npos || prefebName.find("loot-barrel-2.prefab") != std::string::npos) {
						if (Settings::selectedOres[9] == false) continue;
					}
					else if (prefebName.find(safe_str("oil_barrel.prefab")) != std::string::npos) {
						if (Settings::selectedOres[10] == false) continue;
					}
					else if (prefebName.find(safe_str("crate_elite.prefab")) != std::string::npos) {
						if (Settings::selectedOres[11] == false) continue;
					}
					else if (prefebName.find(safe_str("crate_normal.prefab")) != std::string::npos) {
						if (Settings::selectedOres[12] == false) continue;
					}
					else if (prefebName.find(safe_str("crate_normal_2_medical.prefab")) != std::string::npos) {
						if (Settings::selectedOres[13] == false) continue;
					}
					else if (prefebName.find(safe_str("crate_normal_2.prefab")) != std::string::npos) {
						if (Settings::selectedOres[14] == false) continue;
					}
					else if (prefebName.find(safe_str("crate_normal_2_food.prefab")) != std::string::npos) {
						if (Settings::selectedOres[15] == false) continue;
					}
					else if (prefebName.find(safe_str("crate_tools.prefab")) != std::string::npos) {
						if (Settings::selectedOres[16] == false) continue;
					}
					else if (prefebName.find(safe_str("rowboat.prefab")) != std::string::npos) {
						if (Settings::selectedOres[17] == false) continue;
					}
					else if (prefebName.find(safe_str("rhib.prefab")) != std::string::npos) {
						if (Settings::selectedOres[18] == false) continue;
					}
					else if (prefebName.find(safe_str("kayak.prefab")) != std::string::npos) {
						if (Settings::selectedOres[19] == false) continue;
					}
					else if (prefebName.find(safe_str("minicopter.entity.prefab")) != std::string::npos) {
						if (Settings::selectedOres[20] == false) continue;
					}
					else if (prefebName.find(safe_str("bradleyapc.prefab")) != std::string::npos) {
						if (Settings::selectedOres[21] == false) continue;
					}
					else continue;

					auto objectClass = Read<uintptr_t>(object + 0x30);
					auto entity = Read<uintptr_t>(objectClass + 0x18);
					auto transform = Read<uintptr_t>(objectClass + 0x8);

					std::unique_ptr<BaseMiscEntity> oreEntity = std::make_unique<BaseMiscEntity>(entity, transform, object);

					t_oreList->push_back(*oreEntity); continue;
				}
				if (entityClass == "DroppedItem")
				{
					auto objectClass = Read<uintptr_t>(object + 0x30);
					auto entity = Read<uintptr_t>(objectClass + 0x18);
					auto transform = Read<uintptr_t>(objectClass + 0x8);

					std::unique_ptr<BaseWeaponESP> weaponEntity = std::make_unique<BaseWeaponESP>(entity, transform, prefebName);

					t_weaponList->push_back(*weaponEntity); continue;
				}
			}

			entityList->clear();
			corpseList->clear();
			oreList->clear();
			weaponList->clear();

			Mutex->PlayerSync->lock();
			*entityList = *t_entList;
			*corpseList = *t_corpseList;
			*oreList = *t_oreList;
			*weaponList = *t_weaponList;
			Mutex->PlayerSync->unlock();
		}
	}
}
#pragma endregion