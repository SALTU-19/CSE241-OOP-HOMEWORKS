#include<iostream>  
#include<cstring>
#include<cstdlib>
#include <ctime>
#include "hexgame.h"

using namespace std;


void humVshum(char arr[12][12],int size){ // human vs human option
	int i,j,player,flag = 0,counter = 0;
	print_table(arr,size);
	while(1){
		player = 1;
		counter++;
		command_human(arr,size,player);
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
			cout << "Player 1 won!";
			break;
		}
		player = 2;
		command_human(arr,size,player);
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
			cout << "Player 2 won!";
			break;
		}	
	}
	cout << "\n";
	print_table(arr,size);

}
void humVscom(char arr[12][12],int size){ // human vs computer option
	int i,j,player,flag = 0,counter = 0,x,y;
	print_table(arr,size);
	while(1){
		player = 1;
		counter++;
		command_human(arr,size,player);
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
			cout << "Player 1 won!";
			break;
		}
		command_comp(arr,size,&x,&y,counter);
		cout << "\nComputer movement is " << (char)(y+65) << x+1 << "\n";
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
			cout << "Computer Won!\n";
			break;
		}	
	}
	cout << "\n";
	print_table(arr,size);	
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
void command_human(char arr[12][12],int size,int player){ // player movements
	int x,y,length,flag = 0,flag2 = 0;
	char coordinate[3],temp[2];
	while(flag != 1 || flag2 != 1){
		cout << "\n" << player <<". player, Please give a coordinate (e.g: A1):";
		cin >> coordinate;
		length = strlen(coordinate);
		if(length == 2){
			y = (int)coordinate[0] - 65;
			x = (int)coordinate[1] - 49;
		}
		else{
			temp[0] = coordinate[1];
			temp[1] = coordinate[2];
			y = (int)coordinate[0] - 65;
			x = atoi(temp) -1;	
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
void command_comp(char arr[12][12],int size,int *x,int *y,int counter){ // computer movements
	int a,b;
	srand(time(0));
	if(counter == 1){
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

