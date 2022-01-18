#include <iostream>
#include <cmath>
#include <queue>
#include "Castle.h"

bool Castle::CheckExit(int Start_Point){
	/*
		This function is used to check if the castle exists a path
		which links the Player to the Princess and the Lobby
		avoid meeting the Monster.
	*/
	bool Vis[27];
	for(int i=0;i<27;i++){
		//Preset Vis of all rooms to 0, which means that the room is not visited.
		Vis[i]=0;
	}
	//Use Breadth-First-Search to check the castle.
	std::queue <int> Q;
	Q.push(Start_Point);
	Vis[Start_Point]=1;
	for(int P,P_Nxt;!Q.empty();){
		P=Q.front();
		Q.pop();
		for(int i=0;i<6;i++){
			//Check neighbors of every directions.
			P_Nxt=CalcMove(P,i);
			if(P_Nxt!=-1&&RoomType[P_Nxt]!=2&&!Vis[P_Nxt]){
				/*
					If there is an exit and the room is safe from Monster and not visited,
					visit this room and put it into the queue.
				*/
				Q.push(P_Nxt);
				Vis[P_Nxt]=1;
			}
		}
	}
	return Vis[Pos_Princess]&&Vis[Pos_Lobby];
}

int Castle::CalcMove(int P,int Dir){
	/*
		This function is used to judge whether the player can make a step
		from the room P on the direction Dir, and return position of next room.
	*/
	/*
		The ID of exit is calculated through a math way.
		But Dir==0 and Dir==2, or Dir==1 and Dir==3 is similar.
	*/
	if(Dir==0){
		if(P%3==2||!Exit[12*(P/9)+P%9+2*(P%9/3)+((P%9!=7)?(P%3):(0))]){
			//If there is not an exit at this direction, then return -1;
			return -1;
		}else{
			return (P+1);
		}
	}else if(Dir==1){
		if(P%9>=6||!Exit[12*(P/9)+P%9+2*(P%9/3)+P%3+((P%3!=2)?(1):(0))]){
			//If there is not an exit at this direction, then return -1;
			return -1;
		}else{
			return (P+3);
		}
	}else if(Dir==2){
		int Q=P-1;
		if(P%3==0||!Exit[12*(Q/9)+Q%9+2*(Q%9/3)+((Q%9!=7)?(Q%3):(0))]){
			//If there is not an exit at this direction, then return -1;
			return -1;
		}else{
			return Q;
		}
	}else if(Dir==3){
		int Q=P-3;
		if(P%9<3||!Exit[12*(Q/9)+Q%9+2*(Q%9/3)+Q%3+((Q%3!=2)?(1):(0))]){
			//If there is not an exit at this direction, then return -1;
			return -1;
		}else{
			return Q;
		}
	}else if(Dir==4){
		if(P>=18||!Exit[36+P]){
			//If there is not an exit at this direction, then return -1;
			return -1;
		}else{
			return (P+9);
		}
	}else if(Dir==5){
		if(P<9||!Exit[36+P-9]){
			//If there is not an exit at this direction, then return -1;
			return -1;
		}else{
			return (P-9);
		}
	}else{
		return -1;
	}
}

int Castle::CalcDist(int Pos_S,int Pos_T){
	/*
		This function is used to calculate the step-distance between two rooms.
	*/
	int Dist[27];
	for(int i=0;i<27;i++){
		//Preset all Dist to -1, which means that this room is not visited.
		Dist[i]=-1;
	}
	std::queue <int> Q;
	Q.push(Pos_S);
	//Set the Dist of source point to 0.
	Dist[Pos_S]=0;
	for(int P,P_Nxt;!Q.empty();){
		P=Q.front();
		Q.pop();
		for(int i=0;i<6;i++){
			P_Nxt=CalcMove(P,i);
			if(P_Nxt!=-1&&Dist[P_Nxt]==-1){
				//If it is not visited, visit it and put it into queue.
				Q.push(P_Nxt);
				Dist[P_Nxt]=Dist[P]+1;
			}
		}
	}
	//Return the step-distance between Pos_S and Pos_T.
	return Dist[Pos_T];
}