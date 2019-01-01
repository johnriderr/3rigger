#include "stdafx.h"
#include "Memory.h"
#include "CSGO.h"
#include "Offsets.h"

void CSGO::init(const char* procName)
{
	DWORD pid = Memory::getPid(procName);
	_hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	_gameModuleBaseAddr = Memory::getProcModule(pid, "client_panorama.dll");

	ReadProcessMemory(_hProcess,
		(LPCVOID)(_gameModuleBaseAddr + Offsets::dwLocalPlayer),
		&_localPlayer,
		sizeof(_localPlayer),
		NULL);
}

bool CSGO::isPlayerOnTheGround()
{
	BYTE flag;
	ReadProcessMemory(_hProcess,
		(LPCVOID)(_localPlayer + Offsets::m_fFlags),
		&flag,
		sizeof(flag),
		NULL);

	if (flag & (1 << 0))
		return true;
	return false;
}

void CSGO::jump()
{
	int n = 6;
	WriteProcessMemory(_hProcess,
		(LPVOID)(_gameModuleBaseAddr + Offsets::dwForceJump),
		&n,
		sizeof(int),
		NULL);
}

CSGO::CSGO()
{
}

CSGO::~CSGO()
{
}