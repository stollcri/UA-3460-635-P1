#include <stdio.h>
#include <stdlib.h>
#include "linkedList.c"
#include "queue.c"

void testQueue() {
	struct queue *myQueue = newQueue();

	enqueue(myQueue, 1);
	enqueue(myQueue, 2);
	enqueue(myQueue, 3);
	enqueue(myQueue, 4);

	dequeue(myQueue);
	dequeue(myQueue);
	dequeue(myQueue);
	dequeue(myQueue);
	dequeue(myQueue);

	printf("testQueue complete. (no seg fault, then all is well) \n");
}

int main(int argc, char const *argv[]) {
	testQueue();

	return 0;
}