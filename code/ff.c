/**
 * Run Breadth First Search, Ford-Fullkerson, and Image Segmentation
 */

#include <stdio.h>
#include <string.h>
//#include "breadthFirstSearch.c" <= TODO: no include guards
#include "fordFulkerson.c"
#include "imageSegmentation.c"

void runBFS(char *fileName, int source, int sink) {
	if ((strlen(fileName) != 0) && (source != sink)) {
		struct graph *thisGraph = createGraphFromFile(fileName);
		bfs(thisGraph, source, sink);

		// TODO: do something else here?
		printf("BFS Complete\n");
	}
}

void runFF(char *fileName) {
	if (strlen(fileName) == 0) {
		return;
	}

	int graphStart = 0;
	int graphEnd = 0;
	int graphViable = 1;
	int maximumFlow = 0;

	struct graph *thisGraph = createGraphFromFile(fileName);
	struct node *thisNode;
	
	// find the first graph node
	thisNode = thisGraph->adjacencyList[graphStart].head;
	while ((thisNode == NULL) && graphViable) {
		if (thisGraph->adjacencyList[graphStart].head) {
			++graphStart;
			thisNode = thisGraph->adjacencyList[graphStart].head;
		} else {
			graphViable = 0;
		}
	}

	// find the last graph node
	graphEnd = thisGraph->verticesCount - 1;
	/*
	graphEnd = thisGraph->verticesCount;
	thisNode = thisGraph->adjacencyList[graphEnd].head;
	while ((thisNode == NULL) && graphViable) {
		if (thisGraph->adjacencyList[graphStart].head) {
			--graphEnd;
			thisNode = thisGraph->adjacencyList[graphEnd].head;
		} else {
			graphViable = 0;
		}
	}
	*/

	if (thisNode) {
		maximumFlow = maxFlow(thisGraph, graphStart, graphEnd);
		printf("Max flow (from %d to %d) is %d\n", graphStart, graphEnd, maximumFlow);
	} else {
		printf("Error\n");
	}
}

void runIS(char *imageFileName, char *cutFileName) {
	if ((strlen(imageFileName) != 0) && (strlen(cutFileName) != 0)) {
		int mFlow;
		//create a graph complete with source 0 and sink at verticesCount
		struct graph * thisGraph = readPgmFile(imageFileName);
		if (thisGraph == NULL) {
			printf("Error: invalid PGM file!\n");
			return;
		}
		printf("Completed graph, running max flow\n");
		printf("%d\n", thisGraph->verticesCount);
		mFlow = maxFlow(thisGraph, thisGraph->verticesCount-2, thisGraph->verticesCount-1);
		printf("Maximum Flow: %d\n", mFlow);
		//now we have a maximum flow, so run image segmentation to build a minimum cut
		if (mFlow != 0) imageSegmentation(thisGraph, cutFileName);
	}
}

int main(int argc, char *argv[]) {
	if (argc > 2) {
		if (argv[1][0] == 'b') {
			if (argc > 4) {
				runBFS(argv[2], atoi(argv[3]), atoi(argv[4]));
			}

		} else if (argv[1][0] == 'f') {
			runFF(argv[2]);

		} else if (argv[1][0] == 'i') {
			runIS(argv[2], argv[3]);
		}
	}

	return 0;
}
