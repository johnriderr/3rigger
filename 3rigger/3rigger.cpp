// 3rigger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSGO.h"
#include <iostream>
#include <thread>

using namespace std;
int main()
{
	CSGO csgo;
	csgo.init("csgo.exe");

	bool triggerBot = false;
	bool keyHold = false;

	thread bHopThread(&CSGO::bHop, &csgo);
	bHopThread.detach();

	while (true)
	{	
		if (GetAsyncKeyState(VK_F1) && !keyHold)
		{
			csgo.bHopEnabled = !csgo.bHopEnabled;
			cout << "csgo.bHopEnabled: " << csgo.bHopEnabled << endl;
			keyHold = !keyHold;
		}
		if (!GetAsyncKeyState(VK_F1))
		{
			keyHold = false;
		}
		
		Sleep(1);
	}
	return 0;
}

