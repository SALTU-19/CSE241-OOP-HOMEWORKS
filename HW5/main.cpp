#include<iostream>
#include<vector>
#include<deque> 
#include"AbstractHex.h"
#include"cell.h"
#include"HexArray1D.h"
#include"HexVector.h"
#include"HexAdapter.h"
#include"HexAdapter.cpp"
using namespace std;
using namespace SaltuHex;
bool validGame(vector<AbstractHex*> games,int &index);
int main()
{
	int option,selection,i,j=0,temp,flag = 0,flag2 =0,game1,game2,gamemod,size,index;
	AbstractHex *h1;
	vector<AbstractHex*> games;
	HexVector obj;
	HexArray1D obj2;
	HexAdapter<vector> obj3;
	while(option != 7){
		cout << "\nWELCOME TO HEX GAME!\n\n";
		cout << "Please select an option:\n1:Play just a game(HexVector)\n2:Play just a game(HexArray1D)\n3:Play just a game(AdapterHex)\n4:Play more than a game at the same time:\n5:Compare two games:\n6:Control the games validity\n7:Exit\n";
		cin >> option;
		cin.ignore();

		switch (option)
		{
		case 1:
			h1 = &obj;
			if(flag2 == 1){
				cout << "\n1:Human vs human\n2:Human vs computer\n\nPlease select an option:\n";
				cin >> gamemod;
				h1->setGamemod(gamemod);
				cout << "Please enter the size(min:5):\n";
				cin >> size;
				try
				{
					h1->setSize(size);
				}
				catch(const SizeException  & e)
				{
					std::cerr << e.what() << '\n';
				}
				flag2 = 0;
			}		
			try
			{
				while(1){
					if(h1->playGame() == true){
						if(h1->getFlag() != 1){
							cout << "Game is ended" << endl;
							flag2=1;
						}
						else{
							h1->setFlag(0);
						}
						break;
					}

				}
			}
			catch(const IndexException &e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case 2:
			h1 = &obj2;
			if(flag2 == 1){
				cout << "\n1:Human vs human\n2:Human vs computer\n\nPlease select an option:\n";
				cin >> gamemod;
				h1->setGamemod(gamemod);
				cout << "Please enter the size(min:5):\n";
				cin >> size;
				try
				{
					h1->setSize(size);
				}
				catch(const SizeException  & e)
				{
					std::cerr << e.what() << '\n';
				}
				flag2 = 0;
			}		
			try
			{
				while(1){
					
					if(h1->playGame() == true){
						if(h1->getFlag() != 1){
							cout << "Game is ended" << endl;
							flag2=1;
						}
						else{
							h1->setFlag(0);
						}
						break;
					}

				}
			}
			catch(const IndexException &a)
			{
				std::cerr << a.what() << '\n';
			}
			break;
		case 3:
			h1 = &obj3;
			if(flag2 == 1){
				cout << "\n1:Human vs human\n2:Human vs computer\n\nPlease select an option:\n";
				cin >> gamemod;
				h1->setGamemod(gamemod);
				cout << "Please enter the size(min:5):\n";
				cin >> size;
				try
				{
					h1->setSize(size);
				}
				catch(const SizeException  & e)
				{
					std::cerr << e.what() << '\n';
				}
				flag2 = 0;
			}		
			try
			{
				while(1){
					if(h1->playGame() == true){
						if(h1->getFlag() != 1){
							cout << "Game is ended" << endl;
							flag2=1;
						}
						else{
							h1->setFlag(0);
						}
						break;
					}

				}
			}
			catch(const IndexException &e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case 4:
			if(flag == 0){
				cout << "How many game do you want to play at the same time ?:";
				cin >> selection;
				temp = selection;
				for(i=0;i<selection/2;i++){
					HexArray1D *h2 = new HexArray1D(i+1);
					games.push_back(h2);
				}
				for(i;i<selection;i++){
					HexVector *h3 = new HexVector(i+1);
					games.push_back(h3);
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
				if(games[i]->playGame() == true){
					if(games[i]->getFlag() == 1){
						games[i]->setFlag(0);
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
		case 5:
			if(temp != 0){
				for(i=0;i<temp;i++){
					cout << "Game " << games[i]->getGamenumber() << endl;
				}
				cout << "Please select which games do you want to compare (for example: 1 2)";
				cin >> game1 >> game2;
				for(i=0;i<temp;i++){
					if(game1 == games[i]->getGamenumber()){
						game1 = i;
					}
					if(game2 == games[i]->getGamenumber()){
						game2 = i;
					}
				}
				if(*games[game1] == *games[game2])
					cout <<"Game " << games[game1]->getGamenumber() <<" has same table to Game " << games[game2]->getGamenumber() << endl;
				else
					cout <<"Game " << games[game2]->getGamenumber() <<" doesn't have same table to Game " << games[game1]->getGamenumber() << endl;
			}
			else{
				cout << "There is no game!" << endl;
 			}

			break;

		case 6:
			try
			{
				if(validGame(games,index)){
					cout << "Your games are valid!" << endl;
				}
				else{
					cout << "Game "<< index+1 <<" are not valid!" << endl;	
				}
			}
			catch(const ValidityException& e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		case 7:
			cout << "GG" << endl;
			break;
		
		}
		
}
return 0;
}
bool validGame(vector<AbstractHex*> games,int &index)
{
	if(games.size() == 0){
		throw ValidityException();
	}
	int i,j,k;
	for(i=0;i<games.size();i++){
		if(games[i]->getHeight() != games[i]->getWeight()){
			return false;
		}
	}
	for(i=0;i<games.size();i++){
		for (j=0; j <games[i]->getSize(); j++){
			for(k=0; k<games[i]->getSize(); k++){
				try
				{
					if('x'!=(char)(*games[i])(j,k).getinformations() && 'o'!=(char)(*games[i])(j,k).getinformations() && 'X'!=(char)(*games[i])(j,k).getinformations() && 'O'!=(char)(*games[i])(j,k).getinformations() && '.'!=(char)(*games[i])(j,k).getinformations()){
						index = i;
						return false;
					}
				}
				catch(const IndexException &e)
				{
					std::cerr << e.what() << '\n';
				}
			}
		}
		
	}
	return true;
}





























		/*case 4:
			if(flag == 0){
				cout << "How many game do you want to play at the same time ?:";
				cin >> selection;
				temp = selection;
				for(i=0;i<selection;i++){
					HexArray1D h2(i+1);
					games.push_back(HexArray1D());
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
			if(games[0] == games[1])
				cout << "1 ile 2 esit\n";

		case 5:
			cout << "Quitting..." << endl;
			break;
		default:
			cout << "Incorrect value!" << endl;
			break;
		}*/
