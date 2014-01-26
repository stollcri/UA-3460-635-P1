#include <stdio.h>
#include "graph.c"

void printGraph(struct graph* currentGraph) {
    for (int v = 0; v < currentGraph->verticesCount; ++v) {
        struct node* pCrawl = currentGraph->adjacencyList[v].head;
        
        printf("Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->vertex);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

void testGraph() {
	struct graph *myGraph = createGraph(12);
	
	int myList[12][2];
	myList[0][0] = 0;
	myList[0][1] = 1;
	myList[1][0] = 1;
	myList[1][1] = 2;
	myList[2][0] = 1;
	myList[2][1] = 3;
	myList[3][0] = 1;
	myList[3][1] = 4;
	myList[4][0] = 2;
	myList[4][1] = 5;
	myList[5][0] = 2;
	myList[5][1] = 6;
	myList[6][0] = 4;
	myList[6][1] = 7;
	myList[7][0] = 4;
	myList[7][1] = 8;
	myList[8][0] = 5;
	myList[8][1] = 9;
	myList[9][0] = 5;
	myList[9][1] = 10;
	myList[10][0] = 7;
	myList[10][1] = 11;
	myList[11][0] = 7;
	myList[11][1] = 12;
	addEdges(myGraph, 12, myList);
	printGraph(myGraph);

	printf("  ~~~~ testGraph complete. \n");
}

int main(int argc, char const *argv[]) {
	testGraph();
	printf("~~~~~~ testAdjacencyList complete. \n");
	return 0;
}