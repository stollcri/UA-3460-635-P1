/*  	
Program______________________________

Programmer _________________________________

Academic Integrity Pledge

- All source code and documentation used in my program is either
  my original work, or was derived, by me, from the source
  code published in the textbook for this course or presented in class.
  Any source code in this project that is derived from code published 
  elsewhere is documented as such so the original author receives due 
  credit.

- I have not used source code obtained from another student,
  or any other unauthorized source, either modified or unmodified.
  I have not helped another student write their program by providing
  a printed or electronic copy of my solution.

- I have not discussed coding details about this project with anyone
  other than my instructor. I understand that I may discuss the
  concepts of this program with other students, and that another
  student may help me debug my program. However, the responsibility
  to write each program belongs solely to the program's author.

- I have violated neither the spirit nor letter of these restrictions.


_______________________________________  Date___________________
Signature of programmer
*/

/**
 * Run Breadth First Search, Ford-Fullkerson, and Image Segmentation
 */

#include <stdio.h>
#include <string.h>
#include "breadthFirstSearch.c"
#include "fordFulkerson.c"
#include "imageSegmentation.c"

/**
 * Respond to the -b command line switch by runnning
 * breadth first search and reporting back the path found
 */
void runBFS(char *fileName, int source, int sink) {
	if ((strlen(fileName) != 0) && (source != sink)) {
		//
		// TODO: Make sure that source and sink are within the graph
		//
		struct graph *thisGraph = createGraphFromFile(fileName);
		struct list *thisPath = bfs(thisGraph, source, sink);

		struct node *currentNode = thisPath->head;
		struct node *nextNode = NULL;

		printf("Path: ");
		while (currentNode) {
	        printf("=> %d ", currentNode->vertex);
	        nextNode = currentNode->next;
	        currentNode = nextNode;
	    }
	    printf("\n");
	}
}

/**
 * Respond to the -f command line switch by runnning
 * Ford-Fulkerson and reporting back the max-flow
 */
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
		++graphStart;
		if (thisGraph->adjacencyList[graphStart].head) {
			
			thisNode = thisGraph->adjacencyList[graphStart].head;
		} else {
			graphViable = 0;
		}
	}

	// find the last graph node
	graphEnd = thisGraph->verticesCount - (graphStart + 1);

	if (thisNode) {
		maximumFlow = maxFlow(thisGraph, graphStart, graphEnd);
		printf("Max flow (from %d to %d) is %d\n", graphStart, graphEnd, maximumFlow);
	} else {
		printf("Error creating or reading graph.\n");
	}
}

/**
 * Respond to the -i command line switch by runnning
 * the image segmentation routines
 */
void runIS(char *imageFileName, char *cutFileName) {
	if ((strlen(imageFileName) != 0) && (strlen(cutFileName) != 0)) {
		int mFlow;
		//create a graph complete with source 0 and sink at verticesCount
		struct graph * thisGraph = readPgmFile(imageFileName);
		if (thisGraph == NULL) {
			printf("Error: invalid PGM file!\n");
			return;
		}
		//printResidualGraph(thisGraph);
		mFlow = maxFlow(thisGraph, thisGraph->verticesCount-2, thisGraph->verticesCount-1);
		//printf("Maximum Flow: %d\n", mFlow);
		//now we have a maximum flow, so run image segmentation to build a minimum cut
		if (mFlow != 0) imageSegmentation(thisGraph, cutFileName, thisGraph->verticesCount-2);
	}
}

/**
 * ff
 * Run breadth first search, Ford-Fulkerson, and Image Segmentation
 */
int main(int argc, char *argv[]) {
	if (argc > 2) {
		if (argv[1][1] == 'b') {
			if (argc > 4) {
				runBFS(argv[2], atoi(argv[3]), atoi(argv[4]));
			} else {
				printf("Usage (pick one):\n");
				printf(" ff –b graph.txt source_node sink_node\n");
			}

		} else if (argv[1][1] == 'f') {
			runFF(argv[2]);

		} else if (argv[1][1] == 'i') {
			if (argc > 3) {
				runIS(argv[2], argv[3]);
			} else {
				printf("Usage (pick one):\n");
				printf(" ff –i image.pgm imageWcut.pgm\n");
			}
		}
	} else {
		printf("Usage (pick one):\n");
		printf(" ff –b graph.txt source_node sink_node\n");
		printf(" ff –f graph.txt\n");
		printf(" ff –i image.pgm imageWcut.pgm\n");
	}

	return 0;
}
