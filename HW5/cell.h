#ifndef CELL_H_
#define CELL_H_

enum  class informations{empty = '.',user1 = 'x',user2 = 'o',winx = 'X',wino = 'O',other = '$'};
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
#endif