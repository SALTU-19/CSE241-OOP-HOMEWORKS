#include"HexArray1D.h"
using namespace SaltuHex;
HexArray1D::HexArray1D()
    :AbstractHex(){}
HexArray1D::HexArray1D(int _gamenumber)
    :AbstractHex(_gamenumber){}
HexArray1D::HexArray1D(int _gamemod,int _size)
    :AbstractHex(_gamemod,_size){}

void HexArray1D::open_vector()
{
    int i,j;
    hexCells = (Cell*)malloc((size*size)*sizeof(Cell));
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            hexCells[size*i+j].setinformation(informations::empty);
        }
    }

}
void HexArray1D::reset() 
{
    if(last_x == -3 && last_y == -3){
        throw ResetException();
    }
    else{
        free(hexCells);
        hexCells = NULL;
        open_vector();
        comp_x = 0;
        comp_y = 0;
        last_x = -3;
        last_y = -3;
    }	
}
Cell& HexArray1D::operator()(const int &x,const int &y)
{
    if(within_boundaries(x,y)){
		throw IndexException();
	}
    else{
  	    return hexCells[size*x+y];      
    }
}
HexArray1D::HexArray1D(const HexArray1D &game)
    :AbstractHex(game)
{
    int i,j;
    hexCells = (Cell*)malloc((size*size)*sizeof(Cell));
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            hexCells[size*i+j] = game.hexCells[size*i+j];
        }
    }
}
HexArray1D::~HexArray1D()
{
    if(last_x != -3 && last_y != -3){
        free(hexCells);
        hexCells = NULL;      
    }
}
HexArray1D& HexArray1D::operator=(const HexArray1D &game)
{
    int i,j;
    if( size != game.size){
        free(hexCells);
        hexCells = NULL;
        hexCells = (Cell*)malloc((game.size*game.size)*sizeof(Cell));
    }
    gamenumber = game.gamenumber;
    gamemod = game.gamemod;
    size = game.size;
    newsize = game.newsize;
	game_flag = game.game_flag;
    player = game.player;
    comp_x = game.comp_x;
    comp_y = game.comp_y;
	counter_mark = game.counter_mark;
	filename = game.filename;
	command = game.command;
	gamecount = game.gamecount;
    last_x = game.last_x;
    last_y = game.last_y;
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            hexCells[size*i+j] = game.hexCells[size*i+j];
        }
    }
    return *this;
}
