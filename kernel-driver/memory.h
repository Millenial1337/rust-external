#pragma once
#include "imports.h"

namespace memory {
	PVOID get_system_module_base(const char* module_name) {

		ULONG bytes = 0;
		NTSTATUS status = ZwQuerySystemInformation(SystemModuleInformation, 0, bytes, &bytes);

		if (!bytes)
			return 0;


		PRTL_PROCESS_MODULES modules = (PRTL_PROCESS_MODULES)ExAllocatePoolWithTag(NonPagedPool, bytes, 0x454E4F45); // 'ENON'

		status = ZwQuerySystemInformation(SystemModuleInformation, modules, bytes, &bytes);

		if (!NT_SUCCESS(status))
			return 0;


		PRTL_PROCESS_MODULE_INFORMATION module = modules->Modules;
		PVOID module_base = 0, module_size = 0;

		for (ULONG i = 0; i < modules->NumberOfModules; i++)
		{

			if (strcmp((char*)module[i].FullPathName, module_name) == 0)
			{
				module_base = module[i].ImageBase;
				module_size = (PVOID)module[i].ImageSize;
				break;
			}
		}

		if (modules)
			ExFreePoolWithTag(modules, 0);

		if (module_base <= 0)
			return 0;

		return module_base;
	}

	PVOID get_system_module_export(const char* module_name, LPCSTR routine_name)
	{
		PVOID lpModule = memory::get_system_module_base(module_name);

		if (!lpModule)
			return NULL;

		return RtlFindExportedRoutineByName(lpModule, routine_name);
	}

	bool read_memory(void* address, void* buffer, size_t size) {
		if (!RtlCopyMemory(buffer, address, size)) {
			return false;
		}
		else
		{
			return true;
		}
	}

	bool write_memory(void* address, void* buffer, size_t size) {
		if (!RtlCopyMemory(address, buffer, size)) {
			return false;
		}
		else
		{
			return true;
		}
	}

	bool write_to_read_only_memory(void* address, void* buffer, size_t size) {

		PMDL Mdl = IoAllocateMdl(address, size, FALSE, FALSE, NULL);

		if (!Mdl)
			return false;

		// Locking and mapping memory with RW-rights:
		MmProbeAndLockPages(Mdl, KernelMode, IoReadAccess);
		PVOID Mapping = MmMapLockedPagesSpecifyCache(Mdl, KernelMode, MmNonCached, NULL, FALSE, NormalPagePriority);
		MmProtectMdlSystemAddress(Mdl, PAGE_READWRITE);
		
		// Write your buffer to mapping:
		write_memory(Mapping, buffer, size);

		// Resources freeing:
		MmUnmapLockedPages(Mapping, Mdl);
		MmUnlockPages(Mdl);
		IoFreeMdl(Mdl);

		return true;
	}

	bool call_kernel_function(void* kernel_function_address) {

		PVOID* function = reinterpret_cast<PVOID*>(get_system_module_export("\\SystemRoot\\System32\\drivers\\dxgkrnl.sys", "NtQueryCompositionSurfaceStatistics"));

		if (!function)
			return false;

		if (!kernel_function_address)
			return false;

		BYTE orig[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


		BYTE shell_code[] = { 0x48, 0xB8 }; //mov rax -> | 0xB8 = mov | 0x48 = rax
		BYTE shell_code_middle[] = { 0x40, 0x90, 0x40, 0x90, 0x40, 0x90, 0x40, 0x90 }; //random op codes
		BYTE shell_code_end[] = { 0xFF, 0xE0 }; //jmp rax

		RtlSecureZeroMemory(&orig, sizeof(orig));
		memcpy((PVOID)((ULONG_PTR)orig), &shell_code, sizeof(shell_code));
		uintptr_t hook_address = reinterpret_cast<uintptr_t>(kernel_function_address);
		memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code)), &hook_address, sizeof(void*));
		memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code) + sizeof(void*)), &shell_code_middle, sizeof(shell_code_middle));
		memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code) + sizeof(void*) + sizeof(shell_code_middle)), &shell_code_end, sizeof(shell_code_end));

		write_to_read_only_memory(function, &orig, sizeof(orig));

		return true;
	}

	bool write_kernel_memory(HANDLE pid, uintptr_t address, void* buffer, SIZE_T size) {
		if (!address || !buffer || !size)
			return false;

		NTSTATUS Status = STATUS_SUCCESS;
		PEPROCESS process;
		PsLookupProcessByProcessId(pid, &process);

		KAPC_STATE state;
		KeStackAttachProcess((PKPROCESS)process, &state);

		MEMORY_BASIC_INFORMATION info;

		Status = ZwQueryVirtualMemory(ZwCurrentProcess(), (PVOID)address, MemoryBasicInformation, &info, sizeof(info), NULL);
		if (!NT_SUCCESS(Status)) {
			KeUnstackDetachProcess(&state);
			return false;
		}

		if (((uintptr_t)info.BaseAddress + info.RegionSize) < (address + size))
		{
			KeUnstackDetachProcess(&state);
			return false;
		}

		if (!(info.State & MEM_COMMIT) || (info.Protect & (PAGE_GUARD | PAGE_NOACCESS)))
		{
			KeUnstackDetachProcess(&state);
			return false;
		}

		if ((info.Protect & PAGE_EXECUTE_READWRITE) || (info.Protect & PAGE_EXECUTE_WRITECOPY) || (info.Protect & PAGE_READWRITE) || (info.Protect & PAGE_WRITECOPY))
		{
			RtlCopyMemory((void*)address, buffer, size);
		}
		KeUnstackDetachProcess(&state);
		return true;
	}

	NTSTATUS protect_virtual_memory(ULONG64 pid, PVOID address, ULONG size, ULONG protection, ULONG& protection_out)
	{
		if (!pid || !address || !size || !protection)
			return STATUS_INVALID_PARAMETER;

		NTSTATUS status = STATUS_SUCCESS;
		PEPROCESS target_process = nullptr;

		if (!NT_SUCCESS(PsLookupProcessByProcessId(reinterpret_cast<HANDLE>(pid), &target_process)))
		{
			return STATUS_NOT_FOUND;
		}

		//PVOID address = reinterpret_cast<PVOID>( memory_struct->address );
		//ULONG size = (ULONG)( memory_struct->size );
		//ULONG protection = memory_struct->protection;
		ULONG protection_old = 0;

		KAPC_STATE state;
		KeStackAttachProcess(target_process, &state);

		status = ZwProtectVirtualMemory(NtCurrentProcess(), &address, &size, protection, &protection_old);

		KeUnstackDetachProcess(&state);

		if (NT_SUCCESS(status))
			protection_out = protection_old;

		ObDereferenceObject(target_process);
		return status;
	}

	bool read_kernel_memory(HANDLE pid, uintptr_t address, void* buffer, SIZE_T size) {
		if (!address || !buffer || !size)
			return false;
		SIZE_T bytes = 0;
		NTSTATUS status = STATUS_SUCCESS;
		PEPROCESS process;
		PsLookupProcessByProcessId((HANDLE)pid, &process);

		status = MmCopyVirtualMemory(process, (void*)address, (PEPROCESS)PsGetCurrentProcess(), (void*)buffer, size, KernelMode, &bytes);
		if (!NT_SUCCESS(status))
			return false;
		else
			return true;
	}

	ULONG64 get_module_base_x64(PEPROCESS proc, UNICODE_STRING module_name) {
		PPEB pPeb = PsGetProcessPeb(proc);

		if (!pPeb) {
			return 0; // failed
		}

		KAPC_STATE state;

		KeStackAttachProcess(proc, &state);

		PPEB_LDR_DATA pLdr = (PPEB_LDR_DATA)pPeb->Ldr;

		if (!pLdr) {
			KeUnstackDetachProcess(&state);
			return 0; // failed
		}

		// loop the linked list
		for (PLIST_ENTRY list = (PLIST_ENTRY)pLdr->ModuleListLoadOrder.Flink;
			list != &pLdr->ModuleListLoadOrder; list = (PLIST_ENTRY)list->Flink) {
			PLDR_DATA_TABLE_ENTRY pEntry =
				CONTAINING_RECORD(list, LDR_DATA_TABLE_ENTRY, InLoadOrderModuleList);
			if (RtlCompareUnicodeString(&pEntry->BaseDllName, &module_name, TRUE) ==
				0) {
				ULONG64 baseAddr = (ULONG64)pEntry->DllBase;
				KeUnstackDetachProcess(&state);
				return baseAddr;
			}
		}
		KeUnstackDetachProcess(&state);

		return 0;
	}
}