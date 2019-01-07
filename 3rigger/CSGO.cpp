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
	localPlayer = Memory::readProcMemory<DWORD>(hProcess, gameModuleBaseAddr + Offsets::dwLocalPlayer);
}

bool CSGO::playerOnTheGround()
{
	BYTE flag = Memory::readProcMemory<BYTE>(hProcess, localPlayer + Offsets::m_fFlags);

	if (flag & (1 << 0))
		return true;
	return false;
}

void CSGO::jump()
{
	Memory::writeProcMemory<int>(hProcess, gameModuleBaseAddr + Offsets::dwForceJump, 6);
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
	int crosshair = Memory::readProcMemory<int>(hProcess, localPlayer + Offsets::m_iCrosshairId);
	return crosshair;
}

void CSGO::triggerBot()
{
	while (true)
	{
		int crosshair = getCrosshair();
		if (triggerBotEnabled && crosshair != 0 && crosshair < 64)
		{
			DWORD entity= Memory::readProcMemory<int>(hProcess, Offsets::dwEntityList + ((crosshair - 1) * 0x10));	

			int eTeam= Memory::readProcMemory<int>(hProcess, entity + Offsets::m_iTeamNum);

			if (eTeam != myTeam)
			{
				shoot();
				Sleep(50);
			}
		}
		Sleep(5);
	}
}

void CSGO::updateLocalPlayer()
{
	while (true)
	{
		localPlayer=Memory::readProcMemory<int>(hProcess, gameModuleBaseAddr + Offsets::dwLocalPlayer);

		Memory::readProcMemory<int>(hProcess, localPlayer + Offsets::m_iTeamNum);
		myTeam = ReadProcessMemory<int>(hProcess, localPlayer + Offsets::m_iTeamNum);		

		Sleep(1000);
	}

	

}

void CSGO::glowEsp()
{
	while (true)
	{
		Sleep(2);
		if (!glowEspEnabled)
			continue;

		DWORD glowObject = Memory::readProcMemory<int>(hProcess, gameModuleBaseAddr + Offsets::dwGlowObjectManager);
		int myTeam = Memory::readProcMemory<int>(hProcess, localPlayer + Offsets::m_iTeamNum);

		for (short int i = 0; i < 64; i++)
		{
			DWORD entity = Memory::readProcMemory<DWORD>(hProcess, gameModuleBaseAddr + Offsets::dwEntityList + i * 0x10);

			if (entity != NULL)
			{		
				int glowIndx = Memory::readProcMemory<int>(hProcess, entity + Offsets::m_iGlowIndex);
				int entityTeam = Memory::readProcMemory<int>(hProcess, entity + Offsets::m_iTeamNum);

				if (myTeam == entityTeam)
				{
					Memory::writeProcMemory<float>(hProcess, glowObject + ((glowIndx * 0x38) + 0x4), 0);
					Memory::writeProcMemory<float>(hProcess, glowObject + ((glowIndx * 0x38) + 0x8), 0);
					Memory::writeProcMemory<float>(hProcess, glowObject + ((glowIndx * 0x38) + 0xC), 2);
					Memory::writeProcMemory<float>(hProcess, glowObject + ((glowIndx * 0x38) + 0x10), 1);
				}
				else
				{
					Memory::writeProcMemory<float>(hProcess, glowObject + ((glowIndx * 0x38) + 0x4), 2);
					Memory::writeProcMemory<float>(hProcess, glowObject + ((glowIndx * 0x38) + 0x8), 0);
					Memory::writeProcMemory<float>(hProcess, glowObject + ((glowIndx * 0x38) + 0xC), 0);
					Memory::writeProcMemory<float>(hProcess, glowObject + ((glowIndx * 0x38) + 0x10), 1);
				}
				Memory::writeProcMemory<bool>(hProcess, glowObject + ((glowIndx * 0x38) + 0x24), true);
				Memory::writeProcMemory<bool>(hProcess, glowObject + ((glowIndx * 0x38) + 0x25), false);
			}
		}	
	}

}

CSGO::CSGO()
{

}

CSGO::~CSGO()
{
}