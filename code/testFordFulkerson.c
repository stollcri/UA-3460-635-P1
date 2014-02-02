/**
 * Run Ford-Fullkerson tests
 */

#include <stdio.h>
#include <sys/time.h>
#include "fordFulkerson.c"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void testMaxFlowWithFile(char *fileName, int source, int sink, int expectedFlow) {
	int maximumFlow = 0;
	struct timeval stop, start;

	if (sink > 0) {
		struct graph *testGraph = createGraphFromFile(fileName);
		gettimeofday(&start, NULL);
		maximumFlow = maxFlow(testGraph, source, sink);
		gettimeofday(&stop, NULL);

		if (maximumFlow == expectedFlow) {
			//printf("    ~~%s     OK%s, Max Flow = %d / %d (%s) \n", KGRN, KWHT, maximumFlow, expectedFlow, fileName);
			// measure time in microseconds
			printf("    ~~%s     OK%s, Max Flow = %d\t%u us \n", KGRN, KWHT, maximumFlow, stop.tv_usec - start.tv_usec);
		} else {
			printf("    ~~%s NOT OK%s, Max Flow = %d / %d (%s) \n", KRED, KWHT, maximumFlow, expectedFlow, fileName);
		}
	} else {
		printf("    ~~%s NOT OK%s, Bad Sink = %d \n", KRED, KWHT, sink);
	}
}

void testMaxFlow() {
	testMaxFlowWithFile("testdata/testList-basic.txt", 0, 3, 9);
	testMaxFlowWithFile("testdata/testList-advanced.txt", 0, 12, 26);
	
	testMaxFlowWithFile("testdata/testList-001.txt", 0, 5, 23);
	testMaxFlowWithFile("testdata/testList-002.txt", 0, 3, 20000);
	testMaxFlowWithFile("testdata/testList-003.txt", 0, 3, 9);
	testMaxFlowWithFile("testdata/testList-004.txt", 0, 13, 50);
	testMaxFlowWithFile("testdata/testList-005.txt", 0, 15, 50);

	testMaxFlowWithFile("testdata/v0256e1024.txt", 1, 256, 128);
	testMaxFlowWithFile("testdata/v0256e2048.txt", 1, 256, 360);
	testMaxFlowWithFile("testdata/v0512e2048.txt", 1, 510, 99);
	testMaxFlowWithFile("testdata/v0512e4096.txt", 1, 512, 421);
	testMaxFlowWithFile("testdata/v1024e4096.txt", 1, 1022, 26);
	testMaxFlowWithFile("testdata/v1024e8192.txt", 1, 1024, 311);
	testMaxFlowWithFile("testdata/v2048e8192.txt", 1, 2046, 27);
	testMaxFlowWithFile("testdata/v2048e9999.txt", 1, 2048, 145);

	testMaxFlowWithFile("testdata/xl-v10000e40000.txt", 1, 10000, 167);
	testMaxFlowWithFile("testdata/xl-v25000e100000.txt", 1, 20000, 0);
	testMaxFlowWithFile("testdata/xl-v30000e140000.txt", 1, 30000, 104);
	testMaxFlowWithFile("testdata/xl-v40000e160000.txt", 1, 40000, 60);

	printf("  ~~~~ testMaxFlow complete. \n");
}

int main(int argc, char const *argv[]) {
	testMaxFlow();
	printf("~~~~~~ testFordFulkerson complete. \n");
	return 0;
}