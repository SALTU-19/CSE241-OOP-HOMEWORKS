#include"HexAdapter.h"
using namespace SaltuHex;
template<template<typename...> class T>
HexAdapter<T>::HexAdapter()
    :AbstractHex()
{
}
template<template<typename...> class T>
HexAdapter<T>::HexAdapter(int _gamenumber)
    :AbstractHex(_gamenumber)
{
}
template<template<typename...> class T>
HexAdapter<T>::HexAdapter(int _gamemod,int _size)
    :HexAdapter(_gamemod,_size)
{
}
template<template<typename...> class T>
void HexAdapter<T>::open_vector() // the function can open cells
{
    int i,j;
    for (int i = 0; i < size; i++) { 
        hexCells.push_back(T<Cell>());
        for (int j = 0; j < size; j++) { 
            hexCells[i].push_back(Cell(i,j,informations::empty)); 
        } 
    } 
}
template<template<typename...> class T>
void HexAdapter<T>::reset() // the function can set point any cells
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
template<template<typename...> class T>
Cell& HexAdapter<T>::operator()(const int &x,const int &y)
{
	if(within_boundaries(x,y)){
		throw IndexException();
	}
	else{
		return hexCells[x][y];
	}

}
