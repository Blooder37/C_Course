#ifndef SNAKE
#define SNAKE
#include "queue.h"

#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a>b)?a:b)

void draw_line(Dot z1, Dot z2);
void check_key(Dot* direction, int* menu);
void snake_move(Dot* snakeHead, queue* snakeTail, Dot direction, int* eattenApples, int* menu, Dot* apple, int width, int height, int indent, int* mouth, int solid);
void draw(int width, int height, queue snakeTail, Dot snakeHead, Dot apple, int eattenApples, int indent, int* mouth);
void draw_menu(int height, int width, int choice);
void settings(int* indent, int height, int width, int* solid);

#endif