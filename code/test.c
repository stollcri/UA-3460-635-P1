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

int main(int argc, char const *argv[])
{
	struct graph *myGraph = createGraph(12);
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
	printGraph(myGraph);

	return 0;
}