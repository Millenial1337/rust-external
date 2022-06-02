#pragma once

namespace AutherLibrary
{
	void Initialize(std::string kPublic, std::string kPrivate);
	bool Auth(std::string key, std::string hwid);
	bool CreateLog(std::string key, std::string message, std::string tag);
	std::string ExpireDateTimeStamp();
	std::string ExpireDateHumanReadable();
	std::string GetFullJsonResponse();
	std::string GetHwid();
}