/**
 * Ford-Fulkerson Algorithm
 * Christopher Stoll, 2014
 */

#include "breadthFirstSearch.c"
#include <limits.h>

#include <stdio.h>

#define DBGFF 1

/**
 * Calculate the maximum flow along a path
 */
int pathFlow(struct list *thisPath) {
	struct node *currentNode = thisPath->head;
	struct node *nextNode = NULL;
    int flow = INT_MAX;

    while (currentNode) {
        if (currentNode->capacity < flow) {
        	flow = currentNode->capacity;
        }
        nextNode = currentNode->next;
        currentNode = nextNode;
    }
    return flow;
}

/**
 * Determine residual graph
 */
void residual(struct graph *thisGraph, struct list *thisPath, int flow) {
    struct node *currentPathNode = thisPath->head;
    struct node *nextPathNode = currentPathNode->next;
    struct node *currentNode = thisGraph->adjacencyList[currentPathNode->vertex].head;
    struct node *nextNode = NULL;
    
    // for each node in the path
    while (currentNode) {
    	// find the sink node in the graph
    	if (currentNode->vertex == nextPathNode->vertex) {
    		//
    		// TODO: Fix the math here, 
    		//
    		currentNode->flow = flow;
    		currentNode->capacity = currentNode->capacity - flow;
        	if(DBGFF) printf("%d -> %d (x - %d = %d) \n", currentPathNode->vertex, currentNode->vertex, currentNode->flow, currentNode->capacity);

        	// advance to the next item in the path
            currentPathNode = nextPathNode;
    		nextPathNode = currentPathNode->next;
    		currentNode = thisGraph->adjacencyList[currentPathNode->vertex].head;
    	
    	// advance to the next item in the linked list
    	} else {
    		if (currentNode->next) {
	    		nextNode = currentNode->next;
	    		currentNode = nextNode;
	    	}
    	}
    }
}

/**
 * Use Ford-Folkerson to calulate max-flow / min-cut
 */
int maxFlow(struct graph *thisGraph, int source, int sink) {
	int flow = 0;
	
	// initial bfs graph traversal
	struct list *path = bfs(thisGraph, source, sink);
	// while there are still paths
	while (path != NULL) {
		// determine max flow for this path
		flow = pathFlow(path);
		if(DBGFF) printf("FLOW: %d \n", flow);

		// determine the residual graph
		residual(thisGraph, path, flow);

		// find path in residual
		path = bfs(thisGraph, source, sink);
	}
	
	return flow;
}
