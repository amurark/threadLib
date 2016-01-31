#include "internal.h"
#include "mythread.h"

ucontext_t Main, T1, CT;

_MyThread *currentThread, *invokingThread;

Queue *readyQueue;
Queue *blockedQueue;

int count = 0;

/**
 * Function to allocate resources
 */
void memAlloc(_MyThread *rt) {
    char *stack = (char *)malloc(8192*sizeof(char));
	rt->Thread.uc_stack.ss_sp = stack;
    rt->Thread.uc_stack.ss_size = MEM;
    rt->Thread.uc_stack.ss_flags = 0;
    rt->sNum = ++count;
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
    /**
     * Creating the main(root) thread.
     */
    _MyThread *rt = (_MyThread *)malloc(sizeof(_MyThread));
    getcontext(&Main);
    getcontext(&rt->Thread);
    /**
     * Function to allocate resources
     */
    memAlloc(rt);
    currentThread = rt;
    invokingThread = rt;
    makecontext(&rt->Thread, (void (*)(void))start_funct, 1, args);
    swapcontext(&Main, &rt->Thread);

    //TODO: MyThreadJoinAll functionality.
    printf("main finished\n");
}


MyThread MyThreadCreate(void(*start_funct)(void *), void *args) {
	_MyThread *ct = (_MyThread *)malloc(sizeof(_MyThread));
	getcontext(&ct->Thread);
	memAlloc(ct);
    //currentThread = ct;
    makecontext(&ct->Thread, start_funct, 1, args);
    //TODO: assign parent pointer.
    ct->parent = currentThread;
    //TODO: assign child to queue.
	//Add to ready queue
    enqueue(ct, readyQueue);
	return (MyThread)ct;//created thread
}

void MyThreadYield(void) {
    _MyThread *thread = currentThread;
    //printf("\n%d\n",currentThread->sNum);
    enqueue(currentThread, readyQueue);
    currentThread = dequeue(readyQueue);
    printf("\nasdasd %d\n",currentThread->sNum);
    //setcontext(&(currentThread->Thread));
    //swapcontext(&(thread->Thread),&(currentThread->Thread));
    /**
     * TODO: to be handled
     */
    if(currentThread == NULL) {
        printf("FAIL");
    }
}

void MyThreadExit(void) {

}


