default: 
	cc -o testFordFulkerson testFordFulkerson.c

all: clean test

test:
	cc -o testDataStructures testDataStructures.c
	cc -o testGraph testGraph.c
	cc -o testBreadthFirstSearch testBreadthFirstSearch.c
	cc -o testFordFulkerson testFordFulkerson.c

	./testDataStructures
	./testGraph
	./testBreadthFirstSearch
	./testFordFulkerson

analysis:
	cc -o analysisFordFulkerson analysisFordFulkerson.c

clean:
	-rm testDataStructures
	-rm testGraph
	-rm testBreadthFirstSearch
	-rm testFordFulkerson
	-rm generateGraph
