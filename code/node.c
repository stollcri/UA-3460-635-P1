/**
 * Node Data Structure
 * Christopher Stoll, 2014
 */

#ifndef INCLUDE_NODE
#define INCLUDE_NODE

#include <stdlib.h>
#include <limits.h>

/**
 * Simple node structure
 */
struct node {
	int vertex;
	struct node *next;
	int costToNext;
};

/**
 * Node creation function
 */
struct node *newNode(int vertex) {
	struct node *thisNode = (struct node*) malloc(sizeof(struct node));

	thisNode->vertex = vertex;
	thisNode->next = NULL;
	thisNode->costToNext = INT_MAX;

	return thisNode;
}

#endif
