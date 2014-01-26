/**
 * Graph Data Structure
 * Christopher Stoll, 2014
 */

#ifndef INCLUDE_GRAPH
#define INCLUDE_GRAPH

#include <stdlib.h>
#include "linkedList.c"

/**
 * Simple graph structure
 */
struct graph {
	int verticesCount;
	struct list *adjacencyList;
};

/**
 * Graph creation function
 */
struct graph *createGraph(int verticesCount) {
	struct graph *newGraph = (struct graph*) malloc(sizeof(struct graph));
	
	newGraph->verticesCount = verticesCount;
	newGraph->adjacencyList = (struct list*) malloc(sizeof(struct list) * verticesCount);

	for (int i = 0; i < verticesCount; ++i) {
		newGraph->adjacencyList[i].head = NULL;
	}

	return newGraph;
}

/**
 * Add an edge to a graph
 */
void addEdge(struct graph *thisGraph, int source, int sink) {
	/*
	 * TODO: add bounds checking
	 *       adding a backlink from 12 to 7 results in a
	 *       memmory address being assigned to the first itmes
	 *       list. To reproduce in the test file change:
	 *         struct graph *myGraph = createGraph(1+12);
	 *       to
	 *         struct graph *myGraph = createGraph(12);
	 */
	struct node *thisNode = newNode(sink);
	
	thisNode->next = thisGraph->adjacencyList[source].head;
	thisGraph->adjacencyList[source].head = thisNode;

	thisNode = newNode(source);
	thisNode->next = thisGraph->adjacencyList[sink].head;
	thisGraph->adjacencyList[sink].head = thisNode;
}

/**
 * Add a set of edges to a graph
 */
void addEdges(struct graph *thisGraph, int listLength, int adjacencyList[][2]) {
	for (int i = 0; i < listLength; ++i) {
		addEdge(thisGraph, adjacencyList[i][0], adjacencyList[i][1]);
	}
}

#endif
