#include <stdio.h>
#include "dtree.c"
#include "queue.c"

void testQueue() {
	struct queue *myQueue = newQueue();

	struct dtree *myTree1 = newTree(NULL);
	struct dtree *myTree2 = newTree(NULL);
	struct dtree *myTree3 = newTree(NULL);
	struct dtree *myTree4 = newTree(NULL);

	enqueue(myQueue, myTree1);
	enqueue(myQueue, myTree2);
	enqueue(myQueue, myTree3);
	enqueue(myQueue, myTree4);

	dequeue(myQueue);
	dequeue(myQueue);
	dequeue(myQueue);
	dequeue(myQueue);
	dequeue(myQueue);

	printf("  ~~~~ testQueue complete. (no seg fault, then all is well) \n");
}

int main(int argc, char const *argv[]) {
	testQueue();
	printf("~~~~~~ testDataSructures complete. \n");
	return 0;
}