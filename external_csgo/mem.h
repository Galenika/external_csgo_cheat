#pragma once
#include "main.h"

class c_mem
{
public:
	static auto instance() -> c_mem* {
		static c_mem* instance = new c_mem;
		return instance;
	}

	auto init(const char* proc) -> void {
		HANDLE h_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		PROCESSENTRY32 proc_entry;
		proc_entry.dwSize = sizeof(proc_entry);
		do
			if (strstr(proc_entry.szExeFile, proc))
			{
				proc_id = proc_entry.th32ProcessID;
				CloseHandle(h_snap);
				return;
			}
		while (Process32Next(h_snap, &proc_entry));

		printf("Couldn't find %s\n", proc);
		system("pause");
		exit(0);
	}

	auto get_module_base(std::string module) -> DWORD {
		MODULEENTRY32 mod_entry = { 0 };
		mod_entry.dwSize = sizeof(mod_entry);
		HANDLE h_module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, proc_id);
		BOOL mod = Module32First(h_module, &mod_entry);
		while (mod)
		{
			if (!strcmp(mod_entry.szModule, module.c_str()))
			{
				CloseHandle(h_module);
				return (DWORD)mod_entry.modBaseAddr;
			}
			mod = Module32Next(h_module, &mod_entry);
		}

		CloseHandle(h_module);
		printf("Couldn't get %s\n", module.c_str());
		return 0;
	}

	template <class t>
	t read_mem(DWORD address) {
		t read;
		ReadProcessMemory(handle, (LPVOID)address, &read, sizeof(t), NULL);
		return read;
	}
};