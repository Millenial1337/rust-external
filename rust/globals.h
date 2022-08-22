#pragma once
#include <unordered_map>

class c_globals {
public:
	bool auth = true;
	bool started = false;
	char key[255] = "";
};

inline c_globals globals;

namespace glui {
	inline ImVec2 screen_res{ 000, 000 };
}