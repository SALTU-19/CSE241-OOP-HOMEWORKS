#ifndef HEXARRAY1D_H_
#define HEXARRAY1D_H_
#include"cell.h"
#include<iostream>
#include<cstdlib>
#include"AbstractHex.h"
#include"error.h"
using namespace std;
namespace SaltuHex{
    class HexArray1D: public AbstractHex
    {
    private:
        Cell *hexCells;

    public:
        HexArray1D();
        HexArray1D(int _gamenumber);
        HexArray1D(int _gamemod,int _size);
        HexArray1D(const HexArray1D &game);//copy constructer
        ~HexArray1D();//destructer
        HexArray1D& operator=(const HexArray1D &game);//operator = 
        void reset();//it reset the board
        Cell& operator()(const int &x,const int &y);// operator()
        void open_vector(); // it opens the board

    };
}
#endif