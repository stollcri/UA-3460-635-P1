#include <stdio.h>
#include "breadthFirstSearch.c"

void testBFS() {
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
	struct graph *testGraph = createGraphFromFile("testdata/testList-advanced.txt");
	bfs(testGraph, 0, 12);

	printf("  ~~~~ testBFS complete. \n");
}

int main(int argc, char const *argv[]) {
	testBFS();
	printf("~~~~~~ testBreadthFirstSearch complete. \n");
	return 0;
}