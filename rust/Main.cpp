#include "SDK/Classes.hpp"
#include "Features/ESP/ESP.hpp"
#include "Overlay/Overlay.hpp"
#include "SDK/BasePlayer.hpp"
#include "Features/Aimbot/DoAimbot.hpp"
#include "Features/MISC/DoMisc.hpp"
#include "Entity/EntityLoop.hpp"
#include <xstring>
#include "lazy_importer.h"
#include "AuthLib/AutherLibrary.h"
#include "globals.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "libcurl_a.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Normaliz.lib")

int main()
{	
	SetConsoleTitle("A-P");
	HWND hwnd = nullptr;

	//AutherLibrary::Initialize(safe_str("maWwK5sbjUOGpuBHF8SeDtfENdTC1rlI"), safe_str("oCA7K4GerUvgy6u8DdsnT9ShfjPl1Bcm"));

	LI_FN(ShowWindow)(GetConsoleWindow(), SW_SHOW);

	try
	{
		CleanPIDDBCacheTable();

		while (!hwnd)
		{
			//hwnd = FindWindowA(safe_str("UnityWndClass"), safe_str("Rust")); //UnityWndClass  Rust
			//hwnd = LI_FN(FindWindowA)(safe_str("Chrome_WidgetWin_1"), safe_str("GitHub Desktop"));
			hwnd = LI_FN(FindWindowA)(safe_str("UnityWndClass"), safe_str("Rust"));
			LI_FN(Sleep)(50);
		}

		//start_log();

		while (true)
		{
			if (LI_FN(GetAsyncKeyState)(VK_F5))
				break;
			LI_FN(Sleep)(50);
			globals.init = true;
		}

		Mutex = std::make_unique<_Mutex>();

		Mutex->PlayerSync = std::make_unique<sf::contention_free_shared_mutex<>>();
		Mutex->WriteSync = std::make_unique<sf::contention_free_shared_mutex<>>();

		entityList = std::make_unique<std::vector<BaseEntity>>();
		corpseList = std::make_unique<std::vector<EntityCorpse>>();
		oreList = std::make_unique<std::vector<BaseMiscEntity>>();
		weaponList = std::make_unique<std::vector<BaseWeaponESP>>();
		localPlayer = std::make_unique<LocalPlayer>();

		pId = get_process_id(safe_str("RustClient.exe"));
		std::cout << "PID: " << pId << std::endl;
		gBase = get_module_base_address(safe_str("GameAssembly.dll"));
		std::cout << "GameAssemblyBase: " << gBase << std::endl;
		uBase = get_module_base_address(safe_str("UnityPlayer.dll"));
		std::cout << "UnityPlayerBase: " << uBase << std::endl;
		std::thread overlay_thread(Overlay::Loop);
		std::thread entity_thread(Entity::EntityLoop);
		std::thread aimbot_thread(Aimbot::DoAimbot);
		std::thread misc_thread(Misc::DoMisc);

		overlay_thread.join();
	}
	catch (std::exception e)
	{
		std::cerr << safe_str("error occurred: ") << e.what() << std::endl;
	}
}