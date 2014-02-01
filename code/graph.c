/**
 * Graph Data Structure
 * Christopher Stoll, 2014
 */

#ifndef INCLUDE_GRAPH
#define INCLUDE_GRAPH

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include "linkedList.c"

#define MAX_LINE_SIZE 1024

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
	int i;
	struct graph *newGraph = (struct graph*) malloc(sizeof(struct graph));
	
	newGraph->verticesCount = verticesCount;
	newGraph->adjacencyList = (struct list*) malloc(sizeof(struct list) * verticesCount);

	for (i = 0; i < verticesCount; ++i) {
		newGraph->adjacencyList[i].head = NULL;
	}

	return newGraph;
}

/**
 * Add an edge to a graph with a cost
 */
void addEdgeWithCost(struct graph *thisGraph, int source, int sink, int cost) {
	/*
	 * TODO: add bounds checking
	 *       adding a backlink from 12 to 7 results in a
	 *       memmory address being assigned to the first itmes
	 *       list. To reproduce in the test file change:
	 *         struct graph *myGraph = createGraph(1+12);
	 *       to
	 *         struct graph *myGraph = createGraph(12);
	 */
	struct node *thisNode = newNodeWithCost(sink, cost);
	thisNode->next = thisGraph->adjacencyList[source].head;
	thisGraph->adjacencyList[source].head = thisNode;

	/* this code adds a link back from the sink to the source
	thisNode = newNodeWithCost(source, cost);
	thisNode->next = thisGraph->adjacencyList[sink].head;
	thisGraph->adjacencyList[sink].head = thisNode;
	*/
}

/**
 * Add an edge to a graph
 */
void addEdge(struct graph *thisGraph, int source, int sink) {
	addEdgeWithCost(thisGraph, source, sink, 0);
}

/**
 * Add a set of edges to a graph with costs
 */
void addEdgesWithCost(struct graph *thisGraph, int listLength, int adjacencyList[][3]) {
	int i;
	for (i = 0; i < listLength; ++i) {
		addEdgeWithCost(thisGraph, adjacencyList[i][0], adjacencyList[i][1], adjacencyList[i][2]);
	}
}

/**
 * Add a set of edges to a graph
 */
void addEdges(struct graph *thisGraph, int listLength, int adjacencyList[][2]) {
	int i;
	for (i = 0; i < listLength; ++i) {
		addEdge(thisGraph, adjacencyList[i][0], adjacencyList[i][1]);
	}
}

/**
 * Add edges to a graph from a line representing an adjacnecy list
 */
void addEdgesFromLine(struct graph *thisGraph, char *line, int startVertex) {
	int vertex = INT_MAX;
	int cost = INT_MAX;

	int nextDigit = 0;
	int currentNumber = 0;

	int loopCount = 0;
	int charCount = 0;
	while (line[loopCount]) {
		if (isspace(line[loopCount]) || line[loopCount] == '\n') {
			if (vertex == INT_MAX) {
				vertex = currentNumber;
			} else if (cost == INT_MAX) {
				cost = currentNumber;
				addEdgeWithCost(thisGraph, startVertex, vertex, cost);

				vertex = INT_MAX;
				cost = INT_MAX;
			}

			currentNumber = 0;
			charCount = 0;
		} else {
			nextDigit = line[loopCount] - '0';
			currentNumber *= 10;
			currentNumber += nextDigit;
			++charCount;
		}
		++loopCount;
	}
}

/**
 * Add a set of edges to a graph from a file
 */
struct graph *createGraphFromFile(char *fileName) {
	FILE *pFile;
	char line[MAX_LINE_SIZE];

	// TODO: There is surely a better way to do this,
	//       but it works for now
	int loopCount = 0;
	pFile = fopen(fileName, "r");
	if (pFile != NULL) {
		while (fgets(line, MAX_LINE_SIZE, pFile) != NULL) {
			if (line[0] != '#'){
				++loopCount;
			}
		}
	}
	fclose(pFile);
	struct graph *thisGraph = createGraph(loopCount+1);

	loopCount = 0;
	pFile = fopen(fileName, "r");
	if (pFile != NULL) {
		while (fgets(line, MAX_LINE_SIZE, pFile) != NULL) {
			if (line[0] != '#'){
				addEdgesFromLine(thisGraph, line, loopCount);
				++loopCount;
			}
		}
	}
	fclose(pFile);

	return thisGraph;
}

#endif
