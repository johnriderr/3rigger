#pragma once
#include <windows.h>
#include <Tlhelp32.h>


namespace Memory 
{
	DWORD getPid(const char* procName);
	DWORD getProcModule(DWORD pid, const char* modName);

	template <typename T>
	T readProcMemory(HANDLE h, DWORD addr)
	{
		T val;
		ReadProcessMemory(h, (LPVOID)addr, &val, sizeof(val), NULL);
		return val;
	}

	template <typename T>
	void writeProcMemory(HANDLE h, DWORD addr, T val)
	{
		WriteProcessMemory(h, (LPVOID)addr, &val, sizeof(val), NULL);
	}
}