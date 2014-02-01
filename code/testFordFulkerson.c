#include <stdio.h>
#include "fordFulkerson.c"

void testMaxFlow() {
	int maximumFlow = 0;
	struct graph *testGraph = createGraphFromFile("testdata/testList-advanced.txt");
	maximumFlow = maxFlow(testGraph, 0, 1024);

	printf("  ~~~~ testMaxFlow complete. (MAX FLOW = %d) \n", maximumFlow);
}

int main(int argc, char const *argv[]) {
	testMaxFlow();
	printf("~~~~~~ testFordFulkerson complete. \n");
	return 0;
}