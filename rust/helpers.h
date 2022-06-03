#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <Shlwapi.h>
#include <random>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <WinInet.h>
#include <iomanip>
#include <cstdio> 
#include <WinUser.h>
#include "wininet.h"
#include <WinBase.h>
#include <tchar.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "Advapi32.lib") 

#define PATH "/"
#define HOST ("risex.xyz")

using namespace std;

string GetUrlData(string url)
{
	string request_data = "";

	HINTERNET hIntSession = InternetOpenA("", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (!hIntSession)
	{
		return request_data;
	}

	HINTERNET hHttpSession = InternetConnectA(hIntSession, HOST, 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);

	if (!hHttpSession)
	{
		return request_data;
	}

	HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", url.c_str()
		, 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	if (!hHttpSession)
	{
		return request_data;
	}

	const char* szHeaders = ("Content-Type: text/html\r\nUser-Agent: License");
	char szRequest[1024] = { 0 };

	if (!HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szRequest, strlen(szRequest)))
	{
		return request_data;
	}

	CHAR szBuffer[1024] = { 0 };
	DWORD dwRead = 0;

	while (InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer) - 1, &dwRead) && dwRead)
	{
		request_data.append(szBuffer, dwRead);
	}

	InternetCloseHandle(hHttpRequest);
	InternetCloseHandle(hHttpSession);
	InternetCloseHandle(hIntSession);

	return request_data;
}

/*std::string GetVer()
{
	//while (true) {
	std::string web_req = PATH;
	web_req.append("gate.php?version=ok");
	return GetUrlData(web_req);
	//break;
//}
}*/

string GetInfo()
{
	//while (true) {
	string web_req = PATH;
	web_req.append("info.php");
	return GetUrlData(web_req);
	//break;
//}
}