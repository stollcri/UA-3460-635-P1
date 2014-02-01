/**
 * Run Ford-Fullkerson tests
 */

#include <stdio.h>
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

	if (sink > 0) {
		struct graph *testGraph = createGraphFromFile(fileName);
		maximumFlow = maxFlow(testGraph, source, sink);

		if (maximumFlow == expectedFlow) {
			printf("    ~~%s     OK%s, Max Flow = %d / %d (%s) \n", KGRN, KWHT, maximumFlow, expectedFlow, fileName);
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
	testMaxFlowWithFile("testdata/testList-002.txt", 0, 3, 2000000);
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

	printf("  ~~~~ testMaxFlow complete. \n");
}

int main(int argc, char const *argv[]) {
	testMaxFlow();
	printf("~~~~~~ testFordFulkerson complete. \n");
	return 0;
}