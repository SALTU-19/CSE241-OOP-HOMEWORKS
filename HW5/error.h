#ifndef ERROR_H_
#define ERROR_H_
#include<exception>
#include<stdexcept>
using namespace std;
class LastMoveException:public runtime_error
{
public:
    LastMoveException():runtime_error("There is no last move"){}
};
class IndexException:public runtime_error
{
public:
    IndexException():runtime_error("Wrong move!"){}
};
class ResetException:public runtime_error
{
public:
    ResetException():runtime_error("There is no move!"){}
};
class ValidityException:public runtime_error
{
public:
    ValidityException():runtime_error("There is no game!"){}
};
class SizeException:public runtime_error
{
public:
    SizeException():runtime_error("Invalid size!"){}
};




 
#endif