#include<iostream>
#include"cell.h"
Cell::Cell()
{
}
Cell::Cell(int newRow,int newColumn,informations newinformation): //it is the constructer for the Cell class
    row(newRow),column(newColumn),information(newinformation)
{
}