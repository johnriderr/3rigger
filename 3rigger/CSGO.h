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
	bool triggerBotEnabled;

	void shoot();
	void triggerBot();
	int getCrosshair();
	void updateLocalPlayer();

private:
	int myTeam=6;
	void jump();	
	HANDLE hProcess;
	DWORD gameModuleBaseAddr;
	DWORD localPlayer;
};



