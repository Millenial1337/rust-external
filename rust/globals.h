#pragma once
#include <unordered_map>
#include "DiscordRPC/discordrpc.h"

class c_globals {
public:
	bool auth = false;
	bool init = false;
	char user_name[255] = "";
	char pass_word[255] = "";
};

inline c_globals globals;

namespace glui {
	inline ImVec2 screen_res{ 000, 000 };
}