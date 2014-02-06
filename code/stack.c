/* stack.c
 * A stack built for the node class
 * Michael Crouse
 * 1/29/14
 */
#ifndef STACK_C
#define STACK_C
 #include "node.c"
 
// TODO: Add function documentation

 struct stack {
	 struct stackItem * head;
 };
 
 struct stackItem {
	 struct node * data;
	 struct stackItem * next;
 };
 
 struct stack * newStack() {
	 struct stack * result = (struct stack *) malloc(sizeof(struct stack));
	 result->head = NULL;
	 return result;
 }
 
 void push(struct stack * thisStack, struct node * newItem) {
	 struct stackItem * result = (struct stackItem *) malloc(sizeof(struct stackItem));
	 result->next = thisStack->head;
	 result->data = newItem;
	 thisStack->head = result;
 }
 
 struct node * pop (struct stack * thisStack) {
	 if (thisStack == NULL || thisStack->head == NULL) return NULL;
	 struct node * result = thisStack->head->data;
	 struct stackItem* temp = thisStack->head;
	 thisStack->head = thisStack->head->next;
	 free(temp);
	 return result;
 }
 #endif