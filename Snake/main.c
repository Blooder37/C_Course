//TODO
//6.Разбивка по файлам+makefile
//7.Тп при касании поля, а не смерть от него

//MakeFile запускается и в cmd и в powershell, но не здесь???
//Клик не работает, но цвета работают

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses/curses.h>

#include "snakeFunctions.h"
#include "queue.h"

#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a>b)?a:b)


int main() {
    srand(time(NULL));
    initscr();
    timeout(0);
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    keypad(stdscr, TRUE);

    start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);

    MEVENT event;
    WINDOW *menu_win;

    int gameOver = 0;
    int menu = 1; //активность меню
    int indent = 5; //отступ игрового поля
    int framerate = 30;
    int width = COLS;
    int height = LINES; 
    int choice = 0;
    int mouth = 0;
    int solid = 0;

    while(!gameOver) {
        int eattenApples = 0;
        Dot apple = {rand() % (height-2*indent-3) + indent+1, rand() % (width-2*indent-3) + indent+1}; //спавн разобрать
        Dot snakeHead = {height / 2, width / 2};
        queue snakeTail;
        init(&snakeTail);
        Dot direction = {0, 1};

        draw_menu(height, width, choice);  

        int ch = getch();
        switch(ch) {
            case KEY_DOWN:
                choice = (choice + 1) % 4;
                break;
            case KEY_UP:
                if(choice == 0) {
                    choice = 3;
                }
                else {
                    choice = choice - 1;
                }
                break;
            case 'z':
                switch(choice) {
                    case 0:
                        menu = 0;
                        break;
                    case 1:
                        settings(&indent, height, width, &solid);
                        break;
                    case 2:
                        //Лидерборды
                        break;
                    case 3:
                        gameOver = 1;
                        break;
                }
        }
        
        while(!menu) {
            usleep(200000 - eattenApples*2000);
            check_key(&direction, &menu);
            clear();
            snake_move(&snakeHead, &snakeTail, direction, &eattenApples, &menu, &apple, width, height, indent, &mouth, solid);
            draw(width, height, snakeTail, snakeHead, apple, eattenApples, indent, &mouth);
            if(menu) {
                clear();
            }
        }
    }
    endwin();
}


//flash()

// curs_set(0); видно ли курсор, 0 - нет, 1 - да.
// init_pair(1, COLOR_YELLOW, COLOR_RED); устанавливает соответствие числу и набору цветов.
// attrset(COLOR_PAIR(1)); подгружает по числу соответствующий набор цветов.
// attroff(COLOR_PAIR(1)); убирает набор цветов.
// mvaddch(y, x, c); добавляет символ в координаты.
// napms(n); отправляет в сон на n миллисекунд.
// usleep(n); отправляет в сон на n микросекунд.