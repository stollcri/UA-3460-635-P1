/**
 * Queue Data Structure
 * Christopher Stoll, 2014
 */

#ifndef INCLUDE_QUEUE
#define INCLUDE_QUEUE

#include <stdlib.h>
#include "node.c"

/**
 * Simple queue structure
 */
struct queue {
	struct node *head;
	struct node *tail;
};

/**
 * Queue creation function
 */
struct queue *newQueue() {
	struct queue *newQueue = (struct queue*) malloc(sizeof(struct queue));

	newQueue->head = NULL;
	newQueue->tail = NULL;

	return newQueue;
}

/**
 * Enqueue a node
 */
void enqueue(struct queue *thisQueue, int vertex) {
	struct node *thisNode = newNode(vertex);

	if (thisQueue->head == NULL) {
		thisQueue->head = thisNode;
		thisQueue->tail = thisNode;
	} else {
		thisQueue->tail->next = thisNode;
		thisQueue->tail = thisNode;
	}
}

/**
 * Dequeue a node
 */
struct node *dequeue(struct queue *thisQueue) {
	struct node *thisNode = thisQueue->head;

	if (thisNode != NULL) {
		if (thisNode->next != NULL) {
			thisQueue->head = thisNode->next;
		} else {
			thisQueue->head = NULL;
		}
	}

	return thisNode;
}

#endif
