#include "SDK/Classes.hpp"
#include "Features/ESP/ESP.hpp"
#include "Overlay/Overlay.hpp"
#include "SDK/BasePlayer.hpp"
#include "Features/Aimbot/DoAimbot.hpp"
#include "Features/MISC/DoMisc.hpp"
#include "Entity/EntityLoop.hpp"
#include <xstring>
#include "log.h"
#include "lazy_importer.h"
//#include "antdebug.h"

void Hide()
{
	HWND Hide;
	LI_FN(AllocConsole)();
	Hide = FindWindowA("ConsoleWindowClass", NULL);
	LI_FN(ShowWindow)(Hide, 0);
}

void Brrp()
{
	Beep(247, 500);
	Beep(417, 500);
	Beep(417, 500);
	Beep(370, 500);
	Beep(417, 500);
	Beep(329, 500);
	Beep(247, 500);
	Beep(247, 500);
	Beep(247, 500);
	Beep(417, 500);
	Beep(417, 500);
	Beep(370, 500);
	Beep(417, 500);
	Beep(497, 500);
	Sleep(500);
	Beep(497, 500);
	Beep(277, 500);
	Beep(277, 500);
	Beep(440, 500);
	Beep(440, 500);
	Beep(417, 500);
	Beep(370, 500);
	Beep(329, 500);
	Beep(247, 500);
	Beep(417, 500);
	Beep(417, 500);
	Beep(370, 500);
	Beep(417, 500);
	Beep(329, 500);
}


int main()
{
	LI_FN(ShowWindow)(GetConsoleWindow(), SW_HIDE);
	SetConsoleTitle("A-P");
	HWND hwnd = nullptr;

	//start_log();

	try
	{
		CleanPIDDBCacheTable();

		std::cout << safe_str("Launch Rust") << std::endl;

		while (!hwnd)
		{
			hwnd = FindWindowA(safe_str("UnityWndClass"), safe_str("Rust")); //UnityWndClass  Rust
			//hwnd = FindWindowA(safe_str("CDownloadTracker f20000"), safe_str("JavaUpdate SysTray Icon"));
			LI_FN(Sleep)(50);
		}

		std::cout << safe_str("Game has been found! Press F1 when game loads in!") << std::endl;

		while (true)
		{
			if (GetAsyncKeyState(VK_F1))
				break;
			LI_FN(Sleep)(50);
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
		gBase = get_module_base_address(safe_str("GameAssembly.dll"));
		uBase = get_module_base_address(safe_str("UnityPlayer.dll"));
		//injection_log();
//		Brrp();
//		Hide();
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