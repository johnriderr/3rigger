#pragma once
#include <windows.h>
#include <Tlhelp32.h>


namespace Memory 
{
	DWORD getPid(const char* procName);
	DWORD getProcModule(DWORD pid, const char* modName);
}