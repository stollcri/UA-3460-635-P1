/**
 * Breadth Firt Search
 * Christopher Stoll, 2014
 * Last updated by Michael Crouse, 1/26/14
 */

#include <stdlib.h>
#include "linkedList.c"
#include "graph.c"
#include "queue.c"
#include "dtree.c"
#include "stack.c"

#include <stdio.h>

#define DBG 0

/*
 * Perform BFS on a graph
 */
struct list *bfs(struct graph* thisGraph, int start, int end) {
	struct queue *bfsQueue = newQueue();
	int i, sinkFound;
	//an array to keep track of which nodes we have "seen"
	//nodes will be "grey" once seen and "black" once dequeued
	int * seen = (int *) malloc(sizeof(int) * thisGraph->verticesCount);
	for (i = 0; i < thisGraph->verticesCount; i++) seen[i] = 0;
	struct list *bfsPath;
	struct dtree *bfsTree, *currentBranch, *currentChild;
	struct node *startNode = thisGraph->adjacencyList[start].head;
	struct node *currentNode;
	struct node *adjacentNode;
	struct stack *traceStack;
	if(DBG) printf("BEGIN AT: %d \n", startNode->vertex);
	//build the root node for the results tree
	bfsTree = newTree(NULL);
	bfsTree->data = startNode;
	//enqueue the starting node
	//enqueue(bfsQueue, startNode->vertex);
	enqueue(bfsQueue, bfsTree);
	seen[startNode->vertex] = 1;
	sinkFound=0;
	// while there are items in the queue
	while ((currentBranch = dequeue(bfsQueue)) != NULL) {
	//while ((currentNode = dequeue(bfsQueue)) != NULL) {
		// if we have found the target
		currentNode = currentBranch->data;
		if(DBG) printf("OUTER WHILE... %d \n", currentNode->vertex);
		//
		// TODO: Make sure there are more nodes available
		//       If the source is not in the graph it seg faults
		//
		if (currentNode->vertex == end) {
			if(DBG) printf("END. \n");
			sinkFound=1;
			break;
		} else {
			currentChild = NULL;
			adjacentNode = thisGraph->adjacencyList[currentNode->vertex].head;
			// enqueue adjacent nodes that have not yet been seen
			while (adjacentNode != NULL) {
				if(DBG) printf("INNER WHILE... %d \n", adjacentNode->vertex);
				if (seen[adjacentNode->vertex]== 0) {
					if(DBG) printf("UNSEEN %d, QUEUEING\n", adjacentNode->vertex);
					if (currentChild==NULL) {
						currentBranch->children = newTree(currentBranch);
						currentChild = currentBranch->children;
					}
					else {
						currentChild->next = newTree(currentBranch);
						currentChild = currentChild->next;
					}
					currentChild->data = adjacentNode;
					enqueue(bfsQueue, currentChild);
					seen[adjacentNode->vertex] = 1;
				}
				adjacentNode = adjacentNode->next;
			}
		}
	}
	if (sinkFound == 1) { //we've found the result, it's stored in currentBranch
		//we can work our way up the tree thanks to it being doubly linked, but
		//that will return the results in reverse order.  
		traceStack = newStack();
		push(traceStack, currentBranch->data);
		do {
			if(DBG) printf("TRACEBACK AT NODE %d\n", currentBranch->data->vertex);
			currentBranch = currentBranch->parent;
			push(traceStack, currentBranch->data);
		} while(currentBranch != bfsTree);
		bfsPath = newList();
		currentNode = pop(traceStack);
		//bfsPath->head = newNode(currentNode->vertex);
		bfsPath->head = newNodeWithCost(currentNode->vertex, currentNode->capacity);
		if(DBG) printf("ADDING NODE %d TO LIST\n", currentNode->vertex);
		adjacentNode = bfsPath->head;
		while (currentNode->vertex != end) {
			currentNode = pop(traceStack);
			//adjacentNode->next = newNode(currentNode->vertex);
			adjacentNode->next = newNodeWithCost(currentNode->vertex, currentNode->capacity);
			if(DBG) printf("ADDING NODE %d TO LIST\n", currentNode->vertex);
			adjacentNode = adjacentNode->next;
		}
	}
	free(seen);
	return bfsPath;
}

