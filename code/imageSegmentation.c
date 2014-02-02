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

struct graph *readPgmFile(char *fileName) {
	FILE *pFile;
	char line[MAX_LINE_SIZE];
	int validPgmFile = 0, pgmX = 0, pgmY = 0, pgmZ = 0;

	struct graph *thisGraph = createGraph(1);

	pFile = fopen(fileName, "r");
	if (pFile != NULL) {
		while (fgets(line, MAX_LINE_SIZE, pFile) != NULL) {
			if (line[0] != '#'){
				// found the PGM file marker
				if(validPgmFile) {
					// get the graph coordinates
					if ((pgmX == 0) && (pgmY == 0)) {
						readTwoInts(line, &pgmX, &pgmY);
						printf("Extents: %d,%d \n", pgmX, pgmY);

					// get the greyscale depth
					} else if (pgmZ == 0) {
						readOneInt(line, &pgmZ);
						printf("Depth: %d \n", pgmZ);

					// process image line
					} else {
						//
					}

				// look for PGM file marker
				} else {
					if ((line[0] == 'P') && (line[1] == '2')) {
						validPgmFile = 1;
						printf("\n");
					}
				}
			}
		}
	}
	fclose(pFile);

	return thisGraph;
}

#endif

int main(int argc, char *argv[]) {
	readPgmFile(argv[1]);
	printf("DONE \n");
	return 0;
}
