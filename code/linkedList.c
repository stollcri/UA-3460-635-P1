/**
 * Linked List Data Structure
 * Christopher Stoll, 2014
 */

#ifndef INCLUDE_LINKEDLIST
#define INCLUDE_LINKEDLIST

#include <stdlib.h>
#include "node.c"

/**
 * Simple list structure
 */
struct list {
	struct node *head;
};

/**
 * List creation function
 */
struct list *newList() {
	struct list *thisList = (struct list*) malloc(sizeof(struct list));

	thisList->head = NULL;

	return thisList;
}

#endif
