#include <stdio.h>
#include "breadthFirstSearch.c"

void testBFS() {
	struct graph *testGraph = createGraph(12);
	
	int testList[12][2];
	testList[0][0] = 0;
	testList[0][1] = 1;
	testList[1][0] = 1;
	testList[1][1] = 2;
	testList[2][0] = 1;
	testList[2][1] = 3;
	testList[3][0] = 1;
	testList[3][1] = 4;
	testList[4][0] = 2;
	testList[4][1] = 5;
	testList[5][0] = 2;
	testList[5][1] = 6;
	testList[6][0] = 4;
	testList[6][1] = 7;
	testList[7][0] = 4;
	testList[7][1] = 8;
	testList[8][0] = 5;
	testList[8][1] = 9;
	testList[9][0] = 5;
	testList[9][1] = 10;
	testList[10][0] = 7;
	testList[10][1] = 11;
	testList[11][0] = 7;
	testList[11][1] = 12;
	addEdges(testGraph, 12, testList);

	printf("  ~~~~ testBFS complete. \n");
}

int main(int argc, char const *argv[]) {
	testBFS();
	printf("~~~~~~ testBreadthFirstSearch complete. \n");
	return 0;
}