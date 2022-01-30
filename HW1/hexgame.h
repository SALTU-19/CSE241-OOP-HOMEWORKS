#ifndef HEXGAME_H_
#define HEXGAME_H_

void humVshum(char arr[12][12],int size);
void humVscom(char arr[12][12],int size);
void fill_array(char arr[12][12],int size);
void print_table(char arr[12][12],int size);
void command_human(char arr[12][12],int size,int player);
void command_comp(char arr[12][12],int size,int *x,int *y,int counter);
int within_boundaries(int x,int y,int size);
int is_free(char arr[12][12],int x,int y,int size);
int is_finish_y(char arr[12][12],int size,int x,int y);
int is_finish_x(char arr[12][12],int size,int x,int y);


#endif