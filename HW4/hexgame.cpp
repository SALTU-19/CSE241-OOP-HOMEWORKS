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
	move_counter = 0;
	size = 0;
	visit_counter = 0;
}
Hex::Hex(int _gamemod,int _size)  //constructer which can set gamemod and size
	:gamemod(_gamemod),newsize(_size)
{
	move_counter = 0;
	size = _size;
	visit_counter = 0;
	open_vector();
}
Hex::Hex(int _gamenumber) // constructer which can set name to object 
	:gamenumber(_gamenumber),gamemod(0),newsize(0)
{
	move_counter = 0;
	size = 0;
	visit_counter = 0;
}
Hex::Hex(const Hex &obj) //copy constructer
	:gamenumber(obj.gamenumber),game_flag(obj.game_flag),size(obj.size),newsize(obj.newsize),
    gamemod(obj.gamemod),player(obj.player),comp_x(obj.comp_x),comp_y(obj.comp_y),user1_x(obj.user1_x),user1_y(obj.user1_y),
    user1_control(obj.user1_control),user2_x(obj.user2_x),user2_y(obj.user2_y),user2_control(obj.user2_control),counter_mark(obj.counter_mark),move_counter(obj.move_counter),
    visit_counter(obj.visit_counter),score_x(obj.score_x),score_o(obj.score_o),filename(obj.filename),command(obj.command),gamecount(obj.gamecount)
{
	hexCells = new Cell*[obj.size];
	for(int i=0;i<obj.size;i++){
		hexCells[i] =  new Cell[obj.size];
	}
	for(int i=0;i<obj.size;i++){
		for(int j=0;j<obj.size;j++){
			hexCells[i][j] = obj.hexCells[i][j];
		}
	}
	Movements = new Cell[obj.move_counter];
	for(int i=0;i<obj.move_counter;i++)
		Movements[i] = obj.Movements[i];
	visited = new Cell[obj.visit_counter];
	for(int i=0;i<obj.visit_counter;i++)
		visited[i] = obj.visited[i];

}
Hex::~Hex() //destructer
{
	if(visit_counter != 0){
		delete [] visited;
		visited = nullptr;		
	}
	if(move_counter != 0){
		
		delete [] Movements;
		Movements = nullptr;
	}
	if(size != 0){
		for(int i=0;i<size;i++){
			delete [] hexCells[i];
			hexCells[i] = nullptr;
		}
		delete [] hexCells;
		hexCells = nullptr;
	}	
}
Hex &Hex::operator=(const Hex &rightside) //operator = is overloaded
{
	if(size != rightside.size){
		for(int i=0;i<size;i++){
			delete [] hexCells[i];
			hexCells[i] = nullptr;
		}
		delete [] hexCells;
		hexCells = nullptr;	
		hexCells = new Cell*[rightside.size];
		for(int i=0;i<rightside.size;i++){
			hexCells[i] =  new Cell[rightside.size];
		}
	}
	if(move_counter != rightside.move_counter){
		delete [] Movements;
		Movements = nullptr;
		Movements = new Cell[rightside.move_counter];
	}
	if(visit_counter != rightside.visit_counter){
		delete [] visited;
		visited = nullptr;
		visited = new Cell[rightside.visit_counter];
	}
	gamenumber = rightside.gamenumber;
	game_flag = rightside.game_flag;
    size = rightside.size;
	newsize = rightside.newsize;
    gamemod = rightside.gamemod;
    player = rightside.player;
    comp_x = rightside.comp_x;
    comp_y = rightside.comp_y;
    user1_x = rightside.user1_x;
    user1_y = rightside.user1_y;
    user1_control = rightside.user1_control;
    user2_x = rightside.user2_x;
    user2_y = rightside.user2_y;
    user2_control = rightside.user2_control;
 	counter_mark = rightside.counter_mark;
    move_counter = rightside.move_counter;
    visit_counter = rightside.visit_counter;
    score_x = rightside.score_x;
    score_o = rightside.score_o;                               
	filename = rightside.filename;
	command = rightside.command;
	gamecount = rightside.gamecount;
	for(int i=0;i<rightside.size;i++){
		for(int j=0;j<rightside.size;j++){
			hexCells[i][j] = rightside.hexCells[i][j];
		}
	}
	for(int i=0;i<rightside.move_counter;i++)
		Movements[i] = rightside.Movements[i];
	for(int i=0;i<rightside.visit_counter;i++)
		visited[i] = rightside.visited[i];

	return *this;

}
void Hex::setSize(int _size)
{
	size = _size;
	newsize = _size;
}
bool Hex::operator==(const Hex &game)const //compare mark cell function
{
	return(counter_mark == game.getMark());
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
					if(getMark() ==0)
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
					if(getMark() ==0)
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
		hexCells = new Cell*[size];
		for(i=0;i<size;i++){
			hexCells[i] = new Cell[size];
		}
		fill_vector();

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
Hex::Cell Hex::play(const int &x,const int &y) //the function can set user move
{
        if(player == 1)
        {
			if(counter_mark == 0){
				addVisit(x,y,informations::user1);
			}
            hexCells[x][y].setinformation(informations::user1);
			count++;
			counter_mark++;

			return Cell(x,y,informations::user1);

        }
        else
		{
			if(counter_mark == 1){
				addVisit(x,y,informations::user2);
			}
            hexCells[x][y].setinformation(informations::user2);
			count++;
			counter_mark++;

			return Cell(x,y,informations::user2);
		}
        
}
Hex::Cell Hex::play() //the function can set computer move
{
    int a,b;
	srand(time(0));
	if(comp_x == 0 && comp_y == 0){
		if(size % 2 == 0){
			if(is_free(size-1,(size/2)-1)){
				hexCells[size-1][(size/2)-1].setinformation(informations::user2);
				addVisit(size-1,(size/2)-1,informations::user2);
				count++;
				counter_mark++;
				comp_x = size-1;
				comp_y = (size/2)-1;
				return Cell(size-1,(size/2)-1,informations::user2); 
			}
			else{
				hexCells[size-1][(size/2)].setinformation(informations::user2);
				addVisit(size-1,(size/2),informations::user2);
				count++;
				counter_mark++;
				comp_x = size-1;
				comp_y = (size/2);
				return Cell(size-1,(size/2),informations::user2);
			} 
		}
		else{
			if(is_free(size-1,((size+1)/2)-1)){
				hexCells[size-1][((size+1)/2)-1].setinformation(informations::user2);
				addVisit(size-1,((size+1)/2)-1,informations::user2);
				count++;
				counter_mark++;
				comp_x = size-1;
				comp_y = ((size+1)/2)-1;
				return Cell(size-1,((size+1)/2)-1,informations::user2); 
			}
			else{
				hexCells[size-1][((size+1)/2)].setinformation(informations::user2);
				addVisit(size-1,((size+1)/2),informations::user2);
				count++;
				counter_mark++;
				comp_x = size-1;
				comp_y = ((size+1)/2);
				return Cell(size-1,((size+1)/2),informations::user2);
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
					return Cell(a,b,informations::user2);
				}
			}
		}
		if(!within_boundaries(comp_x-1,comp_y) && is_free(comp_x-1,comp_y)){
			hexCells[comp_x-1][comp_y].setinformation(informations::user2);
			count++;
			counter_mark++;
			return Cell((comp_x--)-1,comp_y,informations::user2);
		}
		else if(!within_boundaries(comp_x-1,comp_y+1) && is_free(comp_x-1,comp_y+1)){
			hexCells[comp_x-1][comp_y+1].setinformation(informations::user2);
			count++;
			counter_mark++;
			return Cell((comp_x--)-1,(comp_y++)+1,informations::user2);
		}
		else if(!within_boundaries(comp_x,comp_y+1) && is_free(comp_x,comp_y+1)){
			hexCells[comp_x][comp_y+1].setinformation(informations::user2);
			count++;
			counter_mark++;
			return Cell(comp_x,(comp_y++)+1,informations::user2);
		}
		else if(!within_boundaries(comp_x,comp_y-1) && is_free(comp_x,comp_y-1)){
			hexCells[comp_x][comp_y-1].setinformation(informations::user2);
			count++;
			counter_mark++;
			return Cell(comp_x,(comp_y--)-1,informations::user2);
		}
		else if(!within_boundaries(comp_x+1,comp_y-1) && is_free(comp_x+1,comp_y-1)){
			hexCells[comp_x+1][comp_y-1].setinformation(informations::user2);
			count++;
			counter_mark++;
			return Cell((comp_x++)+1,(comp_y--)-1,informations::user2);
		}
		else if(!within_boundaries(comp_x+1,comp_y) && is_free(comp_x+1,comp_y)){
			hexCells[comp_x+1][comp_y].setinformation(informations::user2);
			count++;
			counter_mark++;
			return Cell((comp_x++)+1,comp_y,informations::user2);
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
					return Cell(a,b,informations::user2);
				}
			}
		}
	}
}
void Hex::x_control() //x scores was controlled
{

		for(int i =0;i<size;i++)
		{
			for(int j=0;j<size;j++){
				if(hexCells[i][j].getinformations() == informations::user1)
				{
					if(control_score_x(i,j) == false){
						if(((user1_control+1)*12-j*12)>score_x){
							score_x=(user1_control+1)*12-(j)*12;
						}
					}
				}
			}
		}
}
void Hex::y_control() //o scores was controlled
{
		for(int i =0;i<size;i++)
		{
			for(int j=0;j<size;j++){
				if(hexCells[i][j].getinformations() == informations::user2)
				{
					if(control_score_y(i,j) == false){
						if(((user2_control+1)*12-i*12)>score_o)
							score_o=(user2_control+1)*12-i*12;
					}
				}
			}
		}
}
ostream& operator<<(ostream &output,const Hex &game) //the function display the game table
{
    int i,j;
	output << "  ";
	for(i=0;i<game.getSize();i++){
		output << (char)(97+i)<< "  ";
	}
	output << "\n"; 
	for(i=0;i<game.getSize();i++){
		output << i+1 << " ";	
		for(j=0;j<i;j++){
			output << "  ";
		}
		for(j=0;j<game.getSize();j++){

			output << (char)(game.hexCells[i][j].getinformations()) << "  ";
		}
		output << "\n";	
	}
	output << endl;
	if(game.gamemod == 1)
		output << "Player 1 score:" << game.getScorex() << "\tPlayer 2 score:" << game.getScoreo() << endl;
	else
		output << "Player 1 score:" << game.getScorex() << "\tComputer score:" << game.getScoreo() << endl;
	return output;	
}
fstream& operator>>(fstream &input,Hex &game) //the operator overloading for load file
{
	int i=0,j=0,counter = 0,temp,row,column;	
	char x,information;
		input >> temp;
		game.size = temp;
		game.newsize = game.size;
		game.open_vector();
		while(1){
			input >> x;
			if(counter == (game.size)*(game.size) ){
				game.gamemod = (int)(x-48);
				if(game.gamemod == 1){
					input >> x;
					if((int)(x-48) == 1){
						game.player = 1;
					}
					else
						game.player = 2;
				}
				if(game.gamemod == 2){ 
					input >> temp;
					game.comp_x = temp;
					input >> temp;
					game.comp_y = temp;
				}
				input >> temp;
				game.count-=game.counter_mark;
				game.counter_mark = temp;
				game.count += game.counter_mark;
				input >> temp;
				game.move_counter = 0;
				game.Movements = nullptr;
				delete [] game.Movements;
				for(int i=0;i<temp;i++){
					input >> row;
					input >> column;
					input >> information;
					if(information == (char)informations::user1)
						game.addMove(Hex::Cell(row,column,informations::user1));
					else
						game.addMove(Hex::Cell(row,column,informations::user2));
					
					game.move_counter++;
				}
				game.score_x = 0;
				game.score_o = 0;
				game.x_control();
				game.y_control();
				break;
			}
			if(j == game.size){
				i++;
				j=0;
			}
			if(x == (char)informations::user1){
				game.hexCells[i][j].setinformation(informations::user1);
				j++;	
			}
			else if(x == (char)informations::user2){
				game.hexCells[i][j].setinformation(informations::user2);
				j++;	
			}
			else if(x == (char)informations::empty){
				game.hexCells[i][j].setinformation(informations::empty);
				j++;	
			}
			counter++;	 
		}
	return input;		
}
fstream& operator<<(fstream &output,const Hex &game)//the operator overloading for save file
{
		output << game.size << '\n';
		for(int i=0;i<game.size;i++){
			for(int j=0;j<game.size;j++){
				output << (char)game.hexCells[i][j].getinformations();
			}
			output << "\n";	
		}
		output << game.gamemod << '\n';
		if(game.gamemod == 1)
			output << game.player << '\n';
		if(game.gamemod == 2){
			output << game.comp_x << '\n';
			output << game.comp_y << '\n';	
		}
		output << game.counter_mark << endl;
		output << game.move_counter << endl;
		for(int i=0;i<game.move_counter;i++)
			output << game.Movements[i].getrow() << " " << game.Movements[i].getcolumn() << " " <<(char)game.Movements[i].getinformations() << endl;

		return output;
}
bool Hex::game() //the function has some necessary funtion and it returns the game menu when necessary.
{

    int x,y,flag =0,counter = 0;
    while(counter != 2)
   {	
   		cout << *this;
		user_command(x,y);
			if(command == "MAIN MENU"){
				game_flag = 1;
				return true;
			}
			else if(command == "UNDO"){
				if(gamemod == 1){
					(*this)--;
				if(player == 1 && counter_mark != 0)
					player = 2;
				else
					player = 1;	
				}
				else{
					--(*this);
				}
				continue;
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
				if(!within_boundaries(x,y) && is_free(x,y) ){
						addMove(play(x,y));
						move_counter++;
						if(player == 1){
							x_control();
							user1_x = x;
							user1_y = y;
						}
						else{
							y_control();
						}
							
						counter++;   
						if(user_1_win() == true){
							flag = 1;
						}
						if(flag == 1){
							cout << *this;
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
				
							addMove(play());
							move_counter++;
							y_control();
							if(getGamenumber() != 0){
								cout << *this;
							}
							counter++;
							if(user_2_win() == true){
								flag = 1;
							}
							if(flag == 1){
								cout << *this;
								cout << "Computer Won!" << endl;
								gamemod = 0;
								size = 0;
								count-=counter_mark;
								return true;
							}
						}
					}
					else{
						cout << "Wrong Move!" << endl; 
					}
			}		
		if(gamemod == 1){
			cout << *this;
			user_command(x,y);
			if(command == "MAIN MENU"){
				game_flag = 1;
				return true;
			}
			else if(command == "UNDO"){
				(*this)--;
				if(player == 1 && counter_mark != 0)
					player = 2;
				else
					player = 1;	
				continue;
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
				if(!within_boundaries(x,y) && is_free(x,y) ){
					addMove(play(x,y));
					move_counter++;
					y_control();
					counter++;
					if(getGamenumber() != 0){
						cout << *this;
					}
					if(user_2_win() == true){
						flag = 1;
					}
					if(user_1_win() == true){
						flag = 1;
					}
					if(flag == 1){
						cout << *this;
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
	        cout << "\n" << player <<". player, Please give a coordinate (e.g: A1)\n(if the save your game write 'SAVE FILE.txt' )\n(if the load your game write 'LOAD FILE.txt' ):\n(if return the menu write 'MAIN MENU'):\n(if you want undo movement 'UNDO') " << endl;
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
			else if(command != "MAIN MENU" && command != "UNDO")
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
bool Hex::control_score_x(int x,int y) //the function calculates the score x
{

		addVisit(x,y,informations::user1);
		if(is_visited(x,y+1,informations::user1) && !within_boundaries(x,y+1) && (hexCells[x][y+1].getinformations() == informations::user1)){
			if(control_score_x(x,y+1)){
				return true;
			}
		}
		else if(is_visited(x-1,y+1,informations::user1) && !within_boundaries(x-1,y+1) && (hexCells[x-1][y+1].getinformations() == informations::user1)){
			if(control_score_x(x-1,y+1)){
				return true;
			}
		}
		else if(is_visited(x+1,y,informations::user1) && !within_boundaries(x+1,y) && (hexCells[x+1][y].getinformations() == informations::user1)){
			if(control_score_x(x+1,y)){
				return true;
			}
		}
		else if(is_visited(x-1,y,informations::user1) && !within_boundaries(x-1,y) && (hexCells[x-1][y].getinformations() == informations::user1)){
			if(control_score_x(x-1,y)){
				return true;
			}
		}
		else if(is_visited(x,y-1,informations::user1) && !within_boundaries(x,y-1) && (hexCells[x][y-1].getinformations() == informations::user1)){
			if(control_score_x(x,y-1)){
				return true;
			}	
		}
		else if(is_visited(x+1,y-1,informations::user1) && !within_boundaries(x+1,y-1) && (hexCells[x+1][y-1].getinformations() == informations::user1)){
			if(control_score_x(x+1,y-1)){
				return true;
			}
		}
		else{
			user1_control = y;
			delete [] visited;
			visited = nullptr;
			visit_counter = 0;
			return false; 
		}

}
void Hex::addVisit(const int &x,const int &y,const informations &information) //the function add moves visited array
{
	if(visit_counter == 0){
		visited = new Cell;
		visited[0] = Cell(x,y,information);
		visit_counter++;
	}
	else{
		Cell *temp = new Cell[visit_counter+1];
		int i,j;
		for(i=0;i<visit_counter;i++){
			temp[i] = visited[i];
		}
		temp[i] = Cell(x,y,information);
		delete [] visited;
		visited = nullptr;
		visited = temp;
		visit_counter++;
	}
}
bool Hex::is_visited(const int &x,const int &y,const informations &information)const //the function controls the moves is visited
{
	for(int i=0;i<visit_counter;i++){
		if(visited[i].getrow() == x && visited[i].getcolumn() == y && visited[i].getinformations() == information){
			return false;
		}
	}
	return true;
}
bool Hex::control_score_y(int x,int y)//the function calculated score o
{

		addVisit(x,y,informations::user2);
		if(is_visited(x+1,y,informations::user2) && !within_boundaries(x+1,y) && (hexCells[x+1][y].getinformations() == informations::user2)){	
			if(control_score_y(x+1,y)){
				return true;
			}
		}
		else if(is_visited(x+1,y-1,informations::user2) && !within_boundaries(x+1,y-1) && (hexCells[x+1][y-1].getinformations() == informations::user2)){
			if(control_score_y(x+1,y-1)){
				return true;
			}
		}
		else if(is_visited(x,y+1,informations::user2) && !within_boundaries(x,y+1) && (hexCells[x][y+1].getinformations() == informations::user2)){	
			if(control_score_y(x,y+1)){
				return true;
			}
		}
		else if(is_visited(x,y-1,informations::user2) && !within_boundaries(x,y-1) && (hexCells[x][y-1].getinformations() == informations::user2)){	
			if(control_score_y(x,y-1)){
				return true;
			}
		}
		else if(is_visited(x-1,y+1,informations::user2) && !within_boundaries(x-1,y+1) && (hexCells[x-1][y+1].getinformations() == informations::user2)){	
			if(control_score_y(x-1,y+1)){
				return true;
			}
		}
		else if(is_visited(x-1,y,informations::user2) && !within_boundaries(x-1,y) && (hexCells[x-1][y].getinformations() == informations::user2)){
			if(control_score_y(x-1,y)){
				return true;
			}
		}
		else{
			user2_control = x;
			delete [] visited;
			visited = nullptr;
			visit_counter = 0;
			return false;
		}
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
		file << *this;
    	file.close();
    }  
}
void Hex::load_file() //it can load the game
{
	fstream file (filename,ios::in);
	if(!file.is_open()){
		cerr << "File is not open" << endl;
	}
	else{
		file >> *this;
		file.close();
	}
}
void Hex::addMove(Cell c) //the function add movement to movement array
{
	if(move_counter == 0){
		Movements = new Cell;
		Movements[0] = c;
	}
	else{
		Cell *temp = new Cell[move_counter+1];
		int i,j;
		for(i=0;i<move_counter;i++){
			temp[i] = Movements[i];
		}
		temp[i] = c;
		delete [] Movements;
		Movements = nullptr;

		Movements = temp;
	}

}
Hex &Hex::operator--()//the operator overloading for undo
{
	if(move_counter != 0){
		Cell *temp = new Cell[move_counter-2];
		int i,j;
		comp_x = Movements[move_counter-3].getrow();
		comp_y = Movements[move_counter-3].getcolumn();
		hexCells[Movements[move_counter-1].getrow()][Movements[move_counter-1].getcolumn()].setinformation(informations::empty);
		hexCells[Movements[move_counter-2].getrow()][Movements[move_counter-2].getcolumn()].setinformation(informations::empty);
		for(i=0;i<move_counter-2;i++){
			temp[i] = Movements[i];
		}
		delete [] Movements;
		Movements = nullptr;
		Movements = temp;
		move_counter-=2;
		counter_mark-=2;
		count-=2;
		if(move_counter == 0){
			comp_x = 0;
			comp_y = 0;
		}
		score_x=0;
		score_o=0;
		x_control();
		y_control();	
    }
	else{
		cout << "No more undos can be made." << endl;
	}
	return *this;	
}
Hex &Hex::operator--(int ignoreme) //the operator overloading for undo
{
	if(move_counter != 0){

		Cell *temp = new Cell[move_counter-1];
		int i,j;
		hexCells[Movements[move_counter-1].getrow()][Movements[move_counter-1].getcolumn()].setinformation(informations::empty);
		for(i=0;i<move_counter-1;i++){
			temp[i] = Movements[i];
		}
		delete [] Movements;
		Movements = nullptr;
		Movements = temp;
		move_counter--;
		counter_mark--;
		count--;
		score_x=0;
		score_o=0;
		x_control();
		y_control();	
    }
	else{
		comp_x = 0;
		comp_y = 0;
		cout << "No more undos can be made." << endl;
	}
	return *this;	
}
Hex::Cell::Cell()// it is default cell constructer
{
}
Hex::Cell::Cell(int newRow,int newColumn,informations newinformation): //it is the constructer for the Cell class
    row(newRow),column(newColumn),information(newinformation)
{
}
