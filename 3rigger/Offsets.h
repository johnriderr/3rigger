#pragma once
#include <windows.h>

namespace Offsets
{
	DWORD dwLocalPlayer = 0xCBD6B4;
	DWORD dwForceJump = 0x5170DB0;
	DWORD dwForceAttack = 0x30FF2A0;

	uintptr_t m_fFlags = 0x104;
}