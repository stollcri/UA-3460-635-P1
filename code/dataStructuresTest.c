#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.c"

int main(int argc, char const *argv[]) {
	struct queue *myQueue = newQueue();
	enqueue(myQueue, 1);
	enqueue(myQueue, 2);

	return 0;
}