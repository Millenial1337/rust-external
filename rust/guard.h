#pragma once
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "Advapi32.lib") 
#include "include.h"
#include "xorstr.hpp"

using namespace std;

string GetHwUID()
{
	HW_PROFILE_INFO hwProfileInfo;
	string szHwProfileGuid = "";

	if (GetCurrentHwProfileA(&hwProfileInfo) != NULL)
		szHwProfileGuid = hwProfileInfo.szHwProfileGuid;

	return szHwProfileGuid;
}

string GetCompUserName(bool User)
{
	string CompUserName = "";

	char szCompName[MAX_COMPUTERNAME_LENGTH + 1];
	char szUserName[MAX_COMPUTERNAME_LENGTH + 1];

	DWORD dwCompSize = sizeof(szCompName);
	DWORD dwUserSize = sizeof(szUserName);

	if (GetComputerNameA(szCompName, &dwCompSize))
	{
		CompUserName = szCompName;

		if (User && GetUserNameA(szUserName, &dwUserSize))
		{
			CompUserName = szUserName;
		}
	}

	return CompUserName;
}

string StringToHex(const string input)
{
	const char* lut = "0123456789ABCDEF";
	size_t len = input.length();
	string output = "";

	output.reserve(2 * len);

	for (size_t i = 0; i < len; i++)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}

	return output;
}

DWORD GetVolumeID()
{
	DWORD VolumeSerialNumber;

	BOOL GetVolumeInformationFlag = GetVolumeInformationA(
		"c:\\",
		0,
		0,
		&VolumeSerialNumber,
		0,
		0,
		0,
		0
	);

	if (GetVolumeInformationFlag)
		return VolumeSerialNumber;

	return 0;
}

string GetSerialKey()
{
	string SerialKey = "61A345B5496B2";
	string CompName = GetCompUserName(false);
	string UserName = GetCompUserName(true);

	SerialKey.append(StringToHex(GetHwUID()));
	SerialKey.append("-");
	SerialKey.append(StringToHex(to_string(GetVolumeID())));
	SerialKey.append("-");
	SerialKey.append(StringToHex(CompName));
	SerialKey.append("-");
	SerialKey.append(StringToHex(UserName));

	return SerialKey;
}
bool SpectroFobia = true;
bool Revenger = false;
bool Diss = false;

string GetHashText(const void* data, const size_t data_size)
{
	HCRYPTPROV hProv = NULL;

	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		return "";
	}

	BOOL hash_ok = FALSE;
	HCRYPTPROV hHash = NULL;

	hash_ok = CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash);

	if (!hash_ok)
	{
		CryptReleaseContext(hProv, 0);
		return "";
	}

	if (!CryptHashData(hHash, static_cast<const BYTE*>(data), data_size, 0))
	{
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return "";
	}

	DWORD cbHashSize = 0, dwCount = sizeof(DWORD);
	if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)&cbHashSize, &dwCount, 0))
	{
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return "";
	}

	vector<BYTE> buffer(cbHashSize);

	if (!CryptGetHashParam(hHash, HP_HASHVAL, reinterpret_cast<BYTE*>(&buffer[0]), &cbHashSize, 0))
	{
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return "";
	}

	ostringstream oss;

	for (vector<BYTE>::const_iterator iter = buffer.begin(); iter != buffer.end(); ++iter)
	{
		oss.fill('0');
		oss.width(2);
		oss << hex << static_cast<const int>(*iter);
	}

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	return oss.str();
}

string GetHashSerialKey()
{
	string SerialKey = GetSerialKey();
	const void* pData = SerialKey.c_str();
	size_t Size = SerialKey.size();
	string Hash = GetHashText(pData, Size);

	for (auto& c : Hash)
	{
		if (c >= 'a' && c <= 'f')
		{
			c = '4';
		}
		else if (c == 'b')
		{
			c = '5';
		}
		else if (c == 'c')
		{
			c = '6';
		}
		else if (c == 'd')
		{
			c = '7';
		}
		else if (c == 'e')
		{
			c = '8';
		}
		else if (c == 'f')
		{
			c = '9';
		}

		c = toupper(c);
	}

	return Hash;
}

string GetSerial()
{
	string Serial = "";
	string HashSerialKey = GetHashSerialKey();

	string Serial1 = HashSerialKey.substr(0, 4);
	string Serial2 = HashSerialKey.substr(4, 4);
	string Serial3 = HashSerialKey.substr(8, 4);
	string Serial4 = HashSerialKey.substr(12, 4);

	Serial += Serial1;
	Serial += '-';
	Serial += Serial2;
	Serial += '-';
	Serial += Serial3;
	Serial += '-';
	Serial += Serial4;

	return Serial;
}

string valid[] =
{
	(" ")
};
const char* user_names[] =
{
	" "
};

#define PATH "/WebPanel/"
#define HOST ("vos9.xyz")
#define HOST2 ("vos9.xyz")
static const string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

string base64_encode(char const* bytes_to_encode, unsigned int in_len)
{
	string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--)
	{
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;
}

string GetSerial64()
{
	string Serial = GetSerial();
	Serial = base64_encode(Serial.c_str(), Serial.size());
	return Serial;
}

string GetUrlData(string url)
{
	string request_data = "";

	HINTERNET hIntSession = InternetOpenA("", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (!hIntSession)
	{
		return request_data;
	}

	HINTERNET hHttpSession = InternetConnectA(hIntSession, xorstr_(HOST), 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);

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

string GetUrlDataSpectro(string url)
{
	string request_data = "";

	HINTERNET hIntSession = InternetOpenA("", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (!hIntSession)
	{
		return request_data;
	}

	HINTERNET hHttpSession = InternetConnectA(hIntSession, xorstr_(HOST2), 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);

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

bool Inject = false;
bool CheckLicense()
{
	string Serial = GetSerial64();

	string UrlRequest = xorstr_(PATH);
	UrlRequest.append(xorstr_("gate.php?serial=") + Serial);

	string ReciveHash = GetUrlData(UrlRequest);

	if (ReciveHash.size())
	{
		string LicenseOK = (xorstr_("license-success-ok-")) + Serial + (xorstr_("-"));

		for (int RandomMd5 = 1; RandomMd5 <= 10; RandomMd5++)
		{
			string LicenseCheck = LicenseOK + to_string(RandomMd5);
			string LicenseOKHash = GetHashText(LicenseCheck.c_str(), LicenseCheck.size());

			if (ReciveHash == LicenseOKHash)
			{
				Inject = true;
				return true;
				break;
			}
			break;
		}
	}
		exit(0);
	for (int i = 0; i < sizeof(valid); i++)
	{
		if (valid[i] == GetSerial())
		{

			return true;
		}
	}
	return false;

}

bool CheckLicenseSpectro()
{
	std::string Serial = GetSerial64();

	std::string UrlRequest = PATH;
	UrlRequest.append(xorstr_("gate.php?serial=") + Serial);

	std::string ReciveHash = GetUrlDataSpectro(UrlRequest);

	if (ReciveHash.size())
	{
		std::string LicenseOK = ("license-success-ok-") + Serial + "-";

		for (int RandomMd5 = 1; RandomMd5 <= 10; RandomMd5++)
		{
			std::string LicenseCheck = LicenseOK + std::to_string(RandomMd5);
			std::string LicenseOKHash = GetHashText(LicenseCheck.c_str(), LicenseCheck.size());

			if (ReciveHash == LicenseOKHash)
			{
				break;
			}
			break;
		}
	}

	/*for (int i = 0; i < sizeof(valid); i++)
	{
	if (valid[i] == GetSerial())
	{

	return true;
	}
	}
	return false;
	*/
}

string GetUserDayCount()
{
	string Serial = GetSerial64();

	string UrlRequest = PATH;
	UrlRequest.append(xorstr_("gate.php?day=") + Serial);

	static string ReciveDay = GetUrlData(UrlRequest);
	return ReciveDay;
}

string GetVer()
{
	//while (true) {
		string web_req = PATH;
		web_req.append(xorstr_("gate.php?version=ok"));
		return GetUrlData(web_req);
		//break;
	//}
}

string GetInfo()
{
	//while (true) {
		string web_req = PATH;
		web_req.append(xorstr_("info.php"));
		return GetUrlData(web_req);
		//break;
	//}
}