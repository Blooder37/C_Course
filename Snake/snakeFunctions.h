#ifndef SNAKE
#define SNAKE
#include "queue.h"

#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a>b)?a:b)

void draw_line(Dot z1, Dot z2);
void check_key(Dot* direction, int menu);
void snake_move(Dot* snakeHead, queue* snakeTail, Dot direction, int* eattenApples, int* menu, Dot* apple, int width, int height, int indent);
void draw(int width, int height, queue snakeTail, Dot snakeHead, Dot apple, int eattenApples, int indent);
void draw_menu(int height, int width, int choice);

#endif