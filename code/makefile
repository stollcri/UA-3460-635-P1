all: 
	cc -o testAdjacencyList testAdjacencyList.c

test:
	cc -o testDataStructures testDataStructures.c
	cc -o testAdjacencyList testAdjacencyList.c
	cc -o testBreadthFirstSearch testBreadthFirstSearch.c

	./testAdjacencyList
	./testDataStructures
	./testBreadthFirstSearch

clean:
	-rm testDataStructures
	-rm testAdjacencyList
	-rm testBreadthFirstSearch
