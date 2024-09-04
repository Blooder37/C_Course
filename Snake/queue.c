#include <stdio.h>
#include <stdlib.h>
#include <ncurses/curses.h>

#include "queue.h"

void init(queue* q) {
    q->head = 0;
    q->tail = 0;
    q->n = 0;

}

int push(queue* q, Dot a) {
    if(q->n == QSIZE) {
        printw("Queue full.");
        return -1;
    }
    else {
        q->qu[q->tail] = a;
        q->tail = (q->tail + 1) % QSIZE;
        q->n++;
    }
}

Dot pop(queue* q) {
    if(q->n == 0) {
        Dot a = {0, 0};
        printw("Queue empty.");
        return a;
    }
    else {
        Dot res = q->qu[q->head];
        q->head = (q->head + 1) % QSIZE;
        q->n--;
        return res;
    }
}