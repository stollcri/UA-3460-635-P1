#ifndef INCLUDE_ISQUEUE
#define INCLUDE_ISQUEUE

struct isQueue {
	struct isItem *head;
	struct isItem *tail;
};

struct isItem {
	struct isItem * next;
	struct node * data;
};

/**
 * Queue creation function
 */
struct isQueue *newISQueue() {
	struct isQueue *thisQueue = (struct isQueue*) malloc(sizeof(struct isQueue));

	thisQueue->head = NULL;
	thisQueue->tail = NULL;

	return thisQueue;
}

/**
 * Enqueue a node
 */
void isEnqueue(struct isQueue *thisQueue, struct node * thisBranch) {
	struct isItem * thisItem = (struct isItem*) malloc(sizeof(struct isItem));
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
struct node * isDequeue(struct isQueue *thisQueue) {
	struct isItem * thisNode = thisQueue->head;
	struct node * result = NULL;
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