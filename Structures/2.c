#include <stdio.h>
#include <ncurses/ncurses.h>

int main() {
    initscr();
    printw("Hello World");
    // refreshes the screen
    refresh();
    // pause the screen output
    getch();
    // deallocates memory and ends ncurses
    endwin();
    printf("Hello");
}