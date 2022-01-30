#include"AbstractHex.h"
#include"error.h"
using namespace std;
using namespace SaltuHex;
AbstractHex::AbstractHex()
    :gamemod(0),size(0)
{
    newsize = 0;
}
AbstractHex::AbstractHex(int _gamenumber)
    :gamenumber(_gamenumber),gamemod(0),newsize(0)
{
    newsize = 0;
}
AbstractHex::AbstractHex(int _gamemod,int _size)
    :gamemod(_gamemod),size(_size)
{
    newsize = 0;
}
Cell AbstractHex::lastMove()
{
	if(last_x == -3 ||last_y == -3){
		throw LastMoveException();
	}

	return (*this)(last_x,last_y);
}
bool AbstractHex::operator==(AbstractHex &game)
{
	bool flag=true;
	if(size == game.size){
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if((char)(*this)(i,j).getinformations() != (char)(game)(i,j).getinformations()){
					flag = false;
				}
			}
		}
	}
	else{
		flag = false;
	}
	return flag;

}
bool AbstractHex::playGame() 
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
					if(numberOfMoves() ==0)
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
					if(numberOfMoves() ==0)
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
void AbstractHex::play(const int &x,const int &y) 
{
        if(player == 1)
        {
            (*this)(x,y).setinformation(informations::user1);
			last_x = x;
			last_y = y;
			counter_mark++;
        }
        else
		{
            (*this)(x,y).setinformation(informations::user2);
			last_x = x;
			last_y = y;
			counter_mark++;
		}
        
}
void AbstractHex::play() 
{
    int a,b;
	srand(time(0));
	if(comp_x == 0 && comp_y == 0){
		if(size % 2 == 0){
			if(is_free(size-1,(size/2)-1)){
				(*this)(size-1,(size/2)-1).setinformation(informations::user2);
				counter_mark++;
				comp_x = size-1;
				comp_y = (size/2)-1;
				last_x = comp_x;
				last_y = comp_y; 
			}
			else{
				(*this)(size-1,(size/2)).setinformation(informations::user2);
				counter_mark++;
				comp_x = size-1;
				comp_y = (size/2);
				last_x = comp_x;
				last_y = comp_y;
			} 
		}
		else{
			if(is_free(size-1,((size+1)/2)-1)){
				(*this)(size-1,((size+1)/2)-1).setinformation(informations::user2);
				counter_mark++;
				comp_x = size-1;
				comp_y = ((size+1)/2)-1;
				last_x = comp_x;
				last_y = comp_y; 
			}
			else{
				(*this)(size-1,((size+1)/2)).setinformation(informations::user2);
				counter_mark++;
				comp_x = size-1;
				comp_y = ((size+1)/2);
				last_x = comp_x;
				last_y = comp_y;
			}
		}

	}
	else{
		if(comp_x == 0){
			while(1){
				a = rand()%(size-1)+4;
				b = rand()%(size-1);
				if(!within_boundaries(a,b) && is_free(a,b)){
					(*this)(a,b).setinformation(informations::user2);
					counter_mark++;
					comp_x = a;
					comp_y = b;
					last_x = comp_x;
					last_y = comp_y;
					break;
				}
			}
		}
		if(!within_boundaries(comp_x-1,comp_y) && is_free(comp_x-1,comp_y)){
			(*this)(comp_x-1,comp_y).setinformation(informations::user2);
			counter_mark++;
			comp_x--;
			last_x = comp_x;
			last_y = comp_y;
		}
		else if(!within_boundaries(comp_x-1,comp_y+1) && is_free(comp_x-1,comp_y+1)){
			(*this)(comp_x-1,comp_y+1).setinformation(informations::user2);
			counter_mark++;
			comp_x--;
			comp_y++;
			last_x = comp_x;
			last_y = comp_y;
		}
		else if(!within_boundaries(comp_x,comp_y+1) && is_free(comp_x,comp_y+1)){
			(*this)(comp_x,comp_y+1).setinformation(informations::user2);
			counter_mark++;
			comp_y++;
			last_x = comp_x;
			last_y = comp_y;
		}
		else if(!within_boundaries(comp_x,comp_y-1) && is_free(comp_x,comp_y-1)){
			(*this)(comp_x,comp_y-1).setinformation(informations::user2);
			counter_mark++;
			comp_y--;
			last_x = comp_x;
			last_y = comp_y;
		}
		else if(!within_boundaries(comp_x+1,comp_y-1) && is_free(comp_x+1,comp_y-1)){
			(*this)(comp_x+1,comp_y-1).setinformation(informations::user2);
			counter_mark++;
			comp_x++;
			comp_y--;
			last_x = comp_x;
			last_y = comp_y;
		}
		else if(!within_boundaries(comp_x+1,comp_y) && is_free(comp_x+1,comp_y)){
			(*this)(comp_x+1,comp_y).setinformation(informations::user2);
			counter_mark++;
			comp_x++;
			last_x = comp_x;
			last_y = comp_y;
		}
		else{
			while(1){
				a = rand()%(size-1)+4;
				b = rand()%(size-1);
				if(!within_boundaries(a,b) && is_free(a,b)){
					(*this)(a,b).setinformation(informations::user2);
					counter_mark++;
					comp_x = a;
					comp_y = b;
					last_x = comp_x;
					last_y = comp_y;
					break;
				}
			}
		}
	}
}
void AbstractHex::print()
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

			cout << (char)((*this)(i,j).getinformations()) << "  ";
		}
		cout << "\n";
	}	
}
void AbstractHex::writeToFile()
{
	fstream file (filename,ios::out);

	if(!file.is_open()){
		cerr << "File is not open" << endl;
	}
	else{
		file << size << '\n';
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				file << (char)(*this)(i,j).getinformations();
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
		file << counter_mark << endl;
		file << last_x << endl;
		file << last_y << endl; 
		file.close();
    }  
}
void AbstractHex::readFromFile() 
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
				counter_mark = temp;
				file >> temp;
				last_x = temp;
				file >> temp;
				last_y = temp;
				break;
			}
			if(j == size){
				i++;
				j=0;
			}
			if(x == (char)informations::user1){
				(*this)(i,j).setinformation(informations::user1);
				j++;	
			}
			else if(x == (char)informations::user2){
				(*this)(i,j).setinformation(informations::user2);
				j++;	
			}
			else if(x == (char)informations::empty){
				(*this)(i,j).setinformation(informations::empty);
				j++;	
			}
			else{
				(*this)(i,j).setinformation(informations::other);
				j++;		
			}
			counter++;	 
		}
	}		
}
bool AbstractHex::game() 
{
    int x,y,flag =0,counter = 0;
    while(counter != 2)
   {	
   		
   		print();
		user_command(x,y);
   		if(command == "MAIN MENU"){
   			game_flag = 1;
   			return true;
   		}
        else if(command == "LAST MOVE"){
			try
			{
				cout <<"Your last move:\t" << (char)(last_y+65) << (last_x+1)  << "   it is " << (char)lastMove().getinformations() << endl;
			}
			catch(const LastMoveException &e)
			{
				std::cerr << e.what() << '\n';
			}
        }
		else if(command == "SET SIZE"){
			cout << "Please enter the new size:";
			cin >> change_size;
			cin.ignore();
			try
			{
				this->setSize(change_size);
			}
			catch(const SizeException  & e)
			{
				std::cerr << e.what() << '\n';
			}
							
			
		}
		else if(command == "LOAD"){
			readFromFile();					
			cout << "Loading..." << endl;
			continue;
		}
		else if(command == "SAVE"){
			writeToFile();
			cout << "Your game is saved" << endl;
			continue;
		}
        else if(command == "RESET"){
			try
			{
				reset();
				cout << "Your game is resetted!" << endl;
			}
			catch(const ResetException &e)
			{
				std::cerr << e.what() << '\n';
			}
        }
		else{
           if(!within_boundaries(x,y) && is_free(x,y) )
            {
                play(x,y);
                counter++;   
                if(user_1_win() == true){
					flag = 1;
				}
                if(flag == 1){
                    print();
                    cout << "Player 1 won!" << endl;
					gamemod = 0;
					size = 0;
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
                		print();
					counter++;
					if(user_2_win() == true){
						flag = 1;
					}
					if(flag == 1){
						print();
						cout << "Computer Won!" << endl;
						gamemod = 0;
						size = 0;
						return true;
					}
                }
            }
            else{
                cout << "Wrong move!" << endl;
				continue;
			}
		}		
		if(gamemod == 1){
			print();
			user_command(x,y);
			if(command == "MAIN MENU"){
				game_flag = 1;
				return true;
			}
			else if(command == "LAST MOVE"){
				try
				{
					cout <<"Your last move:\t" << (char)(last_y+65) << (last_x+1)  << "   it is " << (char)lastMove().getinformations() << endl;
				}
				catch(const LastMoveException &e)
				{
					std::cerr << e.what() << '\n';
				}
			}
			else if(command == "SET SIZE"){
				cout << "Please enter the new size:";
				cin >> change_size;
				cin.ignore();
				try
				{
					this->setSize(change_size);
				}
				catch(const SizeException  & e)
				{
					std::cerr << e.what() << '\n';
				}
			}
			else if(command == "LOAD"){
				readFromFile();
				cout << "Loading..." << endl;
				continue;
			}
			else if(command == "SAVE"){
				writeToFile();
				cout << "Your game is saved" << endl;
				continue;
			}
			else if(command == "RESET"){
				try
				{
					reset();
					cout << "Your game is resetted!" << endl;
				}
				catch(const ResetException &e)
				{
					std::cerr << e.what() << '\n';
				}
			}
			else{
				if(!within_boundaries(x,y) && is_free(x,y) )
				{
					play(x,y);
					if(getGamenumber() != 0)
						print();
					if(user_2_win() == true){
						flag = 1;
					}
					if(user_1_win() == true){
						flag = 1;
					}
					if(flag == 1){
						print();
						if(player == 1)
							cout << "Player 1 won!" << endl;
						else
							cout << "Player 2 won!" << endl;
						gamemod = 0;
						size = 0;
						return true;
					}
					if(player == 1)
						player = 2;
					else
						player = 1;
					counter++;
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
void AbstractHex::user_command(int &x,int &y) 
{
	        cout << "\n" << player <<". player, Please give a coordinate (e.g: A1)\n(if the save your game write 'SAVE FILE.txt' )\n(if the load your game write 'LOAD FILE.txt' ):\n(if return the menu write 'MAIN MENU')\n(if reset the game write 'RESET')\n(if last move the game write 'LAST MOVE')\n(if reset size the game write 'SET SIZE') " << endl;
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
			else if(command != "MAIN MENU" && command != "RESET" && command != "LAST MOVE" && command != "SET SIZE")
			{
				size_t pos = command.find(" ") + 1;
				filename = command.substr(pos);
				command = command.substr(0,4);
			}
			
}
bool AbstractHex::user_1_win() 
{
	for(int i =0;i<size;i++)
    {
        if((*this)(i,0).getinformations() == informations::user1)
        {
            if(is_finish_x(i,0) == true){
                (*this)(i,0).setinformation(informations::winx);
                return true;   
            }
        }
    }
	return false;
}
bool AbstractHex::user_2_win()
{
	for(int i =0;i<size;i++)
    {
        if((*this)(0,i).getinformations() == informations::user2)
        {
            if(is_finish_y(0,i) == true){
                (*this)(0,i).setinformation(informations::wino);
                return true;  
            }
        }
    }
	return false;
}
bool AbstractHex::isEnd()
{
	return user_1_win() || user_2_win();
}
bool AbstractHex::within_boundaries (const int &x,const int &y)const 
{

    return (x > size-1 || y > size - 1 || x < 0 || y < 0); 
}
bool AbstractHex::is_free (const int &x,const int &y)
{
    return ((*this)(x,y).getinformations() == informations::empty);	
}
bool AbstractHex::is_finish_x(int x,int y) 
{
   	if(y == size-1){
		return true;
	}
		if(!within_boundaries(x,y+1) && ((*this)(x,y+1).getinformations() == informations::user1)){	
			(*this)(x,y+1).setinformation(informations::winx);
			if(is_finish_x(x,y+1)){
				return true;
			}
			else{
				(*this)(x,y+1).setinformation(informations::user1) ;	
			}
		}
		else if(!within_boundaries(x-1,y+1) && ((*this)(x-1,y+1).getinformations() == informations::user1)){
			(*this)(x-1,y+1).setinformation(informations::winx);
			if(is_finish_x(x-1,y+1)){
				return true;
			}
			else{
				(*this)(x-1,y+1).setinformation(informations::user1);	
			}
		}
		else if(!within_boundaries(x+1,y) && ((*this)(x+1,y).getinformations() == informations::user1)){
			(*this)(x+1,y).setinformation(informations::winx);
			if(is_finish_x(x+1,y)){
				return true;
			}
			else{
				(*this)(x+1,y).setinformation(informations::user1);	
			}
		}
		else if(!within_boundaries(x-1,y) && ((*this)(x-1,y).getinformations() == informations::user1)){
			(*this)(x-1,y).setinformation(informations::winx) ;
			if(is_finish_x(x-1,y)){
				return true;
			}
			else{
				(*this)(x-1,y).setinformation(informations::user1) ;	
			}
		}
		else if(!within_boundaries(x,y-1) && ((*this)(x,y-1).getinformations() == informations::user1)){
			(*this)(x,y-1).setinformation(informations::winx) ;
			if(is_finish_x(x,y-1)){
				return true;
			}
			else{
				(*this)(x,y-1).setinformation(informations::user1);	
			}			
		}
		else if(!within_boundaries(x+1,y-1) && ((*this)(x+1,y-1).getinformations() == informations::user1)){
			(*this)(x+1,y-1).setinformation(informations::winx);
			if(is_finish_x(x+1,y-1)){
				return true;
			}
			else{
			    (*this)(x+1,y-1).setinformation(informations::user1) ;	
			}
		}
		return false; 
}
bool AbstractHex::is_finish_y(int x,int y) 
{
   	if(x == size-1){
		return true;
	}
		if(!within_boundaries(x+1,y) && ((*this)(x+1,y).getinformations() == informations::user2)){	
			(*this)(x+1,y).setinformation(informations::wino);
			if(is_finish_y(x+1,y)){
				return true;
			}
			else{
				(*this)(x+1,y).setinformation(informations::user2) ;	
			}
		}
		else if(!within_boundaries(x+1,y-1) && ((*this)(x+1,y-1).getinformations() == informations::user2)){	
			(*this)(x+1,y-1).setinformation(informations::wino);
			if(is_finish_y(x+1,y-1)){
				return true;
			}
			else{
				(*this)(x+1,y-1).setinformation(informations::user2) ;	
			}
		}
		else if(!within_boundaries(x,y+1) && ((*this)(x,y+1).getinformations() == informations::user2)){	
			(*this)(x,y+1).setinformation(informations::wino);
			if(is_finish_y(x,y+1)){
				return true;
			}
			else{
				(*this)(x,y+1).setinformation(informations::user2) ;	
			}
		}
		else if(!within_boundaries(x,y-1) && ((*this)(x,y-1).getinformations() == informations::user2)){	
			(*this)(x,y-1).setinformation(informations::wino);
			if(is_finish_y(x,y-1)){
				return true;
			}
			else{
				(*this)(x,y-1).setinformation(informations::user2) ;	
			}
		}
		else if(!within_boundaries(x-1,y+1) && ((*this)(x-1,y+1).getinformations() == informations::user2)){	
			(*this)(x-1,y+1).setinformation(informations::wino);
			if(is_finish_y(x-1,y+1)){
				return true;
			}
			else{
				(*this)(x-1,y+1).setinformation(informations::user2) ;	
			}
		}
		else if(!within_boundaries(x-1,y) && ((*this)(x-1,y).getinformations() == informations::user2)){	
			(*this)(x-1,y).setinformation(informations::wino);
			if(is_finish_y(x-1,y)){
				return true;
			}
			else{
				(*this)(x-1,y).setinformation(informations::user2) ;	
			}
		}
		return false; 
}
void AbstractHex::setSize(int _size)
{
	if(_size < 5){
		throw SizeException();
	}
	else{
		size = _size;
		newsize = _size;
		try
		{
			this->reset();
		}
		catch(const ResetException &e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}
bool AbstractHex::setsize(int newsize) 
{
    if(newsize < 5)
    {
        return false;
    }
    size = newsize;
    return true;
}  