/**
 * Run Ford-Fullkerson tests
 */

#include <stdio.h>
#include <sys/time.h>
#include "fordFulkerson.c"

void testMaxFlowWithFile(char *fileName, int source, int sink, int V, int E) {
	int maximumFlow = 0;
	struct timeval stop, start;

	if (sink > 0) {
		struct graph *testGraph;

		testGraph = createGraphFromFile(fileName);
		gettimeofday(&start, NULL);
		maximumFlow = maxFlow(testGraph, source, sink);
		gettimeofday(&stop, NULL);
		printf("%d\t%d\t%u\t(%d) \n", V, E, stop.tv_usec - start.tv_usec, maximumFlow);

		testGraph = createGraphFromFile(fileName);
		gettimeofday(&start, NULL);
		maximumFlow = maxFlow(testGraph, source, sink);
		gettimeofday(&stop, NULL);
		printf("%d\t%d\t%u\t(%d) \n", V, E, stop.tv_usec - start.tv_usec, maximumFlow);
	}
}

void testMaxFlow() {
	printf("V\tE\tus\t(max flow) \n");
	testMaxFlowWithFile("testdata/v0256e1024.txt", 1, 256, 256, 1024);
	testMaxFlowWithFile("testdata/v0256e2048.txt", 1, 256, 256, 2048);
	testMaxFlowWithFile("testdata/v0512e2048.txt", 1, 510, 512, 2048);
	testMaxFlowWithFile("testdata/v0512e4096.txt", 1, 512, 512, 4096);
	testMaxFlowWithFile("testdata/v1024e4096.txt", 1, 1022, 1024, 4096);
	testMaxFlowWithFile("testdata/v1024e8192.txt", 1, 1024, 1024, 8192);
	testMaxFlowWithFile("testdata/v2048e8192.txt", 1, 2046, 2048, 8192);
	testMaxFlowWithFile("testdata/v2048e9999.txt", 1, 2048, 2048, 9999);

	testMaxFlowWithFile("testdata/xl-v10000e40000.txt", 1, 10000, 10000, 40000);
	testMaxFlowWithFile("testdata/xl-v25000e100000.txt", 1, 20000, 25000, 100000);
	testMaxFlowWithFile("testdata/xl-v30000e140000.txt", 1, 30000, 30000, 140000);
	testMaxFlowWithFile("testdata/xl-v40000e160000.txt", 1, 40000, 40000, 160000);
}

int main(int argc, char const *argv[]) {
	testMaxFlow();
	printf("~~~~~~ analysisFordFulkerson complete. \n");
	return 0;
}