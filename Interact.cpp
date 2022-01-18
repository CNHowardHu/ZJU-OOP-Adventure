#include <iostream>
#include "Castle.h"

std::string RoomName[6]={
	"Lobby",
	"Princess's Prison",
	"Monster's Lair",
	"Normal Room",
	"Radar Room",
	"Trigger Room"
};

std::string Direction[6]={
	"east",
	"south",
	"west",
	"north",
	"up",
	"down"
};

void Castle::Interact(){
	/*
		This function is used to tell player information and wait for his command.
	*/
	//Print Information of the room that the player starts from.
	PrintRoom();
	for(int Dir,NextPos;!GameOver;){
		std::cout<<"Enter your command:"<<std::endl;
		//Input and decode the command.
		Dir=InputMove();
		if(Dir==-1){
			std::cout<<"Your command is wrong!"<<std::endl;
		}else{
			NextPos=CalcMove(Pos_Player,Dir);
			if(NextPos==-1){
				//If the command is illegal, repeat the input process again.
				Dir=-1;
				std::cout<<"Your command is wrong!"<<std::endl;
			}else{
				//Move the player and output the information of the new position.
				Pos_Player=NextPos;
				PrintRoom();
			}
		}
	}
}

void Castle::PrintRoom(){
	/*
		This function is used to print the information about this room and do some operations according to the room type.
	*/
	std::cout<<"Welcome to the "<<RoomName[RoomType[Pos_Player]]<<". "<<std::endl;
	if(RoomType[Pos_Player]==0&&With_Princess){
		//You have returned to Lobby with Princess.
		std::cout<<"Congratulations, you have successfully taken the princess away from the castle!"<<std::endl;
		GameOver=1;
		return;
	}else if(RoomType[Pos_Player]==1&&!With_Princess){
		//You have found princess.
		std::cout<<"You have found princess, and she is going to leave with you. Please take her to the Lobby."<<std::endl;
		With_Princess=1;
	}else if(RoomType[Pos_Player]==2){
		std::cout<<"Unfortunately, you have been killed by the monster. Game Over!"<<std::endl;
		GameOver=1;
		return;
	}else if(RoomType[Pos_Player]==4){
		//This is a Radar Room, which can tell you the minimum number of steps to Lobby, Princess's Prison or Monster's Lair.
		std::cout<<"Welcome to Radar Room! You will get some data about distance:"<<std::endl;
		std::cout<<"0. There are at least "<<CalcDist(Pos_Player,Pos_Lobby)<<" step(s) for you to reach the Lobby."<<std::endl;
		std::cout<<"1. There are at least "<<CalcDist(Pos_Player,Pos_Princess)<<" step(s) for you to reach the Princess's Prison."<<std::endl;
		std::cout<<"2. There are at least "<<CalcDist(Pos_Player,Pos_Monster)<<" step(s) for you to reach the Monster's Lair."<<std::endl;
	}else if(RoomType[Pos_Player]==5){
		//This is a Trigger Room, which can randomly reset Exits of all rooms.
		std::cout<<"Welcome to Trigger Room! Exits of all rooms have been reset randomly, so you need to look for a new path!"<<std::endl;
		SetExit(Pos_Player);
	}
	//Print the exit information of this room.
	PrintExit();
}

void Castle::PrintExit(){
	/*
		This function is used to print the exit information of the current room.
	*/
	int cnt=0,ExitDir[6];
	for(int i=0;i<6;i++){
		if(CalcMove(Pos_Player,i)!=-1){
			ExitDir[cnt++]=i;
		}
	}
	//Print the information according to the grammar of English.
	if(cnt==1){
		std::cout<<"There is "<<cnt<<" exit: "<<Direction[ExitDir[0]]<<'.';
	}else{
		std::cout<<"There are "<<cnt<<" exits: "<<Direction[ExitDir[0]];
		for(int i=1;i<=cnt-2;i++){
			std::cout<<", "<<Direction[ExitDir[i]];
		}
		std::cout<<" and "<<Direction[ExitDir[cnt-1]]<<'.';
	}
	std::cout<<std::endl;
}

int Castle::InputMove(){
	/*
		This function is used to input a command in a line and decode it.
	*/
	std::string S_in;
	std::getline(std::cin,S_in);
	if(S_in.substr(0,3)=="go "){
		std::string S_Dir=S_in.substr(3);
		for(int i=0;i<6;i++){
			if(S_Dir==Direction[i]){
				return i;
			}
		}
	}
	return -1;
}