/**
 * Ford-Fulkerson Algorithm
 * Christopher Stoll, 2014
 */

#include "breadthFirstSearch.c"

#include <stdio.h>

int maxFlow(struct graph *thisGraph, int source, int sink) {
	int flow = 0;
	
	// initial bfs graph traversal
	struct list *path = bfs(thisGraph, source, sink);
	// while there are still paths
	while (path != NULL) {
		// determine residual
		//?????()

		// flow = min(residuals)
		//??????()
		/*
		// for each edge in the path
		for (int i = 0; i < pathLength; ++i){
			if(positiveFLow) {
				positiveFlow += flow;
			} else {
				negativeFlow -= flow;
			}
		}
		*/
		// find path in residual
		path = bfs(thisGraph, source, sink);
	}
	
	return flow;
}
