/**
 * Breadth Firt Search
 * Christopher Stoll, 2014
 */

#include <stdlib.h>
#include "linkedList.c"
#include "graph.c"
#include "queue.c"

struct list bfs(struct graph* thisGraph, int start, int end) {
	struct node* startNode = thisGraph->adjacencyList[start].head;
}