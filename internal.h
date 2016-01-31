#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>

#define MEM 81920
#define READY 1
#define RUNNING 2
#define JOIN 3
#define KILL 4

typedef struct myThread {
    ucontext_t Thread;
    int state;
    struct myThread *parent;
    int sNum;
}_MyThread;

struct node {
	_MyThread *Thread;
	struct node *ptr;
}*front, *rear, *temp, *front1;

typedef struct queue {
	struct node *front;
	struct node *rear;
	int size;
}Queue;

void enqueue(_MyThread *thread, Queue *q);
int checkIfQueueIsEmpty(Queue *queue);