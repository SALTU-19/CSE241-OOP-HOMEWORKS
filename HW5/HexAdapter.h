#ifndef HEXADAPTER_H_
#define HEXADAPTER_H_
#include<iostream>
#include"AbstractHex.h"
#include"cell.h"
#include<string>
#include"error.h"
using namespace std;
namespace SaltuHex{
    template<template<typename...> class T>
    class HexAdapter:public AbstractHex
    {
    private:
        T<T<Cell>> hexCells;

    public:
        HexAdapter();
        HexAdapter(int _gamenumber);
        HexAdapter(int _gamemod,int _size);
        void reset();//it reset the board
        Cell& operator()(const int &x,const int &y);// operator()
        void open_vector(); // it opens the board
    };
}
#endif


