#include<iostream>
#include<fstream>
#include<vector> 
#include<cstdlib>
#include<ctime> 
#include<string>
#include"hexgame.h"
using namespace std;
int main()
{
	int option,selection,i,j=0,temp,flag = 0,flag2 =0,game1,game2;
	Hex h1,h3,h4(2,8),h5,h6(1);
	std::vector<Hex> games;
	while(option != 5){
		cout << "\nWELCOME TO HEX GAME!\n\n";
		cout << "Please select an option:\n1:Play just a game\n2:Play more than a game at the same time:\n3:Compare marks for two game:\n4:Print all marks in games\n5:Exit\n";
		cin >> option;
		cin.ignore();
		switch (option)
		{
		case 1:
			if(flag2 == 1){
				Hex newgame;
				newgame.playGame();
				h1 = newgame;
				flag2 = 0;
			}		
			while(1){
				if(h1.playGame() == true){
					if(h1.getFlag() != 1){
						cout << "Game is ended" << endl;
						flag2=1;
					}
					else{
						h1.setFlag(0);
					}
					break;
				}
			}
			break;
		case 2:
			if(flag == 0){
				cout << "How many game do you want to play at the same time ?:";
				cin >> selection;
				temp = selection;
				for(i=0;i<selection;i++){
					Hex h2(i+1);
					games.push_back(Hex());
					games[i] = h2;
				}
			}
			else
			{
				cout << "\nContiuning the games..." << endl;
			}
			i = 0;
			while(1){
				if(j == selection){
					flag = 0;
					break;
				}
				if(i == temp){
					i = 0;
				}
				if(games[i].playGame() == true){
					if(games[i].getFlag() == 1){
						games[i].setFlag(0);
						flag = 1;
						break;
					}
					games.erase(games.begin()+i);
					temp--;
					j++;
					i--;	
				}
				i++;
			}
			break;
		case 3:
			for(i=0;i<temp;i++){
				cout << "Game " << games[i].getGamenumber() << endl;
			}
			cout << "Please select which games do you want to compare (for example: 1 2)";
			cin >> game1 >> game2;
			for(i=0;i<temp;i++){
				if(game1 == games[i].getGamenumber()){
					game1 = i;
				}
				if(game2 == games[i].getGamenumber()){
					game2 = i;
				}
			}
			if(games[game1].compare_mark(games[game2]))
				cout <<"Game " << games[game1].getGamenumber() <<" has marks more than Game " << games[game2].getGamenumber() << endl;
			else
				cout <<"Game " << games[game2].getGamenumber() <<" has marks more than Game " << games[game1].getGamenumber() << endl;

			break;
		case 4:
			cout << "Total mark of all games: " << Hex::number_of_marked() << endl;
			break;
		case 5:
			cout << "Quitting..." << endl;
			break;
		default:
			cout << "Incorrect value!" << endl;
			break;
		}
	}
    return 0;
}