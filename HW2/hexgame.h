#ifndef HEXGAME_H_
#define HEXGAME_H_

enum class Cells{x,o,X,O,point,humVshum,humVscom,player_1,player_2};
int humVshum(char arr[12][12],int size,int player = 1);
int humVscom(char arr[12][12],int size,int x=0,int y=0);
void fill_array(char arr[12][12],int size);
void print_table(char arr[12][12],int size);
int command_human(char arr[12][12],int &size,int &player,Cells option = Cells::humVshum);
void command_comp(char arr[12][12],int size,int *x,int *y);
int within_boundaries(int x,int y,int size);
int is_free(char arr[12][12],int x,int y,int size);
int is_finish_y(char arr[12][12],int size,int x,int y);
int is_finish_x(char arr[12][12],int size,int x,int y);
void save_file(char arr[12][12],const int &size,const char *filename,Cells option,Cells player);
int load_file(char arr[12][12],int &size,const char *filename,int &option,int &player,int &comp_x,int &comp_y);
int control(int option);


#endif