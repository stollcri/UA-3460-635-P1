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
void addEdge(struct graph *currentGraph, int source, int sink) {
	struct node *newNode = createNode(sink);

	newNode->next = currentGraph->adjacencyList[source].head;
	currentGraph->adjacencyList[source].head = newNode;

	newNode = createNode(source);
	newNode->next = currentGraph->adjacencyList[sink].head;
	currentGraph->adjacencyList[sink].head = newNode;
}

void addEdges(struct graph *currentGraph, int listLength, int adjacencyList[][2]) {
	for (int i = 0; i < listLength; ++i) {
		addEdge(currentGraph, adjacencyList[i][0], adjacencyList[i][1]);
	}
}
