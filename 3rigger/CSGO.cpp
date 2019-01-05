#include "stdafx.h"
#include "Memory.h"
#include "CSGO.h"
#include "Offsets.h"
#include <iostream>

void CSGO::init(const char* procName)
{
	bHopEnabled = false;

	DWORD pid = Memory::getPid(procName);
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	gameModuleBaseAddr = Memory::getProcModule(pid, "client_panorama.dll");

	ReadProcessMemory(hProcess,
		(LPCVOID)(gameModuleBaseAddr + Offsets::dwLocalPlayer),
		&localPlayer,
		sizeof(localPlayer),
		NULL);
}

bool CSGO::playerOnTheGround()
{
	BYTE flag;
	ReadProcessMemory(hProcess,
		(LPCVOID)(localPlayer + Offsets::m_fFlags),
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
	WriteProcessMemory(hProcess,
		(LPVOID)(gameModuleBaseAddr + Offsets::dwForceJump),
		&n,
		sizeof(int),
		NULL);
}

void CSGO::shoot()
{
	int n = 5;
	WriteProcessMemory(hProcess,
		(LPVOID)(gameModuleBaseAddr + Offsets::dwForceAttack),
		&n,
		sizeof(int),
		NULL);
	Sleep(50);
	int n1 = 4;
	WriteProcessMemory(hProcess,
		(LPVOID)(gameModuleBaseAddr + Offsets::dwForceAttack),
		&n1,
		sizeof(int),
		NULL);

}

void CSGO::bHop()
{
	while (true)
	{
		if (bHopEnabled && playerOnTheGround())
		{
			jump();
		}
		Sleep(5);
	}
}

int CSGO::getCrosshair()
{
	int crosshair;

	ReadProcessMemory(hProcess,
		(LPCVOID)(localPlayer + Offsets::m_iCrosshairId),
		&crosshair,
		sizeof(crosshair),
		NULL);

	return crosshair;
}

void CSGO::triggerBot()
{
	while (true)
	{
		int crosshair = getCrosshair();
		if (triggerBotEnabled && crosshair != 0 && crosshair < 64)
		{
			DWORD entity;
			ReadProcessMemory(hProcess,
				(LPCVOID)(gameModuleBaseAddr + Offsets::dwEntityList + ((crosshair - 1) * 0x10)),
				&entity,
				sizeof(entity),
				NULL);

			int eTeam;
			ReadProcessMemory(hProcess,
				(LPCVOID)(entity + Offsets::m_iTeamNum),
				&eTeam,
				sizeof(eTeam),
				NULL);


			if (eTeam != myTeam)
			{
				shoot();
				Sleep(50);
			}
		}
		Sleep(3);
	}
}

void CSGO::updateLocalPlayer()
{
	while (true)
	{
		ReadProcessMemory(hProcess,
			(LPCVOID)(gameModuleBaseAddr + Offsets::dwLocalPlayer),
			&localPlayer,
			sizeof(localPlayer),
			NULL);

		ReadProcessMemory(hProcess,
			(LPCVOID)(localPlayer + Offsets::m_iTeamNum),
			&myTeam,
			sizeof(myTeam),
			NULL);

		Sleep(1000);
	}

	

}

CSGO::CSGO()
{

}

CSGO::~CSGO()
{
}