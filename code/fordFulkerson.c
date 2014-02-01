/**
 * Ford-Fulkerson Algorithm
 * Christopher Stoll, 2014
 * Laste edited by Michael Crouse 2/1/2014
 */

#include "breadthFirstSearch.c"
#include <limits.h>

#include <stdio.h>

#define DBGFF 0

/**
 * Calculate the maximum flow along a path
 */
int pathFlow(struct list *thisPath, int sink) {
	//go to the first node after the s, path starts at s and has no cost/capacity
	struct node *currentNode = thisPath->head->next;
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
    while (currentNode && (nextPathNode != NULL)) {
    	// find the sink node in the graph
    	if (currentNode->vertex == nextPathNode->vertex) {
    		//
    		// TODO: Fix the math here, 
    		//
    		currentNode->flow = flow;
    		currentNode->capacity = currentNode->capacity - flow;
        	if(DBGFF) printf("%d -> %d (x - %d = %d) \n", currentPathNode->vertex, currentNode->vertex, currentNode->flow, currentNode->capacity);

        	// advance to the next item in the path
            if (nextPathNode->next) {
	            currentPathNode = nextPathNode;
	    		nextPathNode = currentPathNode->next;
	    		currentNode = thisGraph->adjacencyList[currentPathNode->vertex].head;
	    	} else {
	    		currentNode = NULL;
	    	}
    	
    	// advance to the next item in the linked list
    	} else {
    		if (currentNode->next) {
	    		nextNode = currentNode->next;
	    		currentNode = nextNode;
	    	}
    	}
    }
}

void printResidualGraph(struct graph* currentGraph) {
    int v;
    for (v = 0; v < currentGraph->verticesCount; ++v) {
        struct node *currentNode = currentGraph->adjacencyList[v].head;
        
        printf("Adjacency list of vertex %d\n head", v);
        while (currentNode) {
            printf(" -> %d (%d)", currentNode->vertex, currentNode->capacity);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}

/**
 * Use Ford-Folkerson to calulate max-flow / min-cut
 */
int maxFlow(struct graph *thisGraph, int source, int sink) {
	int flow = 0;
	int maximumFlow = 0;
	
	if(DBGFF) printf(" BFS 0 ... ");
	// initial bfs graph traversal
	struct list *path = bfs(thisGraph, source, sink);
	if(DBGFF) printf("DONE \n");

	// while there are still paths
	while (path != NULL) {
		// determine max flow for this path
		flow = pathFlow(path, sink);
		maximumFlow += flow;
		if(DBGFF) printf("FLOW: %d / MAXFLOW: %d \n", flow, maximumFlow);

		// determine the residual graph
		residual(thisGraph, path, flow);
		if(DBGFF) printResidualGraph(thisGraph);
		
		if(DBGFF) printf(" BFS n ... ");
		// find path in residual
		path = bfs(thisGraph, source, sink);
		if(DBGFF) printf("DONE \n");
	}
	
	return maximumFlow;
}
