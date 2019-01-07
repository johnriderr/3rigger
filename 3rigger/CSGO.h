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
	bool glowEspEnabled;

	void shoot();
	void triggerBot();
	int getCrosshair();
	void updateLocalPlayer();
	void glowEsp();


private:
	int myTeam;
	void jump();	
	HANDLE hProcess;
	DWORD gameModuleBaseAddr;
	DWORD localPlayer;
};



