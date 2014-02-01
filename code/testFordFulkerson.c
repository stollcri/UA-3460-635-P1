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

void testMaxFlowWithFile(char *fileName, int sink, int expectedFlow) {
	int maximumFlow = 0;
<<<<<<< HEAD
	struct graph *testGraph = createGraphFromFile("testdata/testList-advanced.txt");
	maximumFlow = maxFlow(testGraph, 0, 1024);
=======
>>>>>>> 5a7f1a70181a156dd87da1fb00dbb098017def03

	if (sink > 0) {
		struct graph *testGraph = createGraphFromFile(fileName);
		maximumFlow = maxFlow(testGraph, 0, sink);

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
	testMaxFlowWithFile("testdata/testList-basic.txt", 3, 9);
	testMaxFlowWithFile("testdata/testList-advanced.txt", 12, 26);
	
	testMaxFlowWithFile("testdata/testList-001.txt", 5, 24);
	testMaxFlowWithFile("testdata/testList-002.txt", 5, 999);
	testMaxFlowWithFile("testdata/testList-003.txt", 00, 999);
	testMaxFlowWithFile("testdata/testList-004.txt", 00, 999);
	testMaxFlowWithFile("testdata/testList-005.txt", 00, 999);

	testMaxFlowWithFile("testdata/v0256e1024.txt", 256, 999); 
	testMaxFlowWithFile("testdata/v0256e2048.txt", 256, 999); 
	testMaxFlowWithFile("testdata/v0512e2048.txt", 512, 999); 
	testMaxFlowWithFile("testdata/v0512e4096.txt", 512, 999); 
	testMaxFlowWithFile("testdata/v1024e4096.txt", 1024, 999); 
	testMaxFlowWithFile("testdata/v1024e8192.txt", 1024, 999); 
	testMaxFlowWithFile("testdata/v2048e8192.txt", 2048, 999); 
	testMaxFlowWithFile("testdata/v2048e9999.txt", 2048, 999); 

	printf("  ~~~~ testMaxFlow complete. \n");
}

int main(int argc, char const *argv[]) {
	testMaxFlow();
	printf("~~~~~~ testFordFulkerson complete. \n");
	return 0;
}