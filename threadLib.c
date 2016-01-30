#include "internal.h"
#include "mythread.h"

ucontext_t Main, T1, CT;

_MyThread *currentThread;

Queue *readyQueue;
Queue *blockedQueue;

/**
 * Function to allocate resources
 */
void memAlloc(_MyThread *rt) {
	rt->Thread.uc_stack.ss_sp = malloc(MEM);
    rt->Thread.uc_stack.ss_size = MEM;
    rt->Thread.uc_stack.ss_flags = 0;
}


void MyThreadInit(void(*start_funct)(void *), void *args) {
    /**
     * Initializing Ready Queue
     */
    readyQueue = (Queue *)malloc(sizeof(Queue));
    /**
     * Initializing Blocked Queue
     */
    blockedQueue = (Queue *)malloc(sizeof(Queue));
    _MyThread *rt = (_MyThread *)malloc(sizeof(_MyThread));
    getcontext(&Main);
    getcontext(&rt->Thread);
    /**
     * Function to allocate resources
     */
    memAlloc(rt);
    makecontext(&rt->Thread, (void (*)(void))start_funct, 1, &args);
    swapcontext(&Main, &rt->Thread);

    //TODO: MyThreadJoinAll functionality.
    printf("main finished\n");
}


MyThread MyThreadCreate(void(*start_funct)(void *), void *args) {
	_MyThread *ct = malloc(sizeof(_MyThread));
	getcontext(&CT);
	getcontext(&ct->Thread);
	memAlloc(ct);
    currentThread = ct;
    makecontext(&ct->Thread, start_funct, 1, &args);
    enqueue(ct, readyQueue);
    //TODO: assign parent pointer.
    //TODO: assign child to queue.
	//TODO: Add to ready queue
	return (MyThread)ct;//created thread
}


