#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int data;
	struct node * next;
}node;

typedef struct queue {
	node * front;
	node * rear;
	int size;
}Queue;



void InitQueue(Queue* Q) {
	node* q = (node *)malloc(sizeof(node));
	if (!q) {
		printf("stackoverflow");
		exit(0);
	}
	Q->front = q;
	Q->rear = q;
	Q->size = 0;
}

void DestroyQueue(Queue* Q) {
	if (Q != NULL)
		Q = NULL;
}

void ClearQueue(Queue* Q) {
	if (Q->front != Q->rear)
		Q->rear = Q->front;
}

bool QueueEmpty(Queue* Q) {
	return (Q->front == Q->rear);
}

void GetHead(Queue Q, int* e) {
	*e = Q.front->data;
}

void EnQueue(Queue * Q, int e) {
	node* q = (node *)malloc(sizeof(node));
	if (!q) {
		printf("stackoverflow");
		exit(0);
	}
	Q->rear->data = e;
	Q->rear=Q->rear->next = q;
	Q->size++;
}

void DeQueue(Queue* Q, int* e) {
	if (!QueueEmpty(Q)) {
		*e = Q->front->data;
		Q->front = Q->front->next;
		Q->size--;
	}
}
int QueueLength(Queue Q) {
	return Q.size;
}

int main() {
	Queue Triangle;
	InitQueue(&Triangle);
	EnQueue(&Triangle,1);
	EnQueue(&Triangle, 2);
	EnQueue(&Triangle, 1);

	int a, b, i = 0;
	int foobar;

	while(i <11) {
		a = Triangle.front->data;
		node* foo = Triangle.front->next;
		b = foo->data;
		DeQueue(&Triangle, &foobar);
		printf("%5d", foobar);
		if (a == 1) {
			EnQueue(&Triangle, 1);
			if (b == 1) {
				printf("\n");
				++i;
			}
			else
				EnQueue(&Triangle,a+b);
		}
		else {
			EnQueue(&Triangle, a + b);
		}
	}
	return 0;
}