#pragma once
#include <unordered_map>

class c_globals {
public:
	bool auth = false;
	bool started = false;
	char key[255] = "";
};

inline c_globals globals;

namespace glui {
	inline ImVec2 screen_res{ 000, 000 };
	inline const char* title = "main";
	inline DWORD imflags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
}