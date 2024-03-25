#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define CUP_Y 10
#define CUP_X 10 
#define DELAY 1


char const empty = '.'; 
int mean_x = (CUP_X / 2) - 2;
int y = 0;
    
void print_figure (int fig[][4], int y, int x)
{
 for (int i = 0; i < 4; i++)
 {
  for (int j = 0; j < 4; j++)
  {
   mvaddch(i+y, j+x, fig[i][j]);
  }
 } 
}
void copy_fig(int fig_[][4], int new_fig[][4])
{
 for(int i = 0; i < 4; i++)
 {
  for(int j = 0; j < 4; j++)
  {
   fig_[i][j] = new_fig[i][j];
  }
 }
}

void print_cup (int cup[][CUP_X], int y, int x)
{
 
 for (int i = 0; i < CUP_Y; i++)
 {
  for (int j = 0; j < CUP_X; j++)
  {
   mvaddch(i+y, j+x, cup[i][j]);
  }
 } 
}
 void cup (int cup_arr [][CUP_X], int fig_[][4], int a, int b)
 {
  for (int i = 0; i < 4; i++)
  {
   for (int j = 0; j < 4; j++)
   {
    if (fig_[i][j] == '#')
    cup_arr[i+a][j+b] = fig_[i][j];
   }
  }
 }

void cup_fill (int cup[][CUP_X])
{
 for (int i = 0; i < CUP_Y; i++)
 {
  for(int j = 0; j < CUP_X; j++)
  {
   cup[i][j] = empty;
  }
 }
}


bool clash_fig( int fig_[][4], int cup[][CUP_X], int y, int x)
{
 for(int i = 0; i < 4; i++ )
 {
  for(int j = 0; j < 4; j++)
  {
   if ((fig_[i][j] == '#') && (i+y >= CUP_Y || j+x >= CUP_X))
   return 0;
   else if ((fig_[i][j] == '#') && (cup[i+y][j+x] == '#'))
   return 0;
  }
 }
 return 1;
}

void copy_cup(int cup_arr[][CUP_X], int new_arr[][CUP_X])
{
 
 for(int i = 0; i < CUP_Y; i++)
 {
  for(int j = 0; j < CUP_X; j++)
  {
   new_arr[i][j] = cup_arr[i][j] ;
  }
 }
}

bool left_side(int fig_[][4], int cup[CUP_Y][CUP_X], int x)
{
 for(int i = 0; i < 4; i++)
 {
  for (int j = 0; j < 4; j++)
  {
   if (fig_[i][j] == '#' && x+j < 0) 
   return 0;
   
  }
 }
 return 1;
}

bool right_side(int fig_[][4], int cup[CUP_Y][CUP_X], int x)
{
 for(int i = 0; i < 4; i++)
 {
  for (int j = 0; j < 4; j++)
  {
   if (fig_[i][j] == '#' && j+x >= CUP_X)
   return 0;
  }
 }
 return 1;
}

void turn_fig(int fig_[][4], int new_fig[][4])
{
 for(int i = 0;i < 4; i++)
 {
  for(int j = 0;j < 4; j++)
  {
   new_fig[j][i] = fig_[i][j];
  }
 }
}

void  generate_fig(int fig_[4][4])
{
 int fig_arr [2][4][4] = {{{' ', '#', ' ', ' '},
                           {' ', '#', ' ', ' '},
                           {' ', '#', ' ', ' '},
                           {' ', '#', ' ', ' '}},{{' ', ' ', ' ', ' '},
                                                  {' ', '#', '#', ' '},
                                                  {' ', '#', '#', ' '},
                                                  {' ', ' ', ' ', ' '}} }; 
                                                  
 int num = rand() % 2;
 
  for(int i = 0; i < 4; i++)
  {
   for(int j = 0; j < 4; j++)
   { 
     fig_[i][j] = fig_arr[num][i][j];
   }
  }
                                                    
}

bool complete_str (int cup_arr[][CUP_X], int num_str)
{
 
  for(int j = 0; j < CUP_X; j++)
  {
   if (cup_arr[num_str][j] == empty)
   {
    return 0;    
   }
  }
 return 1;
}

void delete_str(int cup_arr[][CUP_X], int num)
{
  for(int i = num; i > 0; i--)
  {
   for(int j = 0; j < CUP_X; j++)
   {
    cup_arr[i][j] = cup_arr[i-1][j];    
      
   }
  }
   
}


void comp_and_del(int cup_arr[][CUP_X])
{
 for(int i = 0; i < CUP_Y; i++)
 {  
   if(complete_str(cup_arr, i) == 1)
   {
    delete_str(cup_arr, i);
    //mvaddstr(15,15,"oooo");
   } 
 }
}

void delay_fig(int delay, int fig_[][4], int cup_arr[][CUP_X], int y)
{
  time_t sec = time(NULL);
  int new_cup[CUP_Y][CUP_X];
  int new_time = sec + delay;
  
  
  while (time(NULL) < new_time)
  {
    int a = getch();

  if( a == 'a' || a == 'A')
  {
   mean_x -=1;
   
   if(left_side(fig_, cup_arr, mean_x) == 0)
   {
    mean_x +=1;
   }  
    
  }
  else if (a == 'd' || a == 'D')
  {
   
   mean_x +=1;
   if(right_side(fig_, cup_arr, mean_x) == 0)
   mean_x -=1;
  }
  else if(a == 's' || a == 'S')
  {
   y++;
  }
  if(clash_fig(fig_, cup_arr, y+1, mean_x) == 0)
   {
    cup(cup_arr, fig_, y, mean_x);
    y = 0;
    generate_fig(fig_);
   }
  
   
  copy_cup(cup_arr, new_cup);
  cup(new_cup, fig_, y, mean_x);
  print_cup(new_cup, 0, 0);
  }

}

void move_fig(int fig_[][4], int cup_arr[][CUP_X])
{
 
 int new_cup[CUP_Y][CUP_X];
 int new_fig[4][4];
 
  
 for (int y = 0; ;y++)
 {
  int a = getch();
  delay_fig(DELAY, fig_, cup_arr, y);
   if(a == 'q' || a == 'Q')
  {
   turn_fig(fig_,new_fig);
   copy_fig(fig_, new_fig);
  }
  
  if(clash_fig(fig_, cup_arr, y+1, mean_x) == 0)
   {
    cup(cup_arr, fig_, y, mean_x);
    y = 0;
    generate_fig(fig_);
   }
  comp_and_del(cup_arr); 
   
  copy_cup(cup_arr, new_cup);
  cup(new_cup, fig_, y, mean_x);
  print_cup(new_cup, 0, 0);
  
 }
 
}



int main()
{
  
  initscr();
  srand(time(NULL));
  int cup_arr[CUP_Y][CUP_X] = {{empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                               {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                               {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                               {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                               {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                               {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                               {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                               {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                               {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                               {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},};
 cup_fill (cup_arr);
 int fig_I [4][4] = {{' ', '#', ' ', ' '},
                     {' ', '#', ' ', ' '},
                     {' ', '#', ' ', ' '},
                     {' ', '#', ' ', ' '}};
                     
 int fig_O [4][4] = {{' ', ' ', ' ', ' '},
                     {' ', '#', '#', ' '},
                     {' ', '#', '#', ' '},
                     {' ', ' ', ' ', ' '},};          
 int rand_fig[4][4];                     
 nodelay(stdscr, 1);
 generate_fig(rand_fig);
 move_fig(rand_fig, cup_arr); 
 

 
 getch();
 endwin();
}

//