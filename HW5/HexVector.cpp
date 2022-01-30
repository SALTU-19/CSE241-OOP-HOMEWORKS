#include<iostream>
#include<vector>
#include"AbstractHex.h"
#include"cell.h"
#include"HexVector.h"
using namespace SaltuHex;
HexVector::HexVector()
    :AbstractHex(){}
HexVector::HexVector(int _gamenumber)
    :AbstractHex(_gamenumber){}
HexVector::HexVector(int _gamemod,int _size)
    :AbstractHex(_gamemod,_size){}

void HexVector::open_vector() // the function can open cells
{
    int i,j;
    for (int i = 0; i < size; i++) { 
        hexCells.push_back(vector<Cell>());
        for (int j = 0; j < size; j++) { 
            hexCells[i].push_back(Cell(i,j,informations::empty)); 
        } 
    } 
}
void HexVector::reset() // the function can set point any cells
{
    if(last_x == -3 && last_y == -3){
        throw ResetException();
    }
    else{
        hexCells.clear();
        open_vector();
        comp_x = 0;
        comp_y = 0;
        last_x = -3;
        last_y = -3;
    }	
}
Cell& HexVector::operator()(const int &x,const int &y)
{
	if(within_boundaries(x,y)){
		throw IndexException();
	}
	else{
		return hexCells[x][y];
	}
}
