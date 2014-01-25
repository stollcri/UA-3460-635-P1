#include <stdio.h>
#include <stdlib.h>
#include "AdjacencyList.c"

void printGraph(struct graph* currentGraph) {
    for (int v = 0; v < currentGraph->verticesCount; ++v) {
        struct node* pCrawl = currentGraph->adjacencyList[v].head;
        
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->vertex);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[]) {
	struct graph *myGraph = createGraph(12);
	/*
	addEdge(myGraph, 0, 1);
	addEdge(myGraph, 1, 2);
	addEdge(myGraph, 1, 3);
	addEdge(myGraph, 1, 4);
	addEdge(myGraph, 2, 5);
	addEdge(myGraph, 2, 6);
	addEdge(myGraph, 4, 7);
	addEdge(myGraph, 4, 8);
	addEdge(myGraph, 5, 9);
	addEdge(myGraph, 5, 10);
	addEdge(myGraph, 7, 11);
	addEdge(myGraph, 7, 12);
	*/
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

	return 0;
}