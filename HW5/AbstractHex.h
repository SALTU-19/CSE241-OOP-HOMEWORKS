#ifndef ABSTRACTHEX_H_
#define ABSTRACTHEX_H_
#include<iostream>
#include<fstream>
#include"cell.h"
#include<string>
#include<ctime>
#include<cstdlib>
#include<error.h>
using namespace std;
namespace SaltuHex{
    class AbstractHex
    {
    protected:
        int gamenumber = 0;
        int gamemod;
        int size;
        int newsize;
        int game_flag = 0;
        int player = 1;
        int comp_x = 0;
        int comp_y = 0;
        int counter_mark = 0;
        string filename;
        string command;
        int gamecount = 0;
        int last_x = -3;
        int last_y = -3;
        int change_size;
        bool within_boundaries (const int &x,const int &y)const; // it controls game table bouundaries
        bool is_free (const int &x,const int &y);  // it controls cell is empty or not
        bool is_finish_x(int x,int y); // Examines x from right to left.
        bool is_finish_y(int x,int y); //Examines the o from bottom to top.
        bool user_1_win(); //it controls user1 win or not
        bool user_2_win(); //it controls user2 win or not
        bool game(); //the function has some necessary funtion and it returns the game menu when necessary.
        void user_command(int &x,int &y); //It is the function where the user command is taken.
    public:
        AbstractHex();
        AbstractHex(int _gamenumber);
        AbstractHex(int _gamemod,int _size);
        void print(); //the function display the game table
        void readFromFile(); //it can load the game
        void writeToFile(); //it can save the game
        virtual void reset() = 0;
        void setSize(int _size);
        bool setsize(int newsize); // the function can set size for object
        void play(); //the function can set computer move
        void play(const int &x,const int &y); //the function can set user move
        bool isEnd(); // it controls the game is end or not
        virtual Cell& operator()(const int &x,const int &y)  = 0 ;
        bool operator==(AbstractHex &game);//it is == operator overloading
        Cell lastMove(); // the function returns the last move cell
        int getHeight()const{return size;} // it gets height of the table
        int getWeight()const{return size;} // it gets weight of the table
        int getSize()const{return size;} // it gets size of the table
        int numberOfMoves()const{return counter_mark;} // it gets number of cells which non empty
        int getGamenumber()const{return gamenumber;}// it gets gamenumber for example: Game 1
        int getFlag()const{return game_flag;}; // it gets flag when it is neeeded.
        void setFlag(int newFlag){game_flag=newFlag;}//setflag which is needed
        void setGamemod(int _gamemod){gamemod = _gamemod;}//set the gamemod
        bool playGame(); // it is menu function for any game
        virtual void open_vector() = 0;


    };
}
#endif