#include "xorstr.hpp"
#include <debugapi.h>
#include <WinUser.h>
#include "log.h"

namespace Protection {
	bool GetWindowClass(LPCSTR wndclass, LPCSTR wndtitle) { //»щет класс и лейбл, но не зависит от обоих аргументов в отличии от FindWindow
		if (FindWindowA(wndclass, 0) || FindWindowA(0, wndtitle))
			return true;
		return false;
	}
	__forceinline bool CheckProcess()
	{
		std::string szProcesses[] =
		{
			xorstr_("HttpAnalyzerStdV5.exe"),
			xorstr_("ollydbg.exe"),
			xorstr_("x64dbg.exe"),
			xorstr_("x32dbg.exe"),
			xorstr_("die.exe"),
			xorstr_("tcpview.exe"),			// Part of Sysinternals Suite
			xorstr_("autoruns.exe"),			// Part of Sysinternals Suite
			xorstr_("autorunsc.exe"),		// Part of Sysinternals Suite
			xorstr_("filemon.exe"),			// Part of Sysinternals Suite
			xorstr_("procmon.exe"),			// Part of Sysinternals Suite
			xorstr_("regmon.exe"),			// Part of Sysinternals Suite
			xorstr_("procexp.exe"),			// Part of Sysinternals Suite
			xorstr_("idaq.exe"),				// IDA Pro Interactive Disassembler
			xorstr_("idaq64.exe"),			// IDA Pro Interactive Disassembler
			xorstr_("ida.exe"),				// IDA Pro Interactive Disassembler
			xorstr_("ida64.exe"),			// IDA Pro Interactive Disassembler
			xorstr_("ImmunityDebugger.exe"), // ImmunityDebugger
			xorstr_("Wireshark.exe"),		// Wireshark packet sniffer
			xorstr_("dumpcap.exe"),			// Network traffic dump tool
			xorstr_("HookExplorer.exe"),		// Find various types of runtime hooks
			xorstr_("ImportREC.exe"),		// Import Reconstructor
			xorstr_("PETools.exe"),			// PE Tool
			xorstr_("LordPE.exe"),			// LordPE
			xorstr_("dumpcap.exe"),			// Network traffic dump tool
			xorstr_("SysInspector.exe"),		// ESET SysInspector
			xorstr_("proc_analyzer.exe"),	// Part of SysAnalyzer iDefense
			xorstr_("sysAnalyzer.exe"),		// Part of SysAnalyzer iDefense
			xorstr_("sniff_hit.exe"),		// Part of SysAnalyzer iDefense
			xorstr_("windbg.exe"),			// Microsoft WinDbg
			xorstr_("joeboxcontrol.exe"),	// Part of Joe Sandbox
			xorstr_("joeboxserver.exe"),		// Part of Joe Sandbox
			xorstr_("fiddler.exe"),
			xorstr_("tv_w32.exe"),
			xorstr_("tv_x64.exe"),
			xorstr_("Charles.exe"),
			xorstr_("netFilterService.exe"),
			xorstr_("HTTPAnalyzerStdV7.exe")
		};
		return false;
	}
	bool AntiDebug() {
		if (IsDebuggerPresent())
		{
			debug_log();
			return true;
		}
		return false;
	}
	__forceinline BOOL AntiVirtualize(void)
	{
		return GetSystemMetrics(SM_REMOTESESSION);
	}
	bool CheckWindows() {
		if (GetWindowClass(xorstr_("XTPMainFrame"), xorstr_("HTTP Debugger"))) {
			//debug_log();
			return true;
		}
		return false;
	}
	void AllChecks() {
		CheckProcess();
		AntiDebug();
		AntiVirtualize();
		CheckWindows();
	}
}