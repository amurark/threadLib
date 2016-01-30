#include "mythread.h"
#include "internal.h"

int count = 0;

void create() {
	front = rear = NULL;
}

int queuesize()
{
    return count;
}

void enqueue(_MyThread *thread, Queue *queue) {
	if(rear == NULL) {
		printf("Enqueuing: The first thread is added to ready queue.");
		rear = (struct node *)malloc(sizeof(struct node));
		rear->currentThread = thread;
		rear->ptr = NULL;
		front = rear;
		queue->rear = rear;
		queue->front = rear;
	} else {
		printf("Enqueuing: Another thread added to ready queue.");
		temp = (struct node *)malloc(sizeof(struct node));
		temp->currentThread = thread;
		temp->ptr = NULL;
		rear->ptr = temp;
		rear = temp;
		queue->rear = rear;
	}
	count++;
}

_MyThread *dequeue(Queue *queue) {
	front1 = front;
	if(front1 == NULL) {
		printf("Queue Empty: No element in the queue.");
		return 0;
	} else {
		_MyThread *temp;
		if(front1->ptr == NULL) {
			printf("Last Element: Last Element being dequeued, no more elements left in the queue.");
			temp = front->currentThread;
			free(front);
			front = NULL;
			rear = NULL;
			/**
			 * If there are no elements in the queue then the queue is empty, that means rear and front = NULL.
			 */
			queue->rear = NULL;
			queue->front = NULL;
			return temp;
		} else {
			printf("Dequeuing...");
			temp = front->currentThread;
			front1 = front1->ptr;
			free(front);
			front = front1;
			queue->front = front;
			return temp;
		}
	}
}

int checkIfQueueIsEmpty(Queue *queue) {
    if(queue->rear == NULL && queue->front == NULL) {
    	return 1;
    } else {
    	return 0;
    }
}
