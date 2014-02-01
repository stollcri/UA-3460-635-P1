/**
 * Linked List Data Structure
 * Christopher Stoll, 2014
 * Edited Michael Crouse 2/1/14
 */

#ifndef INCLUDE_LINKEDLIST
#define INCLUDE_LINKEDLIST

#include <stdlib.h>
#include "node.c"

/**
 * Simple list structure
 */
struct list {
	struct node *self;
	struct node *head;
};

/**
 * List creation function
 */
struct list *newList() {
	struct list *thisList = (struct list*) malloc(sizeof(struct list));
	thisList->head = NULL;
	thisList->self = NULL;
	return thisList;
}

#endif
