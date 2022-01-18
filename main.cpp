#include <iostream>
#include <ctime>
#include "Castle.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {
	srand((unsigned)time(NULL));
	Castle NewGame;
	NewGame.Initialize();
	NewGame.Interact();
	system("pause");
	return 0;
}

/*
	There are 6 kinds of rooms in the castle:
	0: Lobby *1
	1: Princess's Prison *1
	2: Monster's Lair *1
	3: Normal Room *18
	4: Radar Room *4
	5: Trigger Room *2
	Radar Room can tell you the minimum number of steps to Lobby, Princess's Prison or Monster's Lair.
	Trigger Room can randomly reset Exits of all rooms.
	The total number of rooms is 3*3*3=27, and the room with monster or princess is randomly set.
	It's guaranteed that there exist at least one path to find Princess while avoiding Monster at any time, even if the Trigger Room has been activated.
*/