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
	if (source > dest) return source-dest;
	return dest-source;
}

struct graph * buildImageEdges(int pgmX, int pgmY, int pgmZ, int ** matrix) {
	int x, y, cost;
	int minPixel = INT_MAX, maxPixel = 0;
	int minSpot = 0, maxSpot = 0;

	//2 extra pixels needed for source and sink
	struct graph * thisGraph = createGraph(pgmX*pgmY + 2);
	for (y = 0; y<pgmY; y++) {
		//add a link from the source pixel to the first pixel in this line
		//addEdgeWithCost(thisGraph, thisGraph->verticesCount -2, y*pgmX, INT_MAX);
		for (x =0; x < pgmX; x++) {

			// find the minimum pixel value closest to the begining
			if (matrix[x][y] < minPixel) {
				minPixel = matrix[x][y];
				minSpot = x * y;
			}

			// find the maximum pixel value clostest to the end
			if (matrix[x][y] >= maxPixel) {
				maxPixel = matrix[x][y];
				maxSpot = x * y;
			}

			//since the adjacency list is one dimensional and row-ordered, y*pgmX + x
			//will give us the correct node
			//we'll start with the pixel to the left of this one
			if (x > 0) {
				cost = costCheck(pgmZ, matrix[x][y], matrix[x-1][y]);
				addEdgeWithCost(thisGraph, (y*pgmX + x), (y*pgmX +x -1), cost);
			}
			//onto the pixel to the right of this one
			if (x < pgmX-1) {
				cost = costCheck(pgmZ, matrix[x][y], matrix[x+1][y]);
				addEdgeWithCost(thisGraph, (y*pgmX + x), (y*pgmX +x +1), cost);
			}
			//now the pixel below this one
			if (y < pgmY-1) {
				cost = costCheck(pgmZ, matrix[x][y], matrix[x][y+1]);
				addEdgeWithCost(thisGraph, (y*pgmX + x), ((y+1)*pgmX +x), cost);
			}
			//finally the pixel above this one
			if (y > 0) {
				cost = costCheck(pgmZ, matrix[x][y], matrix[x][y-1]);
				addEdgeWithCost(thisGraph, (y*pgmX + x), ((y-1)*pgmX +x), cost);
			}
		}
		//add a link from the end pixel of the line to the sink
		//addEdgeWithCost(thisGraph, (y*pgmX + pgmX-1), thisGraph->verticesCount-1, INT_MAX);
	}

	// source
	addEdgeWithCost(thisGraph, thisGraph->verticesCount-2, minSpot, INT_MAX);
	// sink
	addEdgeWithCost(thisGraph, maxSpot, thisGraph->verticesCount-1, INT_MAX);

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
						//printf("Extents: %d,%d \n", pgmX, pgmY);

					// get the greyscale depth
					} else if (pgmZ == 0) {
						readOneInt(line, &pgmZ);
						//printf("Depth: %d \n", pgmZ);

					// process image line
					} else {
						readPgmLine(line, &currentY, &currentX, pgmX, imageMatrix);
					}

				// look for PGM file marker
				} else {
					if ((line[0] == 'P') && (line[1] == '2')) {
						validPgmFile = 1;
						//printf("\n");
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
void outputImage(int **matrix, char *cutFileName, int pgmX, int pgmY) {
	//...
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

	int poorMansQueue[1024];
	int poorMansQueuePointer = 0;
	int x, y;

	int currentX = 0;
	int currentY = 0;
	struct node *currentNode = thisGraph->adjacencyList[source].head;
	struct node *nextNode = thisGraph->adjacencyList[currentNode->vertex].head;
	// skip past source node
	currentNode = nextNode;
	nextNode = currentNode->next;

	int **newImageMatrix;

	// turn all pixels off
	newImageMatrix = make2dIntArray(pgmX, pgmY);
	for (y = 0; y < pgmY; ++y){
		for (x = 0; x < pgmX; ++x){
			newImageMatrix[x][y] = 0;
		}
	}

	while (currentNode) {
        printf("=> %d (%d) ", currentNode->vertex, currentNode->capacity);

        if ((currentNode->capacity > 0) && (currentNode->isVisited == 0)) {
        //if (currentNode->capacity != 0) {

        	if (currentNode->isVisited == 0) {
	        	currentNode->isVisited = 1;
	        	currentY = currentNode->vertex / pgmX;
	        	currentX = currentNode->vertex % pgmX;
	        	newImageMatrix[currentX][currentY] = pgmZ;
	        	printf("> %d (%d, %d) ", currentNode->vertex, currentX, currentY);

	        	// save the current node on the queue
	        	poorMansQueue[poorMansQueuePointer] = currentNode->vertex;
	        	++poorMansQueuePointer;
			}
        	
        	// jump to the next node

        	if (currentNode->next != NULL) {
	        	nextNode = currentNode->next;

	        	while ((nextNode != NULL) && (nextNode->isVisited == 1)) {
		        	printf("~ ");
		        	if (nextNode->next) {
		        		nextNode = nextNode->next;
		        	}
		        }

		        if (nextNode != NULL) {
		        	currentNode = thisGraph->adjacencyList[nextNode->vertex].head;
		        	printf(".%d.", currentNode->vertex);
		        }
	        }
        	
        	printf("\n");
	        
        } else {
        	// go back to the previous node
        	--poorMansQueuePointer;
		if (poorMansQueuePointer < 0) {
			currentNode=NULL;
		}else {
        	       currentNode = thisGraph->adjacencyList[poorMansQueue[poorMansQueuePointer]].head;
        	       printf("BACK \n");
		}
        }
    }
    printf("\n\n");

    /**/
	printf("P2\n");
	printf("# Created by Crouse and Stoll\n");
	printf("%d %d\n", pgmX, pgmY);
	printf("%d\n", pgmZ);
	for (y = 0; y < pgmY; ++y){
		for(x = 0; x < pgmX; ++x){
			//printf("%d ", newImageMatrix[x][y]);
			if (newImageMatrix[x][y] != 0) {
				printf("█");
				//printf("B");
			} else {
				printf("░");
				//printf("W");
			}
		}
		printf("\n");
	}
	/**/
	outputImage(newImageMatrix, cutFileName, pgmX, pgmY);
}

#endif

/*
This needs to be commented for ff.c to compile correctly MEC 2/3/14
int main(int argc, char *argv[]) {
	readPgmFile(argv[1]);
	printf("DONE \n");
	return 0;
}
*/