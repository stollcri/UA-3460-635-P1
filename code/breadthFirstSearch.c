/**
 * Breadth Firt Search
 * Christopher Stoll, 2014
 */

#include <stdlib.h>
#include "linkedList.c"
#include "graph.c"
#include "queue.c"

#include <stdio.h>

#define MAX_PATH_SIZE 256

struct list bfs(struct graph* thisGraph, int start, int end) {
	struct list *path = (struct list*) malloc(sizeof(struct list) * MAX_PATH_SIZE);
	struct node *startNode = thisGraph->adjacencyList[start].head;

	return *path;
}