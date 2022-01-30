#ifndef HEXGAME_H_
#define HEXGAME_H_

enum  class informations{empty = '.',user1 = 'x',user2 = 'o',winx = 'X',wino = 'O'}; //it is enum class for cell informations

using namespace std;
class Hex
{
public:
    class Cell
    {
    private:
        int row;
        int column;
        informations information;
    public:
        Cell();
        Cell(int newRow,int newColumn,informations newinformation);
        void setinformation(informations newinformation){information = newinformation;};
        int getrow()const{return row;} //it gets row
        int getcolumn()const{return column;}// it gets column 
        informations getinformations() const{return information;} //it gets information the cell (x or o or .)
    };
    explicit Hex();
	explicit Hex(int _gamemod,int _size);
	explicit Hex(int _gamenumber);
    Hex &operator=(const Hex &rightside);
    Hex(const Hex &obj);
    ~Hex();
    bool playGame();
    int getHeight()const{return size;}; // it gets height of the table
    int getWeight()const{return size;}; // it gets weight of the table
    int getScorex()const{return score_x;}; //it gets score of the x
    int getScoreo()const{return score_o;}; // it gets score of the o
	int getSize()const{return size;} // it gets size of the table
	int getMark()const{return counter_mark;}; // it gets number of cells which non empty
	int getGamenumber()const{return gamenumber;}; // it gets gamenumber for example: Game 1
	int getFlag()const{return game_flag;}; // it gets flag when it is neeeded.
	void setFlag(int newFlag){game_flag = newFlag;};
    friend ostream& operator<<(ostream &output,const Hex &game);
    friend fstream& operator>>(fstream &input,Hex &game);
    friend fstream& operator<<(fstream &output,const Hex &game);
    Hex &operator--(int ignoreme); //postfix version
    Hex &operator--();  //preefix version
    bool setsize(int newsize);
	bool operator==(const Hex &game)const;
	void fill_vector();
    void setSize(int _size);
    void setGamemod(int _gamemod){gamemod = _gamemod;};
	static int number_of_marked() {return count;}; // it gets number of the marked all class.
private:
	int gamenumber = 0;
	int game_flag = 0;
    int size ;
	int newsize;
    int gamemod;
    int player = 1;
    int comp_x = 0;
    int comp_y = 0;
    int user1_x = -5;
    int user1_y = -5;
    int user1_control = 0;
    int user2_x = -5;
    int user2_y = -5;
    int user2_control = 0;
 	int counter_mark = 0;
    int move_counter = 0;
    int visit_counter = 0;
    int score_x = 0;
    int score_o = 0;                                //== DÜZELT VE CONSTLARA DİKKAT ET ONLARI DÜZENLE UNUTMA
	static int count; 
	std::string filename;
	std::string command;
	int gamecount = 0;
    Cell ** hexCells;
    Cell *Movements;
    Cell *visited;
    void addVisit(const int &x,const int &y,const informations &information);
    void open_vector();
    void addMove(Cell c);
    bool is_visited(const int &x,const int &y,const informations &information)const;
    bool game();
	void user_command(int &x,int &y);
    Cell play(const int &x,const int &y);
    Cell play();
    bool within_boundaries (const int &x,const int &y)const;
    bool is_free (const int &x,const int &y);
    bool is_finish_x(int x,int y);
    bool is_finish_y(int x,int y);
    bool control_score_x(int x,int y);
    void x_control(); 
    bool control_score_y(int x,int y);
    void y_control();
	bool user_1_win();
	bool user_2_win();
	void save_file();
	void load_file(); 
};

#endif