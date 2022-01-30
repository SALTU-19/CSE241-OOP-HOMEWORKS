#include<iostream>  
#include<cstring>
#include<cstdlib>
#include <ctime>
#include "hexgame.h"

using namespace std;

int main(){
	int option,size,flag = 0;
	char board[12][12];
	cout << "\nWELCOME TO HEX GAME!\n\n";
	while(size < 12 || size > 6){
		if(flag == 1){
			break;
		}
			while(option != 3){
				cout << "\n1:Human vs human\n2:Human vs computer\n3:Exit\n\nPlease select an option:";
				cin >> option;
				switch(option){
					case 1:
						cout << "Please enter the board size(Min:6,Max:12):";
						cin >> size;
						if(size > 12 || size < 6){
							cout << "You entered an incorrect value!\n";
						}
						else{
							fill_array(board,size);
							humVshum(board,size);
						}
						break;
					case 2:
						cout << "Please enter the board size(Min:6,Max:12):";
						cin >> size;
						if(size > 12 || size < 6){
							cout << "You entered an incorrect value!\n";
						}
						else{
							fill_array(board,size);
							humVscom(board,size);
						}						
						break;
					case 3:
						cout << "Quitting...\n";
						flag = 1;
						break;
					default:
						cout << "You entered an incorrect value!\n";
						break;						
				}
			}			
    }
}