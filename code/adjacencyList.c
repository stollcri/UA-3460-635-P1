/**
 * Adjacency List
 * Christopher Stoll, 2014
 */

#include "dataStructures.c"

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
