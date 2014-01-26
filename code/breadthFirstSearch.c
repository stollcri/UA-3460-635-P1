/**
 * Breadth Firt Search
 * Christopher Stoll, 2014
 */

#include <stdlib.h>
#include "linkedList.c"
#include "graph.c"
#include "queue.c"

#include <stdio.h>

/*
 * Perform BFS on a graph
 */
struct list bfs(struct graph* thisGraph, int start, int end) {
	struct queue *bfsQueue = newQueue();

	struct list *bfsPath = newList();
	struct node *startNode = thisGraph->adjacencyList[start].head;
	struct node *currentNode;
	struct node *adjacentNode;

	printf("BEGIN AT: %d \n", startNode->vertex);
	// enqueue the starting noce
	enqueue(bfsQueue, startNode->vertex);

	// while there are items in the queue
	while ((currentNode = dequeue(bfsQueue)) != NULL) {
		printf("OUTTER WHILE... %d \n", currentNode->vertex);
		// if we have found the target
		if (currentNode->vertex == end) {
			printf("END. \n");
			break;
		} else {

			adjacentNode = thisGraph->adjacencyList[currentNode->vertex].head;
			printf("HERE AT: %d \n", adjacentNode->vertex);
			// enqueue adjacent nodes
			while ((adjacentNode = currentNode->next) != NULL) {
				printf("INNER WHILE... %d \n", adjacentNode->vertex);
			}
		}
	}
	
	return *bfsPath;
}

