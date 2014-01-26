#include <stdio.h>
#include "graph.c"

void printGraph(struct graph* currentGraph) {
    for (int v = 0; v < currentGraph->verticesCount; ++v) {
        struct node *currentNode = currentGraph->adjacencyList[v].head;
        
        printf("Adjacency list of vertex %d\n head", v);
        while (currentNode) {
            printf(" -> %d", currentNode->vertex);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}

void testGraph() {
	struct graph *myGraph = createGraph(1+12);
	
	int myList[12][2] = {
		{0, 1},
		{1, 2},
		{1, 3},
		{1, 4},
		{2, 5},
		{2, 6},
		{4, 7},
		{4, 8},
		{5, 9},
		{5, 10},
		{7, 11},
		{7, 12}
	};
	addEdges(myGraph, 12, myList);
	printGraph(myGraph);

	printf("  ~~~~ testGraph complete. \n");
}

int main(int argc, char const *argv[]) {
	testGraph();
	printf("~~~~~~ testAdjacencyList complete. \n");
	return 0;
}