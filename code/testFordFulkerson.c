#include <stdio.h>
#include "fordFulkerson.c"

void testMaxFlow() {
	struct graph *testGraph = createGraphFromFile("testdata/testList-advanced.txt");
	maxFlow(testGraph, 0, 12);

	printf("  ~~~~ testMaxFlow complete. \n");
}

int main(int argc, char const *argv[]) {
	testMaxFlow();
	printf("~~~~~~ testFordFulkerson complete. \n");
	return 0;
}