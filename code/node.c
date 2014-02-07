/**
 * Node Data Structure
 * Christopher Stoll, 2014
 */

#ifndef INCLUDE_NODE
#define INCLUDE_NODE

#include <stdlib.h>

/**
 * Simple node structure
 */
struct node {
	int vertex;
	struct node *next;
	int capacity; // capacity to this node
	int flow; // flow to this node
	int originalCapacity; // so we can find newly zeroed vertexes

	// WARNING: shortcut to get min cut working quickly
	// do not use for anything else without careful consideration
	int altVertex;

	// Only to be used for image Segmentation
	int isVisited;
};

/**
 * Node creation function with a cost
 */
struct node *newNodeWithCostAndFlow(int vertex, int capacity, int flow) {
	struct node *thisNode = (struct node*) malloc(sizeof(struct node));

	thisNode->vertex = vertex;
	thisNode->next = NULL;
	thisNode->capacity = capacity;
	thisNode->flow = flow;

	thisNode->originalCapacity = capacity;
	thisNode->altVertex = 0;
	thisNode->isVisited = 0;

	return thisNode;
}

/**
 * Node creation function with a cost
 */
struct node *newNodeWithCost(int vertex, int capacity) {
	return newNodeWithCostAndFlow(vertex, capacity, 0);
}

/**
 * Node creation function
 */
struct node *newNode(int vertex) {
	return newNodeWithCost(vertex, 0);
}

#endif
