# Advanced Algorithms Project
- Christopher Stoll
- Michael Crouse

## Unit tests
To run the unit tests, which realy just ensures that changes did not cause other portions of the code to seg fault or no longer compile, use the following command (assuming a Unix/Linux development machine):

	$ make test

## Compiling
Assuming you are a Unix type machine you can use the following commands. If you are on a windows machine then look at the make file for compilation examples (it should be pretty easy: `cc filename.c filename` or `cc filename.c filename.exe`)

	# compile the main program
	$ cd code
	$ make

	# to make development easier, you may like:
	$ make clean && make && ff

	# compiling the analyis program
	$ make analysis

## Running the Program
### Running Breadth First Search

	ff –b graph.txt source sink

### Running Ford-Fulkerson for Max Flow / Min Cut

	ff –f graph.txt

### Running an Image Segemntation Problem

	ff –i image.pgm imageWcut.pgm

