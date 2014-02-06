#include <stdio.h>
#include "../breadthFirstSearch.c"

void testBFS(char *filename, int source, int sink) {
	/*
	struct graph *testGraph = createGraph(1+12);
	int testList[12][2] = {
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
	addEdges(testGraph, 12, testList);
	*/
	struct graph *testGraph = createGraphFromFile(filename);
	struct list *thisPath = bfs(testGraph, source, sink);

	struct node *currentNode = thisPath->head;
	struct node *nextNode = NULL;

	printf("Path: ");
	while (currentNode) {
        printf("=> %d ", currentNode->vertex);
        nextNode = currentNode->next;
        currentNode = nextNode;
    }
    printf("\n");
	
	printf("  ~~~~ testBFS complete. \n");
}

int main(int argc, char *argv[]) {
	//testBFS(argv[1]);
	testBFS("testdata/testList-advanced.txt", 0, 12);
	printf("~~~~~~ testBreadthFirstSearch complete. \n");
	return 0;
}