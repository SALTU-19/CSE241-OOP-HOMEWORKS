#ifndef HEXVECTOR_H_
#define HEXVECTOR_H_
#include<vector>
#include"cell.h"
#include"error.h"
using namespace std;
namespace SaltuHex{
    class HexVector: public AbstractHex
    {
    private:
        vector<vector<Cell>> hexCells;

    public:
        HexVector();
        HexVector(int _gamenumber);
        HexVector(int _gamemod,int _size);
        void reset();//it reset the board
        Cell& operator()(const int &x,const int &y);// operator()
        void open_vector(); // it opens the board

    };
}
#endif


