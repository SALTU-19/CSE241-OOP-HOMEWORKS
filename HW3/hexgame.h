#ifndef HEXGAME_H_
#define HEXGAME_H_

enum  class informations{empty = '.',user1 = 'x',user2 = 'o',winx = 'X',wino = 'O'}; //it is enum class for cell informations

using namespace std;
class Hex
{
private:
	int gamenumber = 0;
	int game_flag = 0;
    int size ;
	int newsize;
    int gamemod;
    int player = 1;
    int comp_x = 0;
    int comp_y = 0;
	int counter_mark = 0;
	static int count; 
	std::string filename;
	std::string command;
	int gamecount = 0;
    class Cell
    {
    private:
        int row;
        char column;
        informations information;
    public:
        Cell(int newRow,char newColumn,informations newinformation);
        void setinformation(informations newinformation);
        int getrow()const{return row;} //it gets row
        char getcolumn()const{return column;}// it gets column 
        informations getinformations() const{return information;} //it gets information the cell (x or o or .)
    };
    std::vector<std::vector<Cell>> hexCells;
    void open_vector();
    bool game();
	void user_command(int &x,int &y);
    void play(int x,int y);
    void play();
    bool within_boundaries (const int &x,const int &y)const;
    bool is_free (const int &x,const int &y);
    bool is_finish_x(int x,int y);
    bool is_finish_y(int x,int y);
	bool user_1_win();
	bool user_2_win();
	void save_file();
	void load_file(); 
public:
    Hex();
	Hex(int _gamemod,int _size);
	Hex(int _gamenumber);
    bool playGame();
    int getHeight()const{return size;} // it gets height of the table
    int getWeight()const{return size;} // it gets weight of the table
	int getSize()const{return size;} // it gets size of the table
	int getMark()const{return counter_mark;}; // it gets number of cells which non empty
	int getGamenumber()const{return gamenumber;}; // it gets gamenumber for example: Game 1
	int getFlag()const{return game_flag;}; // it gets flag when it is neeeded.
	void setFlag(int newFlag);
    void display();
    bool setsize(int newsize);
	bool compare_mark(Hex game);
	void fill_vector();
    void setSize(int _size);
    void setGamemod(int _gamemod);
	static int number_of_marked() {return count;}; // it gets number of the marked all class.
};

#endif