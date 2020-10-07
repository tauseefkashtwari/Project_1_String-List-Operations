#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Allocate memory for a node of type struct nodeStruct and initialize
 * it with the value item. Return a pointer to the new node.
 */
//might be done thurs 9:47 pm
struct nodeStruct* List_createNode(int item)
{
	struct nodeStruct *new_node = malloc(sizeof(struct nodeStruct));

	//check if node empty
	if(new_node == NULL)
	{
		return NULL;
	}

	//we got data and next pointer should be NULL
	else
	{
		new_node->item = item; 
		new_node->next = NULL; //it won't point to anything . 
	}
	
	return new_node;
}

/*
	Added sun 04/02
	Check if already inserted node and return 1(Success), 0 failure
*/
int check_nodeinsert(struct nodeStruct *headRef,struct nodeStruct *node)
{
	struct nodeStruct *temp = headRef;

	//loop using temp pointing to head
	while(temp != NULL)
	{
		//if it is
		if(temp == node)
			return 1;

		temp=temp->next;
	}
	return 0;
}


/*
 * Insert node at the head of the list.
 */

//we are given reference(pointer to a pointer) to head --** allows us to modify memory lcoation
//done sun 04/02 7:36 pm
void List_insertHead (struct nodeStruct **headRef, struct nodeStruct *node)
{
	if(check_nodeinsert(*headRef,node) || node == NULL)
		return;


	node->next = *headRef; //make next pointer to old head
	*headRef = node; //upadte the headref
	
}


/*
 * Insert node after the tail of the list.
 */
//done sun 04/02
void List_insertTail (struct nodeStruct **headRef, struct nodeStruct *node)
{
	if(check_nodeinsert(*headRef,node) || node == NULL)
		return;

	struct nodeStruct *tmp = *headRef;

	while(tmp->next != NULL)
	{
		//move to next
		tmp = tmp->next;
	}

	tmp->next = node;

	//need to defefrence head

}


/*
 * Count number of nodes in the list.
 * Return 0 if the list is empty, i.e., head == NULL
 */
//Done thurs 10:06 pm
int numberofnodes (struct nodeStruct *head)
{
	int count = 0;
	struct nodeStruct *current = head; //that's fine
	while(current != NULL)
	{
		count++;
		//printf("%d",current->item);
		current = current->next; //current-->next points to the next element and if that's empty will be stored in CURRENT 
	}
	return count; //would return 0 if current i.e head is empty. 

}


/*
 * Return the first node holding the value item, return NULL if none found
 */
//done sun 04/02
struct nodeStruct* List_findNode(struct nodeStruct *head, int item)
{
	//base case: empty lisst
	if(head == NULL)
	{
		return NULL;
	}

	struct nodeStruct *current = head;
	
	//loop
	while(current != NULL)
	{
		//match found
		if(current->item == item)
		{
			return current;
		}
		current= current->next;
	
	}
	return NULL; //no match
}

/*
 * Delete node from the list and free memory allocated to it.
 * This function assumes that node has been properly set to a valid node 
 * in the list. For example, the client code may have found it by calling 
 * List_findNode(). If the list contains only one node, the head of the list 
 * should be set to NULL.
 */
void List_deleteNode (struct nodeStruct **headRef, struct nodeStruct *node)
{
	//we need previous pointer,current pointer 

	//base case:delete one node
	if(numberofnodes(*headRef) == 1)
	{
		free(*headRef);
		return;
	}

	struct nodeStruct *current,*previous;
	previous = current = *headRef; //let previous point to the head

	//we have node and it points to something
	while(current->next != NULL)
	{
		previous = current;
		current = current->next; //update current
	}

	previous->next = current->next; //preivous pointer should point to next e.g if delete 2, 1 should point to 3. 
	free(current);

}


/*
 * Sort the list in ascending order based on the item field.
 * Any sorting algorithm is fine.
 */
//done 04/02
void List_sort (struct nodeStruct **headRef)
{
	struct nodeStruct *temp_sort = *headRef; //temp point to head
	struct nodeStruct *smallest, *next_node;

	while(temp_sort != NULL)
	{
		//compare 
		smallest = temp_sort;//smallest be the first one
		next_node = temp_sort->next;//the next node
		
		while(next_node != NULL)
		{
			if(next_node->item < smallest->item)
			{
				//swap and update the smnallest just the node !!!!!!!!!!!!!!
				smallest = next_node;
			}
			next_node = next_node->next;
		}

		//swap item itself!!!(MEMBER OF STRUCT)
		int min = temp_sort->item;
		temp_sort->item = smallest->item;
		smallest->item = min;


		//update 
		temp_sort = temp_sort->next;//end
	}



}


//added************************************************
//DONE -04/02
void List_print(struct nodeStruct **headRef)
{
	struct nodeStruct *current_print = *headRef; //dereferendce headref

	while(current_print != NULL)
	{
		printf("%d\n",current_print->item);
		current_print = current_print->next;
	}
	printf("\n");
}