/**
 * Basic Data Structures
 * Christopher Stoll, 2014
 */

/**
 * Simple node structure
 */
struct node {
	int vertex;
	struct node *next;
};

/**
 * Simple list structure
 */
struct list {
	struct node *head;
};

/**
 * Simple queue structure
 */
struct queue {
	struct node *head;
	struct node *tail;
};

/**
 * Node creation function
 */
struct node *newNode(int vertex) {
	struct node *thisNode = (struct node*) malloc(sizeof(struct node));

	thisNode->vertex = vertex;
	thisNode->next = NULL;

	return thisNode;
}

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

		printf("NULL \n");
	} else {
		// TODO: finish this
		printf("NOT NULL \n");
	}
}

/**
 * Dequeue a node
 */
struct node *dequeue(struct queue *thisQueue) {
	// TODO: implement this
	struct node *thisNode = newNode(0);

	if (thisQueue->head == NULL) {
		printf("NULL \n");
	} else {
		printf("NOT NULL \n");
	}

	return thisNode;
}
