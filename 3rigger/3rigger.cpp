// 3rigger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSGO.h"
#include <iostream>
using namespace std;
int main()
{
	CSGO csgo;
	csgo.init("csgo.exe");

	while (true)
	{
		if (csgo.isPlayerOnTheGround())
			if (GetAsyncKeyState(VK_SPACE))
				csgo.jump();
		Sleep(0);
	}
	return 0;
}

