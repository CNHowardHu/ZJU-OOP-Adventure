#pragma once
class Castle{
private:
	int Pos_Lobby,Pos_Princess,Pos_Monster,Pos_Player,RoomType[27];
	/*
		All data about room-type is stored at an one-dimensional integer array of length 27.
		0~8: Rooms at 0-floor;
		9~17: Rooms at 1-floor;
		18~26: Rooms at 2-floor.
	*/
	bool Exit[54],With_Princess,GameOver;
	/*
		All data about Exits is stored at an one-dimensional bool array of length 54.
		0~11: Exits at 0-floor;
		12~23: Exits at 1-floor;
		24~35: Exits at 2-floor;
		36~44: Exits between 0-floor and 1-floor;
		45~53: Exits between 1-floor and 2-floor.
		Exits of the same floor are sorted in the order of room position,
		and Exits of same room is sorted east firstly and south secondly.
	*/
public:
	//SetCastle.cpp
	void Initialize();
	void SetRoomType();
	void SetExit(int Start_Point);
	int NextRandRoom(int Limit);
	int NextRandExit(int L,int Len,bool op);
	//Interact.cpp
	void Interact();
	void PrintRoom();
	void PrintExit();
	int InputMove();
	//Calculate.cpp
	bool CheckExit(int Start_Point);
	int CalcMove(int P,int Dir);
	int CalcDist(int Pos_S,int Pos_T);
};