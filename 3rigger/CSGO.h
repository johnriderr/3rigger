#pragma once
#include <Windows.h>

class CSGO
{
public:
	CSGO();
	~CSGO();

	void init(const char* procName);
	bool isPlayerOnTheGround();
	void jump();
private:
	HANDLE _hProcess;
	DWORD _gameModuleBaseAddr;
	DWORD _localPlayer;
};



