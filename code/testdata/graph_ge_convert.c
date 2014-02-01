/**
 * Graph Data Structure
 * Christopher Stoll, 2014
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>

#define MAX_LINE_SIZE 256

int processLine(char *line, int currentVertex) {
	int vertexA = INT_MAX; // column 1
	int vertexB = INT_MAX; // column 2
	int cost = INT_MAX; // column 3

	int returnValue = 0;

	int hasSeenCharacter = 0;
	int nextDigit = 0;
	int currentNumber = 0;

	int loopCount = 0;
	while (line[loopCount]) {
		// space delimited values
		if (isspace(line[loopCount]) || line[loopCount] == '\n') {
			// ignore leading blanks
			if (hasSeenCharacter) {
				// we haven't processed column 1
				if (vertexA == INT_MAX) {
					vertexA = currentNumber;

				// we haven't processed column 2
				} else if (vertexB == INT_MAX) {
					vertexB = currentNumber;

				// we haven't processed column 3
				} else if (cost == INT_MAX) {
					cost = currentNumber;
					
					if (vertexA == currentVertex) {
						printf(" %d %d", vertexB, cost);
					} else {
						printf("\n%d %d", vertexB, cost);
					}

					returnValue = vertexA;
					vertexA = INT_MAX;
					vertexB = INT_MAX;
					cost = INT_MAX;
				}
				hasSeenCharacter = 0;
			}

			currentNumber = 0;
		} else {
			hasSeenCharacter = 1;

			nextDigit = line[loopCount] - '0';
			currentNumber *= 10;
			currentNumber += nextDigit;
		}
		++loopCount;
	}
	return returnValue;
}

void processGeneratedGraph(const char *fileName) {
	FILE *pFile;
	char line[MAX_LINE_SIZE];
	int currentVertex = 0;
	int nextVertex = 0;

	pFile = fopen(fileName, "r");
	if (pFile != NULL) {
		while (fgets(line, MAX_LINE_SIZE, pFile) != NULL) {
			if (line[0] != '#'){
				nextVertex = processLine(line, currentVertex);
				currentVertex = nextVertex;
			}
		}
	}
	fclose(pFile);
}

int main(int argc, char const *argv[]) {
	if (argc > 1) {
		processGeneratedGraph(argv[1]);
	}
	return 0;
}