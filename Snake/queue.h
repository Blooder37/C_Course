#ifndef QUEUE
#define QUEUE
#define QSIZE 255

typedef struct {
    int y;
    int x;
} Dot;

typedef struct {
    Dot qu[QSIZE];
    int head;
    int tail;
    int n;
} queue;

void init(queue* q);

int push(queue* q, Dot a);

Dot pop(queue* q);
    
#endif