#include<iostream>
#include<fstream>
#include <vector> 
#include <cstdlib>
#include <ctime> 
#include<string>
#include"hexgame.h"

int Hex::count = 0;
Hex::Hex()  //constructer has no parameters
	:gamemod(0),newsize(0)
{
}
Hex::Hex(int _gamemod,int _size)  //constructer which can set gamemod and size
	:gamemod(_gamemod),newsize(_size)
{

}
Hex::Hex(int _gamenumber) // constructer which can set name to object 
	:gamenumber(_gamenumber),gamemod(0),newsize(0)
{

}
void Hex::setSize(int _size)
{
	size = _size;
	newsize = _size;
}
void Hex::setGamemod(int _gamemod)
{
	gamemod = _gamemod;
}
bool Hex::compare_mark(Hex game) //compare mark cell function
{
	if(getMark() > game.getMark()){
		
		return true;
	}
	else
		return false;
}
void Hex::setFlag(int newFlag) // it is flag function which is neeeded
{
	game_flag = newFlag;
}
bool Hex::playGame() // it is menu function for any game
{

		if( gamenumber != 0){
			cout << "\n\nGAME " << gamenumber << endl;			
		}
		if(gamecount == 0)
        	cout << "\n1:Human vs human\n2:Human vs computer\n\nPlease select an option:\n";
		if(gamemod == 0)
		{
			cin >> gamemod;
		}
        switch(gamemod)
        {
            case 1:
				if(gamecount == 0)
                	cout << "Please enter the size(min:5):\n";
				gamecount++;
				if(newsize == 0){
                	cin >> newsize;
					cin.ignore();
				}
				if(!setsize(newsize))
				{
					cout << "You enter wrong size!" << endl;
					newsize = 0;
				}
				else{
					open_vector();
					if(game() == true){
						return true;
					}
				}
                break;
            case 2:
				if(gamecount == 0)
                	cout << "Please enter the size(min:5):\n";
				gamecount++;
 				if(newsize == 0){
                	cin >> newsize;
					cin.ignore();
				}
				if(!setsize(newsize))
				{
					cout << "You enter wrong size!" << endl;
					gamecount--;
					newsize = 0;
				}
				else{
					open_vector();
					if(game() == true){
						return true;
					}
				}
                break;
			default:
				cout << "You entered an incorrect value!\n";
				gamemod = 0;
				cin.ignore();
				break;		

        }
	return false;
}
bool Hex::setsize(int newsize) // the function can set size for object
{
    if(newsize < 5)
    {
        return false;
    }
    size = newsize;
    return true;
}
void Hex::open_vector() // the function can open cells
{
    int i,j;
    for (int i = 0; i < size; i++) { 
        hexCells.push_back(vector<Cell>());
        for (int j = 0; j < size; j++) { 
            hexCells[i].push_back(Cell(i,j,informations::empty)); 
        } 
    } 
}
void Hex::fill_vector() // the function can set point any cells
{
    int i,j;
    for (int i = 0; i < size; i++) { 
        for (int j = 0; j < size; j++) { 
            hexCells[i][j].setinformation(informations::empty); 
        } 
    } 	
}
void Hex::play(int x,int y) //the function can set user move
{
        if(player == 1)
        {
            hexCells[x][y].setinformation(informations::user1);
			count++;
			counter_mark++;
        }
        else
		{
            hexCells[x][y].setinformation(informations::user2);
			count++;
			counter_mark++;
		}
        
}
void Hex::play() //the function can set computer move
{
    int a,b;
	srand(time(0));
	if(comp_x == 0 && comp_y == 0){
		if(size % 2 == 0){
			if(is_free(size-1,(size/2)-1)){
				hexCells[size-1][(size/2)-1].setinformation(informations::user2);
				count++;
				counter_mark++;
				comp_x = size-1;
				comp_y = (size/2)-1; 
			}
			else{
				hexCells[size-1][(size/2)].setinformation(informations::user2);
				count++;
				counter_mark++;
				comp_x = size-1;
				comp_y = (size/2);
			} 
		}
		else{
			if(is_free(size-1,((size+1)/2)-1)){
				hexCells[size-1][((size+1)/2)-1].setinformation(informations::user2);
				count++;
				counter_mark++;
				comp_x = size-1;
				comp_y = ((size+1)/2)-1; 
			}
			else{
				hexCells[size-1][((size+1)/2)].setinformation(informations::user2);
				count++;
				counter_mark++;
				comp_x = size-1;
				comp_y = ((size+1)/2);
			}
		}

	}
	else{
		if(comp_x == 0){
			while(1){
				a = rand()%(size-1)+4;
				b = rand()%(size-1);
				if(!within_boundaries(a,b) && is_free(a,b)){
					hexCells[a][b].setinformation(informations::user2);
					count++;
					counter_mark++;
					comp_x = a;
					comp_y = b;
					break;
				}
			}
		}
		if(!within_boundaries(comp_x-1,comp_y) && is_free(comp_x-1,comp_y)){
			hexCells[comp_x-1][comp_y].setinformation(informations::user2);
			count++;
			counter_mark++;
			comp_x--;
		}
		else if(!within_boundaries(comp_x-1,comp_y+1) && is_free(comp_x-1,comp_y+1)){
			hexCells[comp_x-1][comp_y+1].setinformation(informations::user2);
			count++;
			counter_mark++;
			comp_x--;
			comp_y--;
		}
		else if(!within_boundaries(comp_x,comp_y+1) && is_free(comp_x,comp_y+1)){
			hexCells[comp_x][comp_y+1].setinformation(informations::user2);
			count++;
			counter_mark++;
			comp_y++;
		}
		else if(!within_boundaries(comp_x,comp_y-1) && is_free(comp_x,comp_y-1)){
			hexCells[comp_x][comp_y-1].setinformation(informations::user2);
			count++;
			counter_mark++;
			comp_y--;
		}
		else if(!within_boundaries(comp_x+1,comp_y-1) && is_free(comp_x+1,comp_y-1)){
			hexCells[comp_x+1][comp_y-1].setinformation(informations::user2);
			count++;
			counter_mark++;
			comp_x++;
			comp_y--;
		}
		else if(!within_boundaries(comp_x+1,comp_y) && is_free(comp_x+1,comp_y)){
			hexCells[comp_x+1][comp_y].setinformation(informations::user2);
			count++;
			counter_mark++;
			comp_x++;
		}
		else{
			while(1){
				a = rand()%(size-1)+4;
				b = rand()%(size-1);
				if(!within_boundaries(a,b) && is_free(a,b)){
					hexCells[a][b].setinformation(informations::user2);
					count++;
					counter_mark++;
					comp_x = a;
					comp_y = b;
					break;
				}
			}
		}
	}
}
void Hex::display() //the function display the game table
{
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

			cout << (char)(hexCells[i][j].getinformations()) << "  ";
		}
		cout << "\n";
	}	
}
bool Hex::game() //the function has some necessary funtion and it returns the game menu when necessary.
{
    int x,y,flag =0,counter = 0;
    while(counter != 2)
   {	
   		
   		display();
		user_command(x,y);
           if(!within_boundaries(x,y) && is_free(x,y) )
            {
                play(x,y);
                counter++;   
                if(user_1_win() == true){
					flag = 1;
				}
                if(flag == 1){
                    display();
                    cout << "Player 1 won!" << endl;
					gamemod = 0;
					size = 0;
					count-=counter_mark;
                    return true;
                }
                if(gamemod == 1)
                {
					if(player == 1)
                    	player = 2;
					else
						player = 1;
                }
                else
                {
         
                	play();
                	if(getGamenumber() != 0)
                		display();
					counter++;
					if(user_2_win() == true){
						flag = 1;
					}
					if(flag == 1){
						display();
						cout << "Computer Won!" << endl;
						gamemod = 0;
						size = 0;
						count-=counter_mark;
						return true;
					}
                }
            }
            else{
				if(command == "MAIN MENU"){
					game_flag = 1;
					return true;
				}
				else if(command == "LOAD"){
					load_file();					
					cout << "Loading..." << endl;
					continue;
				}
				else if(command == "SAVE"){
					cout << counter_mark << endl;
					save_file();
					cout << "Your game is saved" << endl;
					continue;
				}
				else{
                	cout << "Wrong move!" << endl;
					continue;
				}
			}		
		if(gamemod == 1){
			display();
			user_command(x,y);
            if(!within_boundaries(x,y) && is_free(x,y) )
            {
                play(x,y);
                if(getGamenumber() != 0)
                	display();
                if(user_2_win() == true){
					flag = 1;
				}
				if(user_1_win() == true){
					flag = 1;
				}
                if(flag == 1){
                    display();
                    if(player == 1)
                    	cout << "Player 1 won!" << endl;
                    else
                    	cout << "Player 2 won!" << endl;
					gamemod = 0;
					size = 0;
					count-=counter_mark;
                    return true;
                }
                if(player == 1)
                	player = 2;
                else
                	player = 1;
				counter++;
            }
            else{
				if(command == "MAIN MENU"){
					game_flag = 1;
					return true;
				}
				else if(command == "LOAD"){
					load_file();
					cout << "Loading..." << endl;
					continue;
				}
				else if(command == "SAVE"){
					save_file();
					cout << "Your game is saved" << endl;
					continue;
				}
				else{
                	cout << "Wrong move!" << endl;
					continue;
				}
			}
        }  
   }
   return false; 
}
void Hex::user_command(int &x,int &y) //It is the function where the user command is taken.
{
	        cout << "\n" << player <<". player, Please give a coordinate (e.g: A1)\n(if the save your game write 'SAVE FILE.txt' )\n(if the load your game write 'LOAD FILE.txt' ):\n(if return the menu write 'MAIN MENU') " << endl;
            getline(cin,command);
            if(command.size() == 2)
            {
                y = (int)(command[0])-65;
                x = (command[1] - '0')-1;
            }
            else if(command.size() == 3)
            {
                y = (int)(command[0])-65;
                x = ((command[1] - '0')*10)+ (command[2] - '0')-1;
            }
			else if(command != "MAIN MENU")
			{
				size_t pos = command.find(" ") + 1;
				filename = command.substr(pos);
				command = command.substr(0,4);
			}
			
}
bool Hex::user_1_win() //it controls user1 win or not
{
	for(int i =0;i<size;i++)
    {
        if(hexCells[i][0].getinformations() == informations::user1)
        {
            if(is_finish_x(i,0) == true){
                hexCells[i][0].setinformation(informations::winx);
                return true;   
            }
        }
    }
	return false;
}
bool Hex::user_2_win()//it controls user2 win or not
{
	for(int i =0;i<size;i++)
    {
        if(hexCells[0][i].getinformations() == informations::user2)
        {
            if(is_finish_y(0,i) == true){
                hexCells[0][i].setinformation(informations::wino);
                return true;  
            }
        }
    }
	return false;
}
bool Hex::within_boundaries (const int &x,const int &y)const // it controls game table bouundaries
{

    return (x > size-1 || y > size - 1 || x < 0 || y < 0); 
}
bool Hex::is_free (const int &x,const int &y) // it controls cell is empty or not
{
    return (hexCells[x][y].getinformations() == informations::empty);	
}
bool Hex::is_finish_x(int x,int y) // Examines x from right to left.
{
   	if(y == size-1){
		return true;
	}
		if(!within_boundaries(x,y+1) && (hexCells[x][y+1].getinformations() == informations::user1)){	
			hexCells[x][y+1].setinformation(informations::winx);
			if(is_finish_x(x,y+1)){
				return true;
			}
			else{
				hexCells[x][y+1].setinformation(informations::user1) ;	
			}
		}
		else if(!within_boundaries(x-1,y+1) && (hexCells[x-1][y+1].getinformations() == informations::user1)){
			hexCells[x-1][y+1].setinformation(informations::winx);
			if(is_finish_x(x-1,y+1)){
				return true;
			}
			else{
				hexCells[x-1][y+1].setinformation(informations::user1);	
			}
		}
		else if(!within_boundaries(x+1,y) && (hexCells[x+1][y].getinformations() == informations::user1)){
			hexCells[x+1][y].setinformation(informations::winx);
			if(is_finish_x(x+1,y)){
				return true;
			}
			else{
				hexCells[x+1][y].setinformation(informations::user1);	
			}
		}
		else if(!within_boundaries(x-1,y) && (hexCells[x-1][y].getinformations() == informations::user1)){
			hexCells[x-1][y].setinformation(informations::winx) ;
			if(is_finish_x(x-1,y)){
				return true;
			}
			else{
				hexCells[x-1][y].setinformation(informations::user1) ;	
			}
		}
		else if(!within_boundaries(x,y-1) && (hexCells[x][y-1].getinformations() == informations::user1)){
			hexCells[x][y-1].setinformation(informations::winx) ;
			if(is_finish_x(x,y-1)){
				return true;
			}
			else{
				hexCells[x][y-1].setinformation(informations::user1);	
			}			
		}
		else if(!within_boundaries(x+1,y-1) && (hexCells[x+1][y-1].getinformations() == informations::user1)){
			hexCells[x+1][y-1].setinformation(informations::winx);
			if(is_finish_x(x+1,y-1)){
				return true;
			}
			else{
			    hexCells[x+1][y-1].setinformation(informations::user1) ;	
			}
		}
		return false; 
}
bool Hex::is_finish_y(int x,int y) //Examines the o from bottom to top.
{
   	if(x == size-1){
		return true;
	}
		if(!within_boundaries(x+1,y) && (hexCells[x+1][y].getinformations() == informations::user2)){	
			hexCells[x+1][y].setinformation(informations::wino);
			if(is_finish_y(x+1,y)){
				return true;
			}
			else{
				hexCells[x+1][y].setinformation(informations::user2) ;	
			}
		}
		else if(!within_boundaries(x+1,y-1) && (hexCells[x+1][y-1].getinformations() == informations::user2)){	
			hexCells[x+1][y-1].setinformation(informations::wino);
			if(is_finish_y(x+1,y-1)){
				return true;
			}
			else{
				hexCells[x+1][y-1].setinformation(informations::user2) ;	
			}
		}
		else if(!within_boundaries(x,y+1) && (hexCells[x][y+1].getinformations() == informations::user2)){	
			hexCells[x][y+1].setinformation(informations::wino);
			if(is_finish_y(x,y+1)){
				return true;
			}
			else{
				hexCells[x][y+1].setinformation(informations::user2) ;	
			}
		}
		else if(!within_boundaries(x,y-1) && (hexCells[x][y-1].getinformations() == informations::user2)){	
			hexCells[x][y-1].setinformation(informations::wino);
			if(is_finish_y(x,y-1)){
				return true;
			}
			else{
				hexCells[x][y-1].setinformation(informations::user2) ;	
			}
		}
		else if(!within_boundaries(x-1,y+1) && (hexCells[x-1][y+1].getinformations() == informations::user2)){	
			hexCells[x-1][y+1].setinformation(informations::wino);
			if(is_finish_y(x-1,y+1)){
				return true;
			}
			else{
				hexCells[x-1][y+1].setinformation(informations::user2) ;	
			}
		}
		else if(!within_boundaries(x-1,y) && (hexCells[x-1][y].getinformations() == informations::user2)){	
			hexCells[x-1][y].setinformation(informations::wino);
			if(is_finish_y(x-1,y)){
				return true;
			}
			else{
				hexCells[x-1][y].setinformation(informations::user2) ;	
			}
		}
		return false; 
} 
void Hex::save_file() //it can save the game
{
	fstream file (filename,ios::out);

	if(!file.is_open()){
		cerr << "File is not open" << endl;
	}
	else{
		file << size << '\n';
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				file << (char)hexCells[i][j].getinformations();
			}
			file << "\n";	
		}
		file << gamemod << '\n';
		if(gamemod == 1)
			file << player << '\n';
		if(gamemod == 2){
			file << comp_x << '\n';
			file << comp_y << '\n';	
		}
		cout << counter_mark << endl;
		file << counter_mark;
    	file.close();
    }  
}
void Hex::load_file() //it can load the game
{
	fstream file (filename,ios::in);

	int i=0,j=0,counter = 0,temp;	
	char x;
	if(!file.is_open()){
		cerr << "File is not open" << endl;
	}
	else{
		file >> temp;
		size = 	temp;
		newsize = size;
		open_vector();
		while(1){
			file >> x;
			if(counter == size*size ){
				gamemod = (int)(x-48);
				if(gamemod == 1){
					file >> x;
					if((int)(x-48) == 1){
						player = 1;
					}
					else
						player = 2;
				}
				if(gamemod == 2){ 
					file >> temp;
					comp_x = temp;
					file >> temp;
					comp_y = temp;
				}
				file >> temp;
				count-=counter_mark;
				counter_mark = temp;
				count += counter_mark;
				break;
			}
			if(j == size){
				i++;
				j=0;
			}
			if(x == (char)informations::user1){
				hexCells[i][j].setinformation(informations::user1);
				j++;	
			}
			else if(x == (char)informations::user2){
				hexCells[i][j].setinformation(informations::user2);
				j++;	
			}
			else if(x == (char)informations::empty){
				hexCells[i][j].setinformation(informations::empty);
				j++;	
			}
			counter++;	 
		}
	}		
} 
Hex::Cell::Cell(int newRow,char newColumn,informations newinformation): //it is the constructer for the Cell class
    row(newRow),column(newColumn),information(newinformation)
{
}
void Hex::Cell::setinformation(informations newInformation) //it can set x,o or '.' to cell 
{
    information = newInformation;
}