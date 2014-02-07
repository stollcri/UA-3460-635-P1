/**
 * Run Ford-Fullkerson tests
 */

#include <stdio.h>
#include <sys/time.h>
#include "../fordFulkerson.c"

#define TIME_LIMIT 4000000000

void testMaxFlowWithFile(char *fileName, int source, int sink, int V, int E, int numberOfRuns) {
	int maximumFlow = 0;
	struct timeval stop, start;

	if (sink > 0) {
		long thisTime = 0;
		long totalTime = 0;
		struct graph *testGraph;

		for(int i = 0; i < numberOfRuns; ++i) {
			testGraph = createGraphFromFile(fileName);
			gettimeofday(&start, NULL);
			maximumFlow = maxFlow(testGraph, source, sink);
			gettimeofday(&stop, NULL);

			thisTime = (stop.tv_usec - start.tv_usec);

			// try to avoid outliers
			if ((totalTime == 0) || (thisTime < (totalTime * 10))) {
				if ((thisTime > 0) && (thisTime < TIME_LIMIT)) {
					totalTime += thisTime;
					//printf("%d\t%d\t%u\t(%d) \t%s \n", V, E, stop.tv_usec - start.tv_usec, maximumFlow, fileName);
				}
			}
		}
		printf("%d,%d,%d,%ld\n", V, E, maximumFlow, totalTime/numberOfRuns);
	}
}

void testMaxFlow() {
	int itterations = 25;

	printf("Average of %d runs. \n", itterations);
	//printf("V\tE\tus\t(max flow) \n");
	printf("V,E,flow,uS\n");

	testMaxFlowWithFile("testdata/v0256e1024.txt", 1, 256, 256, 1024, itterations);
	testMaxFlowWithFile("testdata/v0256e2048.txt", 1, 256, 256, 2048, itterations);
	testMaxFlowWithFile("testdata/v0256e4096.txt", 1, 256, 256, 4096, itterations);
	testMaxFlowWithFile("testdata/v0256e8192.txt", 1, 256, 256, 8192, itterations);
	testMaxFlowWithFile("testdata/v0512e1024.txt", 1, 510, 512, 1024, itterations);
	testMaxFlowWithFile("testdata/v0512e2048.txt", 1, 510, 512, 2048, itterations);
	testMaxFlowWithFile("testdata/v0512e4096.txt", 1, 512, 512, 4096, itterations);
	testMaxFlowWithFile("testdata/v0512e8192.txt", 1, 512, 512, 8192, itterations);
	testMaxFlowWithFile("testdata/v1024e2048.txt", 1, 1020, 1024, 2048, itterations);
	testMaxFlowWithFile("testdata/v1024e4096.txt", 1, 1022, 1024, 4096, itterations);
	testMaxFlowWithFile("testdata/v1024e8192.txt", 1, 1024, 1024, 8192, itterations);
	testMaxFlowWithFile("testdata/v2048e4096.txt", 1, 2046, 2048, 4096, itterations);
	testMaxFlowWithFile("testdata/v2048e8192.txt", 1, 2046, 2048, 8192, itterations);
	testMaxFlowWithFile("testdata/v2048e9999.txt", 1, 2048, 2048, 9999, itterations);

	testMaxFlowWithFile("testdata/xl-v10000e20000.txt", 1, 1000, 10000, 20000, itterations);
	testMaxFlowWithFile("testdata/xl-v10000e40000.txt", 1, 10000, 10000, 40000, itterations);
	testMaxFlowWithFile("testdata/xl-v10000e80000.txt", 1, 10000, 10000, 80000, itterations);
	testMaxFlowWithFile("testdata/xl-v25000e50000.txt", 1, 20000, 25000, 50000, itterations);
	testMaxFlowWithFile("testdata/xl-v25000e100000.txt", 1, 20000, 25000, 100000, itterations);
	testMaxFlowWithFile("testdata/xl-v25000e99000.txt", 1, 20000, 25000, 99000, itterations);
	testMaxFlowWithFile("testdata/xl-v30000e070000.txt", 1, 30000, 30000, 70000, itterations);
	testMaxFlowWithFile("testdata/xl-v30000e140000.txt", 1, 30000, 30000, 140000, itterations);
	testMaxFlowWithFile("testdata/xl-v30000e280000.txt", 1, 30000, 30000, 280000, itterations);
	testMaxFlowWithFile("testdata/xl-v40000e100000.txt", 1, 40000, 40000, 100000, itterations);
	testMaxFlowWithFile("testdata/xl-v40000e160000.txt", 1, 40000, 40000, 160000, itterations);
}

int main(int argc, char const *argv[]) {
	testMaxFlow();
	printf("~~~~~~ analysisFordFulkerson complete. \n");
	return 0;
}