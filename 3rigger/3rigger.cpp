// 3rigger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSGO.h"
#include <iostream>
#include <thread>

using namespace std;

void showCheatStatus(CSGO csgo)
{
	system("cls");
	cout << "bHopEnabled: " << csgo.bHopEnabled << endl;
	cout << "triggerEnabled: " << csgo.triggerBotEnabled << endl;
}

int main()
{
	CSGO csgo;
	csgo.init("csgo.exe");

	bool keyHold = false;

	thread(&CSGO::bHop, &csgo).detach();
	thread(&CSGO::triggerBot, &csgo).detach();
	thread(&CSGO::updateLocalPlayer, &csgo).detach();

	showCheatStatus(csgo);
	while (true)
	{	
		if (GetAsyncKeyState(VK_F1) && !keyHold)
		{
			csgo.bHopEnabled = !csgo.bHopEnabled;			
			keyHold = !keyHold;
			showCheatStatus(csgo);
		}
	
		if (GetAsyncKeyState(VK_F2) && !keyHold)
		{
			csgo.triggerBotEnabled = !csgo.triggerBotEnabled;
			keyHold = !keyHold;
			showCheatStatus(csgo);
		}


		if (!GetAsyncKeyState(VK_F1) && !GetAsyncKeyState(VK_F2))
		{
			keyHold = false;
		}

		Sleep(1);
	}
	return 0;
}

