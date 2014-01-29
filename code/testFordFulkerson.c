#include <stdio.h>
#include "fordFulkerson.c"

void testMaxFlow() {
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
	maxFlow(testGraph, 0, 12);

	printf("  ~~~~ testMaxFlow complete. \n");
}

int main(int argc, char const *argv[]) {
	testMaxFlow();
	printf("~~~~~~ testFordFulkerson complete. \n");
	return 0;
}