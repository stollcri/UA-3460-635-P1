default: ford

all: clean test analysis ff

ford:
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

emperical:
	cc -o analysis/analysisBreadthFirstSearch analysis/analysisBreadthFirstSearch.c
	cc -o analysis/analysisFordFulkerson analysis/analysisFordFulkerson.c

	./analysis/analysisBreadthFirstSearch
	./analysis/analysisFordFulkerson

clean:
	-rm unittests/testDataStructures
	-rm unittests/testGraph
	-rm unittests/testBreadthFirstSearch
	-rm unittests/testFordFulkerson

	-rm analysis/analysisFordFulkerson

	-rm imageSegmentation
	-rm ff
