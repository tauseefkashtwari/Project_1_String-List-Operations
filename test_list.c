// Sample test routine for the list module.
#include <stdio.h>
#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//GIVEN TO US BY PROF
/*
 * Main()
 */
int main(int argc, char** argv)
{
	printf("Starting tests...\n");
	struct nodeStruct *head = NULL;

	// Starting count:
	assert(numberofnodes(head) == 0);

	// Create 1 node:
	struct nodeStruct* firstNode = List_createNode(0);
	List_insertHead(&head, firstNode);
	
	printf("Let's Print the List: ");
	List_print(&head); //added print 
	
	assert(numberofnodes(head) == 1); //count should be 1 
	assert(List_findNode(head, 0) == firstNode); //firstnode should be 0
	assert(List_findNode(head, 1) == NULL); //2nd node should be empty

	
	// Insert tail:
	struct nodeStruct* lastNode = List_createNode(-5);

	List_insertTail(&head, lastNode);
	printf("Let's Print last node List_insertTail: ");
	List_print(&head); //added print 
	


	assert(numberofnodes(head) == 2); //head and tail
	assert(List_findNode(head, 0) == firstNode);
	assert(List_findNode(head, -5) == lastNode);
	assert(List_findNode(head, 1) == NULL); //not there

	// Verify list:
	//done 04/02
	struct nodeStruct *current = head;
	assert(current->item == 0);
	assert(current->next != NULL);
	
	current = current->next;
	assert(current->item == -5);
	assert(current->next == NULL);

	// Sort and verify: 
	//should have -5,0
	List_sort(&head);
	current = head;
	assert(current->item == -5);
	assert(current->next != NULL);
	
	current = current->next;
	assert(current->item == 0);
	assert(current->next == NULL);

	// Delete
	assert(numberofnodes(head) == 2);
	struct nodeStruct *nodeOf0 = List_findNode(head, 0);
	List_deleteNode(&head, nodeOf0);
	
	assert(numberofnodes(head) == 1);
	assert(List_findNode(head, 0) == NULL);
	assert(List_findNode(head, 1) == NULL);
	current = head;
	assert(current->item == -5);
	assert(current->next == NULL);


	//------------------------------------MORE TESTS----------------------

	printf("\nExecution finished. Passed above tests\n");
	return 0;
}

