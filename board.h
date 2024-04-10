#ifndef BOARD_H_
#define BOARD_H_
using namespace std;
#include <string>
#include <cmath>
struct object{
	char Character_symbol;
	char X_coordinate;
	char Y_coordinate;
	char alive;
};

class Board{
	private:
		string buffer="";//it's possible to print element by element 
		//yet calling cout many times is not effiecnt
		char board[26][26];
		object Hero={'P',0,0,1};
		object reward[3]={{'.',3,4,1},{'.',7,12,1},{'.',21,9,1}};
		char Empty=' ';
		char nowals=6,nomobs=5,noreward=3;//don't forget to edit those
		object Walls[6]={
			{'+',12,12,1}
			,{'+',12,13,1}
			,{'+',11,12,1}
			,{'+',11,13,1}
			,{'+',11,11,1}
			,{'+',12,11,1}
			};
		object Mobs[5]={
			{'*',24,24,1},
			{'*',0,24,1},
			{'*',24,0,1},
			{'*',24,1,1},
			{'*',23,1,1}
			};
		char IS_player_alive=1,arethererewards=1;

		bool isnearwall(object mob){
			bool yeswall=0;
			if (board[mob.X_coordinate+1][mob.Y_coordinate]==Walls[0].Character_symbol)
				yeswall=1;
			if (board[mob.X_coordinate-1][mob.Y_coordinate]==Walls[0].Character_symbol)
				yeswall=1;
			if (board[mob.X_coordinate][mob.Y_coordinate+1]==Walls[0].Character_symbol)
				yeswall=1;
			if (board[mob.X_coordinate][mob.Y_coordinate-1]==Walls[0].Character_symbol)
				yeswall=1;
			return yeswall;
		}
		void MobMovement(object &mob) {
				if (mob.alive) {
					// Calculate the direction towards the player
					int dx = Hero.X_coordinate - mob.X_coordinate;
					int dy = Hero.Y_coordinate - mob.Y_coordinate;

					// Move the mob one step closer towards the player
					board[mob.X_coordinate][mob.Y_coordinate]=Empty;
					if (abs(dx) > abs(dy)) {
						if (dx > 0) {

							if(board[mob.X_coordinate+1][mob.Y_coordinate]==Empty||board[mob.X_coordinate+1][mob.Y_coordinate]==Hero.Character_symbol){
							board[mob.X_coordinate+1][mob.Y_coordinate]=mob.X_coordinate++;
							}
							else if(isnearwall(mob)){
								mob.Y_coordinate--;
							}
						
						} else if (dx < 0) {
							if(board[mob.X_coordinate-1][mob.Y_coordinate]==Empty||board[mob.X_coordinate-1][mob.Y_coordinate]==Hero.Character_symbol){
							board[mob.X_coordinate-1][mob.Y_coordinate]=mob.X_coordinate--;
							}
							else if(isnearwall(mob)){
								mob.Y_coordinate--;
							}
						}
					} else {
						if (dy > 0) {
							if(board[mob.X_coordinate][mob.Y_coordinate+1]==Empty||board[mob.X_coordinate][mob.Y_coordinate+1]==Hero.Character_symbol){
							board[mob.X_coordinate][mob.Y_coordinate+1]=mob.Y_coordinate++;
							}
							else if(isnearwall(mob)){
								mob.X_coordinate++;
							}
						} else if (dy < 0) {
							if(board[mob.X_coordinate][mob.Y_coordinate-1]==Empty||board[mob.X_coordinate][mob.Y_coordinate-1]==Hero.Character_symbol){
							board[mob.X_coordinate][mob.Y_coordinate-1]=mob.Y_coordinate--;
							}
							else if(isnearwall(mob)){
								mob.X_coordinate--;
							}
							
						}
					}
				}
		}
	void Checkreward(object &reward){
			if (board[reward.X_coordinate][reward.Y_coordinate]!=reward.Character_symbol){
				reward.alive=0;
			}
		}
	public:
	void move_mobs(){
		for (int i=0;i<nomobs;i++){
			if (Mobs[i].alive){
				MobMovement(Mobs[i]);
			}
		}
	}
	Board(){
		for (char i=0;i<25;i++){
			for (char j=0;j<25;j++){
				board[i][j]=Empty;
			}
		}
		for(char i=0;i<25;i++){
			board[25][i]='#';
		}
		for(char i=0;i<26;i++){
			board[i][25]='#';
		}
	}


	int DisplayBoard(){ 
		for (int i=0;i<noreward;i++){
			if (reward[i].alive)
			board[reward[i].X_coordinate][reward[i].Y_coordinate]=reward[i].Character_symbol;	
		}
		board[Hero.X_coordinate][Hero.Y_coordinate]=Hero.Character_symbol;

		for (int i=0;i<nomobs;i++){
			if (Mobs[i].alive){
				board[Mobs[i].X_coordinate][Mobs[i].Y_coordinate]=Mobs[i].Character_symbol;	
			}
		}
		for(int i=0;i<nowals;i++){
			board[Walls[i].X_coordinate][Walls[i].Y_coordinate]=Walls[i].Character_symbol;
		}
		Hero.alive=0;
	    arethererewards=0;//prove by contridiction :D
		for (char i=0;i<26;i++){
			for (char j=0;j<26;j++){
				buffer+=board[i][j];
				buffer+=' ';//space between characters
				switch (board[i][j]){
					case 'P':
						Hero.alive=1;
						break;
					case '.':
						arethererewards=1;
						break;
				}
			}
			buffer+='\n';
		}
		for (int i=0;i<noreward;i++){
			Checkreward(reward[i]);
		}
		if (!Hero.alive)
		{
			cout<<buffer;
			cout<<"YOU LOSE"<<endl;
			return 1;
			}
		if (!arethererewards)
		{
			cout<<buffer;
			cout<<"YOU WIN"<<endl;
			return 1;
			}
		else{
			cout<<buffer;
			//cout<<"x:"<<int(Hero.X_coordinate)<<"y:"<<int(Hero.Y_coordinate)<<'\n';
			buffer="";
			
			return 0;
			}
	}
	void moverRight(){
		board[Hero.X_coordinate][Hero.Y_coordinate]=Empty;
		if (Hero.Y_coordinate<24){
			Hero.Y_coordinate++;
		}
		else{
			Hero.Y_coordinate=0;
		}
	}
	void moveLeft(){
		board[Hero.X_coordinate][Hero.Y_coordinate]=Empty;
		if (Hero.Y_coordinate>0){
			Hero.Y_coordinate--;
		}
		else{
			Hero.Y_coordinate=24;
		}
	}
	void moverUP(){
		board[Hero.X_coordinate][Hero.Y_coordinate]=Empty;
		if (Hero.X_coordinate>0){
			Hero.X_coordinate--;
		}
		else{
			Hero.X_coordinate=24;
		}
	}
	void moveDown(){
		board[Hero.X_coordinate][Hero.Y_coordinate]=Empty;
		if (Hero.X_coordinate<24){
			Hero.X_coordinate++;
		}
		else{
			Hero.X_coordinate=0;
		}
	}

	
};

#endif