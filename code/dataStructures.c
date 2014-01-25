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
 * Node creation function
 */
struct node *createNode(int vertex) {
	struct node *newNode = (struct node*) malloc(sizeof(struct node));

	newNode->vertex = vertex;
	newNode->next = NULL;

	return newNode;
}