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
	struct node *newNode = createNode(sink);

	newNode->next = thisGraph->adjacencyList[source].head;
	thisGraph->adjacencyList[source].head = newNode;

	newNode = createNode(source);
	newNode->next = thisGraph->adjacencyList[sink].head;
	thisGraph->adjacencyList[sink].head = newNode;
}

/**
 * Add a set of edges to a graph
 */
void addEdges(struct graph *thisGraph, int listLength, int adjacencyList[][2]) {
	for (int i = 0; i < listLength; ++i) {
		addEdge(thisGraph, adjacencyList[i][0], adjacencyList[i][1]);
	}
}
