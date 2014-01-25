/**
 * Adjacency List
 * Christopher Stoll, 2014
 */

/**
 * Simple node structure
 */
struct node {
	int vertex;
	struct node *next;
};

/**
 * Simple list structure
 */
struct list {
	struct node *head;
};

/**
 * Simple graph structure
 */
struct graph {
	int verticesCount;
	struct list *adjacencyList;
};

/**
 * Node creation function
 */
struct node *createNode(int vertex) {
	struct node *newNode = (struct node*) malloc(sizeof(struct node));

	newNode->vertex = vertex;
	newNode->next = NULL;

	return newNode;
}

/**
 * Graph creation function
 */
struct graph *createGraph(int verticesCount) {
	struct graph *newGraph = (struct graph*) malloc(sizeof(struct graph));
	
	newGraph->verticesCount = verticesCount;
	newGraph->adjacencyList = (struct list*) malloc(sizeof(struct list) * verticesCount);

	for (int i = 0; i < verticesCount; ++i) {
		newGraph->adjacencyList[i].head = NULL;
	}

	return newGraph;
}

/**
 * Add an edge to a graph
 */
void addEdge(struct graph *currentGraph, int source, int sink) {
	struct node *newNode = createNode(sink);

	newNode->next = currentGraph->adjacencyList[source].head;
	currentGraph->adjacencyList[source].head = newNode;
}

void addEdges(struct graph *currentGraph, int listLength, int adjacencyList[][2]) {
	for (int i = 0; i < listLength; ++i) {
		addEdge(currentGraph, adjacencyList[i][0], adjacencyList[i][1]);
	}
}
