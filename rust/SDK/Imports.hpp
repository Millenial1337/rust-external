#pragma once
#include <msxml.h>
#include <atomic>
#include <mutex>
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <vector>
#include <random>
#include <memoryapi.h>
#include <xstring>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#include <string_view>
#include <d3d9.h>
#include <dwmapi.h>
#include <xlocbuf>
#include <codecvt>
#include <xmmintrin.h>
#include <emmintrin.h>
#include "VMProtectSDK.h"

#define safe_str(x) VMProtectDecryptStringA(x)
#define safe_strW(x) VMProtectDecryptStringW(x)

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

const unsigned int screenWidth = GetSystemMetrics(SM_CXSCREEN);
const unsigned int screenHeight = GetSystemMetrics(SM_CYSCREEN);