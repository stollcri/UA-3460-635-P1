/**
 * Queue Data Structure
 * Christopher Stoll, 2014
 */

#ifndef INCLUDE_QUEUE
#define INCLUDE_QUEUE

#include <stdlib.h>
#include "node.c"
#include "dtree.c"

/**
 * Simple queue structure
 */
struct queue {
	struct queueItem *head;
	struct queueItem *tail;
};

struct queueItem {
	struct queueItem * next;
	struct dtree * data;
};

/**
 * Queue creation function
 */
struct queue *newQueue() {
	struct queue *thisQueue = (struct queue*) malloc(sizeof(struct queue));

	thisQueue->head = NULL;
	thisQueue->tail = NULL;

	return thisQueue;
}

/**
 * Enqueue a node
 */
void enqueue(struct queue *thisQueue, struct dtree * thisBranch) {
	struct queueItem * thisItem = (struct queueItem*) malloc(sizeof(struct queueItem));
	thisItem->data = thisBranch;
	if (thisQueue->head == NULL) {
		thisQueue->head = thisItem;
		thisQueue->tail = thisItem;
	} else {
		thisQueue->tail->next = thisItem;
		thisQueue->tail = thisItem;
	}
	thisItem->next = NULL;
}

/**
 * Dequeue a node
 */
struct dtree *dequeue(struct queue *thisQueue) {
	struct queueItem * thisNode = thisQueue->head;
	struct dtree * result = NULL;
	if (thisNode != NULL) {
		if (thisNode->next != NULL) {
			thisQueue->head = thisNode->next;
		} else {
			thisQueue->head = NULL;
		}
		result = thisNode->data;
		free(thisNode);
	}
	return result;
}

#endif
