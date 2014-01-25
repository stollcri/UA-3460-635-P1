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