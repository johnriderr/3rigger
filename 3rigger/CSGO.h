#pragma once
#include <Windows.h>

class CSGO
{
public:
	CSGO();
	~CSGO();

	void init(const char* procName);
	bool playerOnTheGround();	
	void bHop();
	bool bHopEnabled;
private:
	void shoot();
	void jump();	
	HANDLE hProcess;
	DWORD gameModuleBaseAddr;
	DWORD localPlayer;
};



