/**
 * Image Segementation
 * Christopher Stoll, 2014
 */

#ifndef INCLUDE_IMAGESEGMENTATION
#define INCLUDE_IMAGESEGMENTATION

#include <stdlib.h>
#include <stdio.h>
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
void readPgmLine(char *line, int currentY, int xWidth, int **matrix) {
	int nextDigit = 0, currentNumber = 0, currentX = 0;
	int didProcessNumber = 0;
	int loopCount = 0;
	while ((line[loopCount]) && (currentX < xWidth)) {
		if (isspace(line[loopCount]) || line[loopCount] == '\n') {
			if (didProcessNumber) {
				matrix[currentX][currentY] = currentNumber;

				didProcessNumber = 0;
				currentNumber = 0;
				++currentX;
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

void buildImageEdges(struct graph * thisGraph, int pgmX, int pgmY, int pgmZ, int ** imageMatrix) {
	//...
}

/**
 * Process a PGM file
 */
struct graph *readPgmFile(char *fileName) {
	FILE *pFile;
	char line[MAX_LINE_SIZE];
	int validPgmFile = 0, pgmX = 0, pgmY = 0, pgmZ = 0;
	int currentY = 0;
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
						printf("Extents: %d,%d \n", pgmX, pgmY);

					// get the greyscale depth
					} else if (pgmZ == 0) {
						readOneInt(line, &pgmZ);
						printf("Depth: %d \n", pgmZ);

					// process image line
					} else {
						readPgmLine(line, currentY, pgmX, imageMatrix);
						++currentY;
					}

				// look for PGM file marker
				} else {
					if ((line[0] == 'P') && (line[1] == '2')) {
						validPgmFile = 1;
						thisGraph = createGraph(1);
						printf("\n");
					}
				}
			}
		}
		if (validPgmFile) buildImageEdges(thisGraph, pgmX, pgmY, pgmZ, imageMatrix);
	}

	fclose(pFile);

	return thisGraph;
}

void imageSegmentation(struct graph * thisGraph, char * cutFileName) {
	//...
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