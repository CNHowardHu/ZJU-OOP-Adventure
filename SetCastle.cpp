#include <iostream>
#include <cstdlib>
#include "Castle.h"

void Castle::Initialize(){
	/*
		This function is used to initialize the types and exits of all rooms,
		and initialize the state of the player and the game.
	*/
	SetRoomType();
	SetExit(Pos_Lobby);
	With_Princess=0;
	GameOver=0;
	//Player starts the game at the Lobby.
	Pos_Player=Pos_Lobby;
}

void Castle::SetRoomType(){
	/*
		This function is used to set the type of all rooms.
		There are 6 kinds of rooms in the castle.
		0: Lobby *1
		1: Princess's Prison *1
		2: Monster's Lair *1
		3: Normal Room *18
		4: Radar Room *4
		5: Trigger Room *2
	*/
	for(int i=0;i<27;i++){
		RoomType[i]=3;
	}
	Pos_Lobby=NextRandRoom(9);
	RoomType[Pos_Lobby]=0;
	Pos_Princess=NextRandRoom(27);
	RoomType[Pos_Princess]=1;
	Pos_Monster=NextRandRoom(27);
	RoomType[Pos_Monster]=2;
	for(int i=0;i<4;i++){
		RoomType[NextRandRoom(27)]=4;
	}
	for(int i=0;i<2;i++){
		RoomType[NextRandRoom(27)]=5;
	}
}

void Castle::SetExit(int Start_Point){
	/*
		This function is used to set some exits randomly.
	*/
	while(true){
		for(int i=0;i<36;i++){
			Exit[i]=1;
		}
		for(int i=36;i<54;i++){
			Exit[i]=0;
		}
		//There are 12-5=7 exits in each floors.
		for(int x,i=0;i<3;i++){
			for(int j=0;j<5;j++){
				x=NextRandExit(i*12,12,1);
				Exit[x]=0;
			}
		}
		//There are 2 exits between each two floors.
		for(int x,i=0;i<2;i++){
			for(int j=0;j<2;j++){
				x=NextRandExit(36+i*9,9,0);
				Exit[x]=1;
			}
		}
		if(CheckExit(Start_Point)){
			//Repeat the process if there is no path to find Princess while avoiding Monster.
			break;
		}
	}
}

int Castle::NextRandRoom(int Limit){
	/*
		This function is used to return the ID of a Normal Room randomly.
	*/
	int Res=rand()%Limit;
	for(;RoomType[Res]!=3;Res=rand()%Limit){}
	return Res;
}

int Castle::NextRandExit(int L,int Len,bool op){
	/*
		This function is used to return the ID of a location that no exit is in here randomly.
	*/
	int Res=L+rand()%Len;
	for(;Exit[Res]!=op;Res=L+rand()%Len){}
	return Res;
}