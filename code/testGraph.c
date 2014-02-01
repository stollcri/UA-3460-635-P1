#include <stdio.h>
#include "graph.c"

void printGraph(struct graph* currentGraph) {
    for (int v = 0; v < currentGraph->verticesCount; ++v) {
        struct node *currentNode = currentGraph->adjacencyList[v].head;
        
        printf("Adjacency list of vertex %d\n head", v);
        while (currentNode) {
            printf(" -> %d (%d)", currentNode->vertex, currentNode->capacity);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}

void testGraph() {
	struct graph *myGraph = createGraph(1+12);
	
	int myList[12][3] = {
		{0, 1, 99},
		{1, 2, 99},
		{1, 3, 99},
		{1, 4, 99},
		{2, 5, 99},
		{2, 6, 99},
		{4, 7, 99},
		{4, 8, 99},
		{5, 9, 99},
		{5, 10, 99},
		{7, 11, 99},
		{7, 12, 99}
	};
	addEdgesWithCost(myGraph, 12, myList);
	printGraph(myGraph);

	printf("  ~~~~ testGraph complete. \n");
}

void testGraphFromFile() {
	struct graph *myGraph = createGraphFromFile("testdata/testList-advanced.txt");
	printGraph(myGraph);

	printf("  ~~~~ testGraphFromFile complete. \n");
}

int main(int argc, char const *argv[]) {
	testGraph();
	testGraphFromFile();
	printf("~~~~~~ testAdjacencyList complete. \n");
	return 0;
}