#ifndef _DRIVER_HPP
#define _DRIVER_HPP

#include <Windows.h>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <TlHelp32.h>

typedef struct _COPY_MEMORY
{
	void* bufferAddress;
	UINT_PTR  address;
	ULONGLONG  size;
	ULONG     pid;
	BOOLEAN   write;
	BOOLEAN  ReqBase;
	ULONG64 BaseAddress;
	void* Output;
	BOOLEAN ClearPIDCache;
	BOOLEAN PIDCacheCleared;
	BOOLEAN Read;
	BOOLEAN ReadString;
	BOOLEAN WriteString;
	const char* moduleName;
	ULONG pid_ofSource;

	BOOLEAN		change_protection;
	ULONG		protection;
	ULONG		protection_old;
} COPY_MEMORY;

static std::uint32_t pId = 0;
static uintptr_t gBase = 0;
static uintptr_t uBase = 0;

struct HandleDisposer
{
	using pointer = HANDLE;

	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
			CloseHandle(handle);
	}
};

using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

static std::uint32_t __fastcall get_process_id(std::string_view process_name)
{
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return 0;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE) {
		if (process_name.compare(processentry.szExeFile) == 0)
			return processentry.th32ProcessID;
	}
	return 0;
}

template<typename ... A>
uint64_t __fastcall call_hook(const A ... arguments)
{
	LoadLibrary("user32.dll");
	void* control_function = GetProcAddress(LoadLibrary("win32u.dll"), "NtQueryCompositionSurfaceStatistics");

	const auto control = static_cast<uint64_t(__stdcall*)(A...)>(control_function);

	return control(arguments ...);
}

static ULONG64 __fastcall change_protection(uint64_t pid, uint64_t address, uint32_t page_protection, std::size_t size)
{
	COPY_MEMORY __fastcall m = { 0 };

	m.pid = pId;
	m.address = address;
	m.protection = page_protection;
	m.size = size;
	m.change_protection = TRUE;
	m.ReqBase = FALSE;
	m.ClearPIDCache = FALSE;
	m.Read = FALSE;
	m.ReadString = FALSE;
	m.write = FALSE;
	m.WriteString = FALSE;

	return call_hook(&m);
}

static ULONG64 __fastcall get_module_base_address(const char* moduleName)
{
	COPY_MEMORY __fastcall m = { 0 };

	m.pid = pId;
	m.ReqBase = TRUE;
	m.ClearPIDCache = FALSE;
	m.Read = FALSE;
	m.ReadString = FALSE;
	m.write = FALSE;
	m.WriteString = FALSE;
	m.moduleName = moduleName;
	call_hook(&m);

	ULONG64 base = NULL;
	base = m.BaseAddress;
	return base;
}

template <class T>
T __fastcall Read(UINT_PTR ReadAddress)
{
	T response{};

	COPY_MEMORY __fastcall m = { 0 };

	m.pid = pId;
	m.size = sizeof(T);
	m.address = ReadAddress;
	m.Read = TRUE;
	m.ReadString = FALSE;
	m.WriteString = FALSE;
	m.write = FALSE;
	m.ReqBase = FALSE;
	m.ClearPIDCache = FALSE;
	m.Output = &response;
	call_hook(&m);

	return response;
}

template <typename Type>
Type ReadChain(uint64_t address, std::vector<uint64_t> chain) {
	uint64_t current = address;
	for (int i = 0; i < chain.size() - 1; i++) {
		current = Read<uint64_t>(current + chain[i]);
	}
	return Read<Type>(current + chain[chain.size() - 1]);
}

static bool __fastcall WriteVirtualMemoryRaw(UINT_PTR WriteAddress, UINT_PTR SourceAddress, SIZE_T WriteSize);

template<typename S>
bool __fastcall Write(UINT_PTR WriteAddress, const S& value)
{
	return WriteVirtualMemoryRaw(WriteAddress, (UINT_PTR)&value, sizeof(S));
}

bool __fastcall WriteVirtualMemoryRaw(UINT_PTR WriteAddress, UINT_PTR SourceAddress, SIZE_T WriteSize)
{
	COPY_MEMORY __fastcall m = { 0 };

	m.address = WriteAddress;
	m.pid = pId;
	m.pid_ofSource = GetCurrentProcessId();
	m.write = TRUE;
	m.ClearPIDCache = FALSE;
	m.Read = FALSE;
	m.ReadString = FALSE;
	m.ReqBase = FALSE;
	m.WriteString = FALSE;
	m.bufferAddress = (void*)SourceAddress;
	m.size = WriteSize;

	call_hook(&m);

	return true;
}

static BOOLEAN __fastcall CleanPIDDBCacheTable()
{
	COPY_MEMORY __fastcall m = { 0 };

	m.ClearPIDCache = TRUE;
	m.Read = FALSE;
	m.WriteString = FALSE;
	m.write = FALSE;
	m.ReqBase = FALSE;
	m.ReadString = FALSE;
	call_hook(&m);

	return m.PIDCacheCleared;
}

static void __fastcall ReadString(UINT_PTR String_address, void* buffer, SIZE_T size)
{
	COPY_MEMORY __fastcall m = { 0 };

	m.pid = pId;
	m.ReadString = TRUE;
	m.Read = FALSE;
	m.ClearPIDCache = FALSE;
	m.ReqBase = FALSE;
	m.write = FALSE;
	m.WriteString = FALSE;
	m.address = String_address;
	m.bufferAddress = buffer;
	m.size = size;

	call_hook(&m);
}

static void __fastcall WriteString(UINT_PTR String_address, void* buffer, SIZE_T size)
{
	COPY_MEMORY __fastcall m = { 0 };

	m.pid = pId;
	m.WriteString = TRUE;
	m.ClearPIDCache = FALSE;
	m.Read = FALSE;
	m.ReadString = FALSE;
	m.ReqBase = FALSE;
	m.write = FALSE;
	m.address = String_address;
	m.bufferAddress = buffer;
	m.size = size;

	call_hook(&m);
}

std::wstring ReadUnicode(uint64_t address) {
	wchar_t buffer[1024 * sizeof(wchar_t)];

	ReadString(address, &buffer, 1024 * sizeof(wchar_t));

	return std::wstring(buffer);
}

std::string ReadNative(uint64_t address)
{
	char buffer[1024];

	ReadString(Read<uint64_t>(address), &buffer, 1024);

	return std::string(buffer);
}

static uint64_t __fastcall IL2CPPScan(const char* class_name)
{
	uint64_t base = gBase;
	IMAGE_DOS_HEADER dos_header = Read<IMAGE_DOS_HEADER>(base);
	IMAGE_SECTION_HEADER data_header = Read<IMAGE_SECTION_HEADER>(base + dos_header.e_lfanew + sizeof(IMAGE_NT_HEADERS64) + (3 * 40));
	IMAGE_SECTION_HEADER next_section = Read<IMAGE_SECTION_HEADER>(base + dos_header.e_lfanew + sizeof(IMAGE_NT_HEADERS64) + (4 * 40));
	DWORD data_size = next_section.VirtualAddress - data_header.VirtualAddress;

	if (strcmp((char*)data_header.Name, ".data"))
		return 0;

	for (uint64_t offset = data_size; offset > 0; offset -= 8) {
		char klass_name[0x100] = { 0 };
		auto klass = Read<uint64_t>(base + data_header.VirtualAddress + offset);
		if (klass == 0) continue;

		auto name_pointer = Read<uint64_t>(klass + 0x10);
		if (name_pointer == 0) continue;
		ReadString(name_pointer, klass_name, sizeof(klass_name));

		if (!strcmp(klass_name, class_name))
			return klass;
	}

	return 0;
}

#endif