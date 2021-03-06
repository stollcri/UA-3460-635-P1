/**
 * Doubly linked tree structure
 * Used to build a search tree for BFS
 * Michael Crouse, 1/26/14
 */
#ifndef INCLUDE_DTREE
#define INCLUDE_DTREE
 
#include "node.c"

struct dtree {
	struct node * data;
	//a linked list of children
	struct dtree *children;
	//the next sibling to this node
	struct dtree *next;
	//link back to the parent
	struct dtree *parent;
};

struct dtree * newTree(struct dtree * ancestor) {
	struct dtree * result = (struct dtree *) malloc(sizeof(struct dtree));
	result->data = NULL;
	result->parent = ancestor;
	result->children = NULL;
	result->next = NULL;
	return result;
}

void treeFree(struct dtree * thisBranch) {
	if (thisBranch == NULL) return;
	//start with all siblings, if any
	treeFree(thisBranch->next);
	//then onto children
	treeFree(thisBranch->children);
	//we won't be killing the data because these nodes belong to the graph structure
	free(thisBranch);
}
#endif