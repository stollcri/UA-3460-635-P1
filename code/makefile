default: ff

all: clean test analysis ff

ff:
	cc -o ff ff.c

test:
	cc -o unittests/testDataStructures unittests/testDataStructures.c
	cc -o unittests/testGraph unittests/testGraph.c
	cc -o unittests/testBreadthFirstSearch unittests/testBreadthFirstSearch.c
	cc -o unittests/testFordFulkerson unittests/testFordFulkerson.c

	./unittests/testDataStructures
	./unittests/testGraph
	./unittests/testBreadthFirstSearch
	./unittests/testFordFulkerson

analysis:
	cc -o analysis/analysisFordFulkerson analysis/analysisFordFulkerson.c

clean:
	-rm unittests/testDataStructures
	-rm unittests/testGraph
	-rm unittests/testBreadthFirstSearch
	-rm unittests/testFordFulkerson
	-rm analysis/analysisFordFulkerson
	-rm ff
