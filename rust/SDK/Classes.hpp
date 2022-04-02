#pragma once
#include "Utils.hpp"
#include "safe_ptr.hpp"

enum Tag : int
{
	main_camera = 5,
	player = 6,
	terrain = 20001,
	misc = 20006,
	animal = 20008,
	corpse = 20009,
	monument = 20015,
	helicopter = 20017, // ???
	skydometag = 20011
};

struct _Mutex {
	std::unique_ptr<sf::contention_free_shared_mutex<>> PlayerSync;
	std::unique_ptr<sf::contention_free_shared_mutex<>> WriteSync;
}; std::unique_ptr<_Mutex> Mutex;