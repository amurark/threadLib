#include "mythread.h"
#include "internal.h"

void create() {
	front = rear = NULL;
}

void enqueue(_MyThread *thread, Queue *queue) {
	if(rear == NULL) {
		printf("Enqueuing: The first thread is added to ready queue.\n");
		rear = (struct node *)malloc(sizeof(struct node));
		rear->Thread = thread;
		rear->ptr = NULL;
		front = rear;

		queue->rear = rear;
		queue->front = rear;
		queue->size = 1;
	} else {
		printf("Enqueuing: Another thread added to ready queue.\n");
		temp = (struct node *)malloc(sizeof(struct node));
		temp->Thread = thread;
		temp->ptr = NULL;
		rear->ptr = temp;
		rear = temp;

		queue->rear = rear;
		queue->size++;
	}
}

_MyThread *dequeue(Queue *queue) {
	_MyThread *temp;
	front1 = front;
	if(front1 == NULL) {
		printf("Queue Empty: No element in the queue.\n");
		return 0;
	} else {
		if(front1->ptr == NULL) {
			printf("Last Element: Last Element being dequeued, no more elements left in the queue.\n");
			temp = front->Thread;
			free(front);
			front = NULL;
			rear = NULL;
			/**
			 * If there are no elements in the queue then the queue is empty, that means rear and front = NULL.
			 */
			queue->rear = NULL;
			queue->front = NULL;

			//TODO: TEMP
			if(--queue->size == 0) {
				printf("Last Element dequeue confirmed.\n");
			}
			queue->size = 0;
		} else {
			printf("Dequeuing...\n");
			temp = front->Thread;
			front1 = front1->ptr;
			free(front);
			front = front1;
			queue->front = front;
			queue->size--;
			printf("\nmama mia %d\n",temp->sNum);
			
		}
	}
	printf("hey qwerty %d\n",temp->sNum);
	return temp;
}

int checkIfQueueIsEmpty(Queue *queue) {
    if(queue->rear == NULL && queue->front == NULL) {
    	return 1;
    } else {
    	return 0;
    }
}
