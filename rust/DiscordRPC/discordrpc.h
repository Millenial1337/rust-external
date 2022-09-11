#pragma once
#include "includes/discord_register.h"
#include "includes/discord_rpc.h"
#include <Windows.h>

class Discord {
public:
    void Initialize();
    void Update();
    void State(const char* state);
    void Details(const char* details);
};