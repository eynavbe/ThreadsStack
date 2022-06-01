// C program for linked list implementation of stack
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "mallocCalloc.cpp"
#include <cstring>

#define TXT 1024;

//the node struct
struct StackNode {
	char * data;
	struct StackNode* next;
};

//create new node. The data is the data we received and "next" is set to be NULL
struct StackNode* newNode(char * data)
{
	struct StackNode* stackNode =
	(struct StackNode*)
	mymalloc(sizeof(struct StackNode));
	
	stackNode->data = data;
	stackNode->next = NULL;
	return stackNode;
}

//Checks if the stack is empty
int isEmpty(struct StackNode* root)
{
	return !root;
}

//push value into the stack.
void push(struct StackNode** root, char * data)
{
	//create the node
	struct StackNode* stackNode = newNode(data);
	//set the next of the node to be the node that enters the list/stack before it
	stackNode->next = *root;
	//The address of the root is the address of the node we have just added - "StackNode"
	*root = stackNode;
	printf("%s pushed to stack\n", data);
}

//pop text from the stack
char * pop(struct StackNode** root)
{
	//If there is nothing in the stack it will return an empty string and pop nothing
	if (isEmpty(*root))
		return (char*)"";
	//Takes out the first node and the node after it is updated to be the root
	struct StackNode* temp = *root;
	*root = (*root)->next;
	char * popped = temp->data;
	//free the memory devoted to the nome we took out
	free(temp);

	return popped;
}

//display (output) the stack top.
char * peek(struct StackNode* root)
{
	//If there is nothing in the stack it will return an empty string
	if (isEmpty(root))
		return (char*)"";
	//return the data of the first node
	return root->data;
}