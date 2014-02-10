/**
 * Image Segementation
 * Christopher Stoll, 2014
 */

#ifndef INCLUDE_IMAGESEGMENTATION
#define INCLUDE_IMAGESEGMENTATION

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graph.c"
#include "isQueue.c"

#define DBGIS 0
#define MAX_LINE_SIZE 1024

/**
 * Get a single int from the begining of a string of characters
 */
void readOneInt(char *line, int *x) {
	int tmpX = 0;
	int nextDigit = 0, currentNumber = 0;

	int loopCount = 0;
	while (line[loopCount]) {
		if (isspace(line[loopCount]) || line[loopCount] == '\n') {
			if (tmpX == 0) {
				tmpX = currentNumber;
				*x = tmpX;
			}
		} else {
			nextDigit = line[loopCount] - '0';
			currentNumber *= 10;
			currentNumber += nextDigit;
		}
		++loopCount;
	}
}

/**
 * Get two space sepperated ints from the begining of a string of characters
 */
void readTwoInts(char *line, int *x, int *y) {
	int tmpX = 0, tmpY = 0;
	int nextDigit = 0, currentNumber = 0;

	int loopCount = 0;
	while (line[loopCount]) {
		if (isspace(line[loopCount]) || line[loopCount] == '\n') {
			if (tmpX == 0) {
				tmpX = currentNumber;
				*x = tmpX;

			} else if (tmpY == 0) {
				tmpY = currentNumber;
				*y = tmpY;
			}

			currentNumber = 0;
		} else {
			nextDigit = line[loopCount] - '0';
			currentNumber *= 10;
			currentNumber += nextDigit;
		}
		++loopCount;
	}
}

/**
 * Create a two dimensional array of integers
 */
int** make2dIntArray(int arraySizeX, int arraySizeY) {  
	int** theArray;
	int i;
	theArray = (int**) malloc(arraySizeX*sizeof(int*));
	for (i = 0; i < arraySizeX; i++) {
		theArray[i] = (int*) malloc(arraySizeY*sizeof(int));
	}
	return theArray;
} 

/**
 * Read in a line from a PGM file
 */
void readPgmLine(char *line, int *currentY, int *currentX, int xWidth, int **matrix) {
	int nextDigit = 0, currentNumber = 0;
	int didProcessNumber = 0;
	int loopCount = 0;
	while ((line[loopCount])) {
		if (isspace(line[loopCount]) || line[loopCount] == '\n') {
			if (didProcessNumber) {
				matrix[(*currentX)][(*currentY)] = currentNumber;
				didProcessNumber = 0;
				currentNumber = 0;
				++(*currentX);
				if ((*currentX) == xWidth) {
					(*currentX)=0;
					(*currentY)++;
				}
			}
		} else {
			nextDigit = line[loopCount] - '0';
			currentNumber *= 10;
			currentNumber += nextDigit;
			didProcessNumber = 1;
		}
		++loopCount;
	}
}

//Builds an edge weight between two adjacent pixels
//TODO: figure out a heuristic for building edge weights properly.
//This one just figures the background is easier to flow through
int costCheck(int pgmZ, int source, int dest) {
	int result = 0;
	if (source > dest) {
		result = (source-dest);
	} else {
		result = (dest-source);
	}
	return result;
}

struct graph * buildImageEdges(int pgmX, int pgmY, int pgmZ, int ** matrix) {
	int x, y, cost;
	int minPixel = pgmZ / 2, maxPixel = pgmZ / 2;
	int minSpot = 0, maxSpot = 0;

	//2 extra pixels needed for source and sink
	struct graph * thisGraph = createGraph(pgmX*pgmY + 2);
	for (y = 0; y<pgmY; y++) {
		//add a link from the source pixel to the first pixel in this line
		for (x =0; x < pgmX; x++) {
			// find the minimum pixel value closest to the begining
			if (matrix[x][y] <= minPixel) {
				minSpot = pgmX * y + x;
				addEdgeWithCost(thisGraph, thisGraph->verticesCount-2, minSpot, INT_MAX, pgmZ);
			}

			// find the maximum pixel value clostest to the end
			if (matrix[x][y] >= maxPixel) {
				maxSpot = pgmX * y + x;
				addEdgeWithCost(thisGraph, maxSpot, thisGraph->verticesCount-1, INT_MAX, pgmZ);
			}
			thisGraph->adjacencyList[y*pgmX +x].self->zValue = matrix[x][y];
			//since the adjacency list is one dimensional and row-ordered, y*pgmX + x
			//will give us the correct node
			//we'll start with the pixel to the left of this one
			if (x > 0) {
				cost = costCheck(pgmZ, matrix[x][y], matrix[x-1][y]);
				addEdgeWithCost(thisGraph, (y*pgmX + x), (y*pgmX +x -1), cost, matrix[x][y]);
			}
			//onto the pixel to the right of this one
			if (x < pgmX-1) {
				cost = costCheck(pgmZ, matrix[x][y], matrix[x+1][y]);
				addEdgeWithCost(thisGraph, (y*pgmX + x), (y*pgmX +x +1), cost, matrix[x][y]);
			}
			//now the pixel below this one
			if (y < pgmY-1) {
				cost = costCheck(pgmZ, matrix[x][y], matrix[x][y+1]);
				addEdgeWithCost(thisGraph, (y*pgmX + x), ((y+1)*pgmX +x), cost, matrix[x][y]);
			}
			//finally the pixel above this one
			if (y > 0) {
				cost = costCheck(pgmZ, matrix[x][y], matrix[x][y-1]);
				addEdgeWithCost(thisGraph, (y*pgmX + x), ((y-1)*pgmX +x), cost, matrix[x][y]);
			}
		}
	}

	return thisGraph;
}

/**
 * Process a PGM file
 */
struct graph *readPgmFile(char *fileName) {
	FILE *pFile;
	char line[MAX_LINE_SIZE];
	int validPgmFile = 0, pgmX = 0, pgmY = 0, pgmZ = 0;
	int currentY = 0, currentX=0;
	int** imageMatrix;
	struct graph *thisGraph = NULL;
	pFile = fopen(fileName, "r");
	if (pFile != NULL) {
		while (fgets(line, MAX_LINE_SIZE, pFile) != NULL) {
			if (line[0] != '#'){
				// found the PGM file marker
				if(validPgmFile) {
					// get the graph coordinates
					if ((pgmX == 0) && (pgmY == 0)) {
						readTwoInts(line, &pgmX, &pgmY);
						imageMatrix = make2dIntArray(pgmX, pgmY); 

					// get the greyscale depth
					} else if (pgmZ == 0) {
						readOneInt(line, &pgmZ);

					// process image line
					} else {
						readPgmLine(line, &currentY, &currentX, pgmX, imageMatrix);
					}

				// look for PGM file marker
				} else {
					if ((line[0] == 'P') && (line[1] == '2')) {
						validPgmFile = 1;
					}
				}
			}
		}
		if (validPgmFile) {
			thisGraph = buildImageEdges(pgmX, pgmY, pgmZ, imageMatrix);
			thisGraph->extentX = pgmX;
			thisGraph->extentY = pgmY;
			thisGraph->extentZ = pgmZ;
		}
	}
	fclose(pFile);
	return thisGraph;
}

/*
 * Take an image matrix generated by imageSegmentation and output  
 */
void outputImage(int **matrix, char *cutFileName, int pgmX, int pgmY, int pgmZ) {
	FILE * out = fopen(cutFileName, "w");
	int x, y, n;
	if (out == NULL) {
		printf("Cannot open %s for writing!\n", cutFileName);
	}
	else {
		fprintf(out, "P2\n");
		fprintf(out, "# Created by Crouse and Stoll\n");
		fprintf(out, "%d %d\n", pgmX, pgmY);
		fprintf(out, "%d\n", pgmZ);
		for (y=0; y < pgmY; ++y) {
			for (x=0; x < pgmX; ++x) {
				fprintf(out, "%d ", matrix[x][y]);
			}
			fprintf(out, "\n");
		}
		fclose(out);
	}
}

/**
 * TODO: Split this into smaller pieces
 *
 * Perform DEPTH Firts search from the source, stop when a zero capacity residual node is found
 * (this is the min-cut boundary). Every reachable node should be marked (black), and every
 * unreachable node should remain un-marked (white).
 */
void imageSegmentation(struct graph *thisGraph, char *cutFileName, int source) {
	int pgmX = thisGraph->extentX;
	int pgmY = thisGraph->extentY;
	int pgmZ = thisGraph->extentZ;
	int x, y;
	int currentX = 0;
	int currentY = 0;
	struct node *currentNode = thisGraph->adjacencyList[source].head;
	struct node *nextNode = NULL;
	struct isQueue * visitQueue = newISQueue();
	
	int **newImageMatrix;
	int *seen = (int *) malloc(sizeof(int) * thisGraph->verticesCount);
	for (x=0; x < thisGraph->verticesCount; ++x) {
		seen[x] = 0;
	}
	
	// turn all pixels off
	newImageMatrix = make2dIntArray(pgmX, pgmY);
	for (y = 0; y < pgmY; ++y){
		for (x = 0; x < pgmX; ++x){
			//newImageMatrix[x][y] = thisGraph->adjacencyList[y*pgmX +x].self->zValue;
			newImageMatrix[x][y] = pgmZ;
		}
	}

	nextNode = currentNode;
	while (nextNode != NULL) {
		isEnqueue(visitQueue, nextNode);
		seen[nextNode->vertex] = 1;
		if(DBGIS) printf("Enqueueing vertex %d\n", nextNode->vertex);

		nextNode = nextNode->next;
	}

	while ((currentNode = isDequeue(visitQueue)) != NULL) {
		currentX = currentNode->vertex % pgmX;
		currentY = currentNode->vertex / pgmX;
		//is this a node that had capacity and now has none?
		if (currentNode->capacity == 0) {
			//if(DBGIS) printf("No remaining capacity at this node\n");
		} else {
			//we are at a previously univisited node that isn't cut off here.
			//we'll enqueue all nearby nodes and work on them next
			nextNode = thisGraph->adjacencyList[currentNode->vertex].head;
			newImageMatrix[currentX][currentY] = nextNode->zValue;
			while ((nextNode != NULL) && (nextNode->capacity != 0)) {
				//is the node we're going to look at alrady visited?
				if (seen[nextNode->vertex] == 0) {
					isEnqueue(visitQueue, nextNode);
					seen[nextNode->vertex] = 1;
				}
				nextNode = nextNode->next;
			}
		}
	}
	outputImage(newImageMatrix, cutFileName, pgmX, pgmY, pgmZ);
}

#endif
