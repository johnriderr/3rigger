#include "stdafx.h"
#include "Memory.h"
#include <windows.h>
#include <Tlhelp32.h>

namespace Memory 
{
	DWORD getPid(const char* procName)
	{
		DWORD pid = 0;
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (Process32First(snapshot, &entry) == TRUE)
		{
			while (Process32Next(snapshot, &entry) == TRUE)
			{
				if (strcmp(entry.szExeFile, procName) == 0)
				{
					pid = entry.th32ProcessID;
				}
			}
		}

		CloseHandle(snapshot);
		return pid;
	}
	DWORD getProcModule(DWORD pid, const char* modName)
	{
		DWORD hModule = 0;
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	
		if (hSnapshot != INVALID_HANDLE_VALUE)
		{
			MODULEENTRY32 mEntry32 = { 0 };
			mEntry32.dwSize = sizeof(MODULEENTRY32);
			if (Module32First(hSnapshot, &mEntry32))
			{
				do
				{
					if (!strcmp(mEntry32.szModule, modName))
					{						
						hModule = (DWORD)mEntry32.hModule;
						break;
					}

				} while (Module32Next(hSnapshot, &mEntry32));
			}
			CloseHandle(hSnapshot);
		}
		return hModule;
	}

}