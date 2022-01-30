#include<iostream>  
#include<cstring>
#include<cstdlib>
#include <ctime>
#include<fstream>
#include "hexgame.h"
using namespace std;

int comp_x=0,comp_y=0;

int humVshum(char arr[12][12],int size,int player){ // human vs human option
	int i,j,flag = 0,flag2 = 0;
	cout << "\033[2J\033[1;1H";
	print_table(arr,size);
	while(1){
		if(player == 1){

			if(command_human(arr,size,player) == 0){
				flag2= 1;
				break;
			}
			cout << "\033[2J\033[1;1H";
			print_table(arr,size);
							for(i=0;i<size;i++){
								if(arr[i][0] == 'x'){
									if(is_finish_x(arr,size,i,0)){
										arr[i][0] = 'X';
										flag = 1;
										break;
									}
								} 
							}
							player = 2;
				if(flag == 1){
					cout << endl;
					print_table(arr,size);
					cout << "Player 1 won!" << endl;
					flag2 = 1;
					break;
				}
		}
		if(player == 2){
			if(command_human(arr,size,player) == 0){
				flag2 = 1;
				break;
			}
			cout << "\033[2J\033[1;1H";
			print_table(arr,size);
						for(i=0;i<size;i++){
							if(arr[0][i] == 'o'){
								if(is_finish_y(arr,size,0,i)){
									arr[0][i] = 'O';
									flag = 1;
									break;
								}
							} 
						}
						player = 1;
			if(flag == 1){
				cout << endl;
				print_table(arr,size);
				cout << "Player 2 won!" << endl;
				flag2 = 1;
				break;
			}
		}	
	}
	if(flag2 == 1){
		return 0;
	}
	cout << "\n";
}
int humVscom(char arr[12][12],int size,int x,int y){ // human vs computer option
	int i,j,player=1,flag = 0,flag2=0;
	Cells option = Cells::humVscom;
	print_table(arr,size);
	while(1){
		if(command_human(arr,size,player,option) == 0){
			flag2=1;
			break;
		}
		cout << "\033[2J\033[1;1H";
		print_table(arr,size);
					for(i=0;i<size;i++){
						if(arr[i][0] == 'x'){
							if(is_finish_x(arr,size,i,0)){
								arr[i][0] = 'X';
								flag = 1;
								break;
							}
						} 
					}
		if(flag == 1){
			cout << endl;
			print_table(arr,size);
			cout << "Player 1 won!";
			flag2 = 1;
			break;
		}
		command_comp(arr,size,&x,&y);
		comp_x = x;
		comp_y = y;
		cout << "\nComputer movement is " << (char)(y+65) << x+1 << "\n";
		cout << "\033[2J\033[1;1H";
		print_table(arr,size);
					for(i=0;i<size;i++){
						if(arr[0][i] == 'o'){
							if(is_finish_y(arr,size,0,i)){
								arr[0][i] = 'O';
								flag = 1;
								break;
							}
						} 
					}
		if(flag == 1){
			cout << endl;
			print_table(arr,size);
			cout << "Computer Won!\n";
			flag2 = 1;
			break;

		}	
	}
	if(flag2 == 1){

		return 0;
	}
	cout << "\n";
}
void fill_array(char arr[12][12],int size){ // We have filled the array with points.
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			arr[i][j] = '.';
		}
	}
}
void print_table(char arr[12][12],int size){ // printed table
	int i,j;

	cout << "  ";
	for(i=0;i<size;i++){
		cout << (char)(97+i)<< "  ";
	}
	cout << "\n"; 
	for(i=0;i<size;i++){
		cout << i+1 << " ";	

		for(j=0;j<i;j++){
			cout << "  ";
		}

		for(j=0;j<size;j++){

			cout << arr[i][j] << "  ";
		}
		cout << "\n";
	}	
}
int command_human(char arr[12][12],int &size,int &player,Cells option){ // player movements
	int x,y,length,length2,com_x,com_y;
	auto flag = 0,flag2 = 0;
	decltype(flag) selection;
	char coordinate[20],temp[2],coordinate2[20];
	Cells _player;
	while(flag != 1 || flag2 != 1){
		cout << "\n" << player <<". player, Please give a coordinate (e.g: A 1)\n(if the save your game write 'SAVE FILE.txt' )\n(if the load your game write 'LOAD FILE.txt' ):";
		cin >> coordinate;
		cin >> coordinate2;
		length = strlen(coordinate);
		length2 = strlen(coordinate2);
		if(length == 1 && length2 == 1){
			y = (int)coordinate[0] - 65;
			x = (int)coordinate2[0] - 49;
		}
		else if(length == 1 && length2 == 2){
			temp[0] = coordinate2[0];
			temp[1] = coordinate2[1];
			y = (int)coordinate[0] - 65;
			x = atoi(temp) -1;	
		}
		else {
			if(strcmp(coordinate,"SAVE") == 0){
				if(player == 1){
					_player = Cells::player_1;
				}
				else{
					_player = Cells::player_2;
				}
				save_file(arr,size,coordinate2,option,_player);
				cout << "Your game is saved!" << endl;
				continue;		
			}
			else if(strcmp(coordinate,"LOAD") == 0){				
				if(load_file(arr,size,coordinate2,selection,player,com_x,com_y) == 0){
					continue;
				}
				if(selection == (int)Cells::humVscom){

					if(humVscom(arr,size,com_x,com_y) == 0){
						return 0;
					}
				}
				else
					if(humVshum(arr,size,player) == 0){
						return 0;
					}

				continue;
			}
			else{
				cout << "You entered an incorrected option!\n" << endl;
				continue;
			}

	
		}

		if(within_boundaries(x,y,size)){
			cout << "The coordinate you entered is out of the table boundaries!";
		}
		else
			flag = 1;
		if(is_free(arr,x,y,size)){
			if(player == 1){
				arr[x][y] = 'x';
			}
			else{
				arr[x][y] = 'o';
			}
			flag2 = 1;
		}
		else
			cout << "\nThat coordinate has already been used!\n";			
	}
}
void command_comp(char arr[12][12],int size,int *x,int *y){ // computer movements
	int a,b;
	cout << *x << endl;
	cout << *y << endl;
	srand(time(0));
	if(*x == 0 && *y == 0){
		if(size % 2 == 0){
			if(is_free(arr,size-1,(size/2)-1,size)){
				arr[size-1][(size/2)-1] = 'o';
				*x = size-1;
				*y = (size/2)-1; 
			}
			else{
				arr[size-1][(size/2)] = 'o';
				*x = size-1;
				*y = (size/2);
			} 
		}
		else{
			if(is_free(arr,size-1,((size+1)/2)-1,size)){
				arr[size-1][((size+1)/2)-1] = 'o';
				*x = size-1;
				*y = ((size+1)/2)-1; 
			}
			else{
				arr[size-1][((size+1)/2)] = 'o';
				*x = size-1;
				*y = ((size+1)/2);
			}
		}

	}
	else{
		if(*x == 0){
			while(1){
				a = rand()%(size-1)+4;
				b = rand()%(size-1);
				if(is_free(arr,a,b,size) && !within_boundaries(a,b,size)){
					arr[a][b] = 'o';
					*x = a;
					*y = b;
					break;
				}
			}
		}
		if(is_free(arr,*x-1,*y,size) && !within_boundaries(*x-1,*y,size)){
			arr[*x-1][*y] = 'o';
			*x = *x-1;
		}
		else if(is_free(arr,*x-1,*y+1,size) && !within_boundaries(*x-1,*y+1,size)){
			arr[*x-1][*y+1] = 'o';
			*x = *x-1;
			*y = *y+1;
		}
		else if(is_free(arr,*x,*y+1,size) && !within_boundaries(*x,*y+1,size)){
			arr[*x][*y+1] = 'o';
			*y = *y+1;
		}
		else if(is_free(arr,*x,*y-1,size) && !within_boundaries(*x,*y-1,size)){
			arr[*x][*y-1] = 'o';
			*y = *y-1;
		}
		else if(is_free(arr,*x+1,*y-1,size) && !within_boundaries(*x+1,*y-1,size)){
			arr[*x+1][*y-1] = 'o';
			*x = *x+1;
			*y = *y-1;
		}
		else if(is_free(arr,*x+1,*y,size) && !within_boundaries(*x+1,*y,size)){
			arr[*x+1][*y] = 'o';
			*x = *x+1;
		}
		else{
			while(1){
				a = rand()%(size-1)+4;
				b = rand()%(size-1);
				if(is_free(arr,a,b,size) && !within_boundaries(a,b,size)){
					arr[a][b] = 'o';
					*x = a;
					*y = b;
					break;
				}
			}
		}
	}
}
int within_boundaries(int x,int y,int size){ // table boundaries control
	if(x > size-1 || y > size - 1){
		return 1;
	}
	return 0;
}
int is_free(char arr[12][12],int x,int y,int size){ //check whether the place is occupied
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(x == i && y == j){
				if(arr[i][j] == '.'){
					return 1;
				}
				else if(arr[i][j] == 'x' || arr[i][j] == 'o' || arr[i][j] == 'X' || arr[i][j] == 'O'){
					return 0;
				}
			}
		}
	}	
}
int is_finish_x(char arr[12][12],int size,int x,int y){ // Checking whether the x's are finished
	if(y == size-1){
		return 1;
	}
		if(arr[x][y+1] == 'x'){	
			arr[x][y+1] = 'X';
			if(is_finish_x(arr,size,x,y+1)){
				return 1;
			}
			else{
				arr[x][y+1] = 'x';	
			}
		}
		else if(arr[x-1][y+1] == 'x'){
			arr[x-1][y+1] = 'X';
			if(is_finish_x(arr,size,x-1,y+1)){
				return 1;
			}
			else{
				arr[x-1][y+1] = 'x';	
			}
		}
		else if(arr[x+1][y] == 'x'){
			arr[x+1][y] = 'X';
			if(is_finish_x(arr,size,x+1,y)){
				return 1;
			}
			else{
				arr[x+1][y] = 'x';	
			}
		}
		else if(arr[x-1][y] == 'x'){
			arr[x-1][y] = 'X';
			if(is_finish_x(arr,size,x-1,y)){
				return 1;
			}
			else{
				arr[x-1][y] = 'x';	
			}
		}
		else if(arr[x][y-1] == 'x'){
			arr[x][y-1] = 'X';
			if(is_finish_x(arr,size,x,y-1)){
				return 1;
			}
			else{
				arr[x][y-1] = 'x';	
			}			
		}
		else if(arr[x+1][y-1] == 'x'){
			arr[x+1][y-1] = 'X';
			if(is_finish_x(arr,size,x+1,y-1)){
				return 1;
			}
			else{
				arr[x+1][y-1] = 'x';	
			}
		}
		return 0;
}
int is_finish_y(char arr[12][12],int size,int x,int y){ // Checking whether the o's are finished.
	if(x == size-1){
		return 1;
	}
		if(arr[x+1][y] == 'o'){
			arr[x+1][y] = 'O';
			if(is_finish_y(arr,size,x+1,y)){
				return 1;
			}
			else{
				arr[x+1][y] = 'o';
			}
		}
		else if(arr[x+1][y-1] == 'o'){
			arr[x+1][y-1] = 'O';
			if(is_finish_y(arr,size,x+1,y-1)){
				return 1;
			}
			else{
				arr[x+1][y-1] = 'o';
			}
		}
		else if(arr[x][y+1] == 'o'){
			arr[x][y+1] = 'O';
			if(is_finish_y(arr,size,x,y+1)){
				return 1;
			}
			else{
				arr[x][y+1] = 'o';
			}
		}
		else if(arr[x][y-1] == 'o'){
			arr[x][y-1] = 'O';
			if(is_finish_y(arr,size,x,y-1)){
				return 1;
			}
			else{
				arr[x][y-1] = 'o';
			}
		}
		else if(arr[x-1][y+1] == 'o'){
			arr[x-1][y+1] = 'O';
			if(is_finish_y(arr,size,x-1,y+1)){
				return 1;
			}
			else{
				arr[x-1][y+1] = 'o';
			}
		}
		else if(arr[x-1][y] == 'o'){
			arr[x-1][y] = 'O';
			if(is_finish_y(arr,size,x-1,y)){
				return 1;
			}
			else{
				arr[x-1][y] = 'o';
			}
		}		
		return 0;		
}
void save_file(char arr[12][12],const int &size,const char *filename,Cells option,Cells player){ // saved the datas in files 

	fstream file (filename,ios::out);

	if(!file.is_open()){
		cerr << "File is not open" << endl;
	}
	else{
		file << size << '\n';
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if(arr[i][j] == 'x'){
					file << (int)Cells::x;	
				}
				else if(arr[i][j] == 'o'){
					file << (int)Cells::o;	
				}
				else if(arr[i][j] == 'X'){
					file << (int)Cells::X;	
				}
				else if(arr[i][j] == 'O'){
					file << (int)Cells::O;	
				}
				else if(arr[i][j] == '.'){
					file << (int)Cells::point;
				}	
			}
			file << "\n";	
		}
		file << (int)option << '\n';
		file << (int)player << '\n';
		if(option == Cells::humVscom){
			file << (int)comp_x << '\n';
			file << (int)comp_y << '\n';	
		}

    	file.close();
    }  
}
int load_file(char arr[12][12],int &size,const char *filename,int &option,int &player,int &comp_x,int &comp_y){ //loaded the datas in files 

	fstream file (filename,ios::in);

	int i=0,j=0;	
	char x;
	if(!file.is_open()){
		cerr << "File is not open" << endl;
		return 0;
	}
	else{
		file >> x;
		size = 	(int)(x-48);
		while(1){
			file >> x;
			if((int)(x-48) > (int)Cells::point){
				option = (int)(x-48);
				file >> x;
				 if((int)(x-48) == (int)Cells::player_1){
				 	player = 1;
				 }
				 else
				 	player = 2;
				if(option == 6){ 
					file >> x;
					comp_x = (int)(x-48);
					file >> x;
					comp_y = (int)(x-48);
				}
				break;
			}
			if(j == size){
				i++;
				j=0;
			}
			if((int)(x-48) == (int)Cells::x){
				arr[i][j] = 'x';
				j++;	
			}
			else if((int)(x-48) == (int)Cells::o){
				arr[i][j] = 'o';
				j++;	
			}
			else if((int)(x-48) == (int)Cells::X){
				arr[i][j] = 'X';
				j++;	
			}
			else if((int)(x-48) == (int)Cells::O){
				arr[i][j] = 'O';
				j++;	
			}
			else if((int)(x-48)== (int)Cells::point){
				arr[i][j] = '.';
				j++;	
			}
			 
		}
	}
}


