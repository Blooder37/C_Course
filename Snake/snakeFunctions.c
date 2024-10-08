#include <stdio.h>
#include <stdlib.h>
#include <ncurses/curses.h>
#include <unistd.h>

#include "snakeFunctions.h"
#include "queue.h"


void draw_line(Dot z1, Dot z2) {
    //проверка не выходят ли точки за экран
    float a, b;
    int dx, dy, flag = 1;
    dx = z2.x-z1.x;
    dy = z2.y-z1.y;
    if(dx != 0) {
        a = (float)dy / (float)dx;
    }
    b = (float)z1.y - (float)a*z1.x;
    
    if(abs(dx)>=abs(dy)) {
        for(int i = MIN(z1.x, z2.x); i<=MAX(z1.x, z2.x); i++) {
            int y = a*i+b;
            move(y, i);
            if(a>=1 && a<=4) {
                addch('\\');
            }
            else if(a>=-1 && a<1) {
                addch('-');
            }
            else if(a>4 || a<-4) {
                addch('|');
            }
            else if(a<=-1 && a>=-4) {
                addch('/');
            }
        }
    }
    else {
        for(int i = MIN(z1.y, z2.y); i<=MAX(z1.y, z2.y); i++) {
            int x;
            if(dx == 0) {
                a = 99999;
                x = z1.x;
            }
            else {
                x = ((float)i-b)/a;
            }
            move(i, x);
            if(abs(a)>4) {
                addch('|');
            }
            else if(a>=1 && a<=4) {
                addch('\\');
            }
            else if(abs(a)<1) {
                addch('-');
            }
            
            else if(a<=-1 && a>=-4) {
                addch('/');
            }
        }
    }
    refresh();
}


void check_key(Dot* direction, int* menu) {
    char c = getch();
    switch(c) {
        case 'd':
            if(direction->y == 0 && direction->x == -1) break;
            direction->y = 0;
            direction->x = 1;
            break;
        case 'a':
            if(direction->y == 0 && direction->x == 1) break;
            direction->y = 0;
            direction->x = -1;
            break;
        case 's':
            if(direction->y == -1 && direction->x == 0) break;
            direction->y = 1;
            direction->x = 0;
            break;
        case 'w':
            if(direction->y == 1 && direction->x == 0) break;
            direction->y = -1;
            direction->x = 0;
            break;
        case 'q':
            *menu = 1;
            break;
    }
    while ((c = getch()) != EOF) { }
}


void snake_move(Dot* snakeHead, queue* snakeTail, Dot direction, int* eattenApples, int* menu, Dot* apple, int width, int height, int indent, int* mouth, int solid) {
    snakeHead->x += direction.x;
    snakeHead->y += direction.y;
    Dot pushing = {snakeHead->y-direction.y, snakeHead->x-direction.x};
    if(solid) {
        if(snakeHead->x <= indent || snakeHead->x >= width-indent || snakeHead->y <= indent || snakeHead->y >= height-indent) {
            clear();
            *menu = 1;
            return;
        }
    }
    else {
        if(snakeHead->x <= indent) {
            snakeHead->x = width-indent-1;
        }
        else if(snakeHead->x >= width-indent) {
            snakeHead->x = indent+1;
        }
        if(snakeHead->y <= indent) {
            snakeHead->y = height-indent-1;
        }
        else if(snakeHead->y >= height-indent) {
            snakeHead->y = indent+1;
        }
    }

    for(int i = 0; i < snakeTail->n; i++) {
        Dot tmp = snakeTail->qu[(snakeTail->head+i) % QSIZE];
        if(tmp.y == snakeHead->y && tmp.x == snakeHead->x) {
            clear();
            *menu = 1;
            return;
        }
    }

    if(snakeHead->y == apple->y && snakeHead->x == apple->x) {
        *eattenApples += 1;
        *mouth = 1;
        push(snakeTail, pushing);
        do {
            apple->y = rand() % (height-2*indent-3) + indent+1;
            apple->x = rand() % (width-2*indent-3) + indent+1;
        } while (mvinch(apple->y, apple->x) != ' ');
    }
    else {
        if(snakeTail->n > 0) {
            push(snakeTail, pushing);
            pop(snakeTail);
        }
    }
}

void draw(int width, int height, queue snakeTail, Dot snakeHead, Dot apple, int eattenApples, int indent, int* mouth) {
    Dot first = {indent, indent};
    Dot second = {indent, width - indent};
    Dot third = {height - indent, indent};
    Dot fourth = {height - indent, width - indent};
    draw_line(first, second);
    draw_line(third, fourth);
    draw_line(first, third);
    draw_line(second, fourth);
    attron(COLOR_PAIR(1));
    for(int i = 0; i < snakeTail.n; i++) {
        Dot tmp = snakeTail.qu[snakeTail.head+i];
        mvaddch(tmp.y, tmp.x, '0');
    }
    if(*mouth) {
        attron(COLOR_PAIR(3));
        *mouth = 0;
    }
    mvaddch(snakeHead.y, snakeHead.x, '$');
    attroff(COLOR_PAIR(3));
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvaddch(apple.y, apple.x, '@');
    attroff(COLOR_PAIR(2));

    //Декоративные Штуки
    mvprintw(1, width/2-6, "The snake game");
    mvprintw(1, 1, "Press Q to leave");
    mvprintw(1, width-10, "Score: %d", eattenApples);
    mvprintw(height-1, 1, "Input:");
    refresh();
}

void draw_menu(int height, int width, int choice) {
    if(choice == 0) {
        attron(A_REVERSE);
    }
    Dot a1 = {5, width/2-5};
    Dot a2 = {5, width/2+3};
    Dot a3 = {7, width/2-5};
    Dot a4 = {7, width/2+3};

    draw_line(a1, a2);
    draw_line(a3, a4);
    mvaddch(6, width/2-5, '|');
    mvaddch(6, width/2+3, '|');
    attroff(A_REVERSE);
    mvprintw(6, width/2-3, "Start");

    if(choice == 1) {
        attron(A_REVERSE);
    }
    Dot b1 = {9, width/2-7};
    Dot b2 = {9, width/2+6};
    Dot b3 = {11, width/2-7};
    Dot b4 = {11, width/2+6};
    draw_line(b1, b2);
    draw_line(b3, b4);
    mvaddch(10, width/2-7, '|');
    mvaddch(10, width/2+6, '|');
    attroff(A_REVERSE);
    mvprintw(10, width/2-4, "Settings");

    if(choice == 2) {
        attron(A_REVERSE);
    }
    Dot c1 = {13, width/2-8};
    Dot c2 = {13, width/2+7};
    Dot c3 = {15, width/2-8};
    Dot c4 = {15, width/2+7};
    draw_line(c1, c2);
    draw_line(c3, c4);
    mvaddch(14, width/2-8, '|');
    mvaddch(14, width/2+7, '|');
    attroff(A_REVERSE);
    mvprintw(14, width/2-6, "Leaderboards");

    if(choice == 3) {
        attron(A_REVERSE);
    }
    Dot d1 = {17, width/2-5};
    Dot d2 = {17, width/2+3};
    Dot d3 = {19, width/2-5};
    Dot d4 = {19, width/2+3};
    draw_line(d1, d2);
    draw_line(d3, d4);
    mvaddch(18, width/2-5, '|');
    mvaddch(18, width/2+3, '|');
    attroff(A_REVERSE);
    mvprintw(18, width/2-3, "Quit");


    mvprintw(0, 1, "Press Z to chose");
    mvprintw(height-1, 1, "Input:");

    refresh();
}

void settings(int* indent, int height, int width, int* solid) {
    clear();
    int choice = 0;
    int out = 0;
    int max = 0;
    while(!out) {
        int ch = getch();
        switch(ch) {
            case KEY_DOWN:
                choice = (choice + 1) % 3;
                break;
            case KEY_UP:
                if(choice == 0) {
                    choice = 2;
                }
                else {
                    choice = choice - 1;
                }
                break;
                
            case KEY_RIGHT:
                if(choice == 0) {
                    if(*indent < 9) {
                        (*indent)++;
                    }
                    else max = 1;
                }
                else if(choice == 1) {
                    *solid = (*solid + 1) % 2;
                }
                break;
            case KEY_LEFT:
                if(choice == 0) {
                    if(*indent > 2) {
                        (*indent)--;
                    }
                    else max = 1;
                }
                else if(choice == 1) {
                    *solid = (*solid - 1) % 2;
                }
                break;
            case 'z':
                if(choice == 2) out = 1;
                break;
        }

        usleep(30000);
        clear();

        if(choice == 0) attron(A_REVERSE);
        mvprintw(4, width/2-3, "Indent");
        attroff(A_REVERSE);
        if(max) {
            attroff(A_REVERSE);
            attron(COLOR_PAIR(1));
            max = 0;
        }
        mvprintw(5, width/2, "%d", *indent);
        mvprintw(5, width/2-3, "<-");
        mvprintw(5, width/2+2, "->");
        attroff(COLOR_PAIR(1));

        if(choice == 1) attron(A_REVERSE);
        mvprintw(7, width/2-3, "Solid?");
        attroff(A_REVERSE);
        if(*solid) {
            mvprintw(8, width/2-1, "Yes");
        }
        else {
            mvprintw(8, width/2-1, "No");
        }
        mvprintw(8, width/2-3, "<-");
        mvprintw(8, width/2+2, "->");

        if(choice == 2) attron(A_REVERSE);
        mvprintw(10, width/2-2, "Back");
        attroff(A_REVERSE);

        mvprintw(height-1, 1, "Input:");
        refresh();
    }
    clear();
}