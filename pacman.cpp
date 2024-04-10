#include <iostream>
#include "board.h"
#include <conio.h> // For _getch()
#include <windows.h> //for game speed "sleep function"
using namespace std;

int main() {
	while(1){
	char pressed_key;
	Board obj;
	string waitbeforexit;
	system ("CLS");
	obj.DisplayBoard();
	char isplaying=1;
	while (isplaying){
		if (_kbhit()){
		pressed_key=_getch();
		switch (pressed_key)
		{
		case 'w':
			obj.moverUP();
			break;
		case 'a':
			obj.moveLeft();
			break;
		case 's':
			obj.moveDown();
			break;
		case 'd':
			obj.moverRight();
			break;		
		default:
			break;
		}}
		else{
			//system("cls");
			obj.move_mobs();
			if(obj.DisplayBoard()){
			isplaying=0;
			}	
			Sleep(90);
		}
		

	}
	cout<<"game over";
	cin>>waitbeforexit;
	}
}
