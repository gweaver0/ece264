#include "pa07.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Prints a linked-list "head" into the output fie "out"
 *
 * NOTE: we have given the code for this function
 */
void List_print(FILE * out, Node * head)
{
 while(head != NULL)
	{
	    fprintf(out, "%5d: %6d\n", head -> index, head -> value);
	    head = head -> next;
	}
    printf("\n");
}


/**
 * Please fill in the code below
 */

/**
 * Destroys a linked list.
 * Arguments:
 * head    A pointer pointing to the first element of the linked list.
 *
 * Returns:
 * void
 *
 * Destroys (frees memory for) the whole linked list. 
 * You can either use recursion or a while loop.
 */
void List_destroy(Node * head)
{
  while(head!=NULL)
  {
    Node *p = head->next;
    free(head);
    head = p;
  }
}

/**
 * Create and initialize a linked list. 
 *
 * Arguments:
 * value     The "value" of the new node
 * index     The "index" of the new node
 *
 * Returns:
 * Returns a newly constructed node. The node can be the head of a
 * linked list.
 * 
 * You should allocate memory in this function. 
 */
Node * List_create(int value, int index)
{
  Node *myNode;
  myNode = malloc(sizeof(Node));
  myNode -> value = value;
  myNode -> index = index;
  myNode -> next = NULL;
  return myNode;
}


/**
 * Build a sparse array from the given indices and values with 
 * specific length.
 *
 * Arguments:
 * value    Array of values
 * index    Array of indices
 * length   Length of the above arrays
 *
 * Returns:
 * A sparse array.
 *
 * If a sparse array node has { value = 1000, index = 2 }, then that means that
 * the index "2" caries the value "1000". This is meant to convey an array of 1000 
 * "2s", but instead of creating 1000 nodes in your linked list, you only create
 * 1 node, and that note conceptually has 1000 "copies" of it. Hence 
 * each node in a sparse array has a "value" in addition to its "index".
 *
 * Note that an index can never carry the value of "0", because this would not make
 * any sense; however, negative values are fine. A negative value may seem odd
 * at first blush; however, this is like substraction, and makes sense for certain
 * cases.
 *
 * You need to insert nodes in ascending order by index.
 * See the notes to "List_insert_ascend"
 */
Node * List_build(int * value, int * index, int length)
{
  Node * head;
  head = NULL;
  int i;  
  for(i = length -1; i >0; i--)
  {
    if(index[i]==index[i-1])
    {
      value[i-1]+=value[i];
      value[i] = 0;
    }
  }
  for(i = 0; i < length; i++)
  {
    if(value[i]!=0)
      head = List_insert_ascend(head, value[i],index[i]);
  }
  return head;
}


/**
 * Inserting "value" and "index" into the correct location in the 
 * sparse array "head"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the linked list.
 * value     The "value" of the value
 * index     The "value" of the index
 *
 * Returns:
 * A sparse array
 *
 * This function inserts the node ["value", "index"] into the sparse
 * array "head", and ensures that the nodes remain in ascending order
 * by their "index".
 *
 * Before and after the call to this function, "head" must be in
 * ASCENDING order by the "index" of each node.
 */
Node * List_insert_ascend(Node * head, int value, int index)
{
  Node *curr;
  Node *insertion;
  insertion = List_create(value,index);
  curr = head;
  if(head == NULL)
    return insertion;
  if(head->index>=index)
  {
    insertion -> next = head;
    return insertion;
  }
  if(head -> next == NULL)
  {
    if(head->index>index)
    {
      insertion -> next = head;
      return insertion;
    }
    else
    {
      head -> next = insertion;
      return head;
    }
  }
  while(curr->next!=NULL)
  {
    if(curr->next->index >= index)
    {
      insertion -> next = curr-> next;
      curr->next = insertion;
      return head;
    }
    curr = curr->next;
  }
  curr->next = insertion;
  return head;
}


/**
 * This function deletes the node with the passed "index"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the sparse array.
 * index     The index to be deleted
 *
 * Returns: 
 * A sparse array with the node removed (the one with index)
 */
Node * List_delete(Node * head, int index)
{
  Node *myNode;
  Node *deletion;
  myNode = head;
  int done = 0;
  if(head->index == index)
  {
    myNode = head->next;
    head->next = NULL;
    List_destroy(head);
    return myNode;
  }
  while(myNode->next!=NULL&&!done)
  {
    if(myNode ->next-> index == index)
    {
      deletion = myNode->next;
      myNode -> next = deletion -> next;
      deletion -> next = NULL;
      List_destroy(deletion);
      done = 1;
    }
    if(!done)
      myNode = myNode -> next;
  }
  return head;
}

/**
 * Copy a list
 *
 * Arguments:
 * head      A pointer pointing to the first element of the sparse array
 *
 * Returns:
 * A copy sparse array
 *
 * This function will copy the sparse array that is passed to it. The
 * copy will be made into new memory. 
 *
 * This is useful, for example, when we want to merge
 * two linked lists together. We can make a copy of one of the linked
 * lists, and then merge the second into the copy. In this way the
 * original copy of the list is not "mutated".
 */
Node * List_copy(Node * head)
{
  int *value;
  int *index;
  Node *curr;
  curr = head;
  int count = 0;
  int i = 0;
  while(curr!=NULL)
  {
    count++;
    curr = curr-> next;
  }
  index = malloc(sizeof(int)*count);
  value = malloc(sizeof(int)*count);
  curr = head;
  while(curr!=NULL)
  {
    value[i]=curr->value;
    index[i]=curr->index;
    i++;
    curr = curr -> next;
  }
  curr = List_build(value, index, count);
  free(index);
  free(value);
  return curr;  
}


/**
 * Merged two linked list together
 * 
 * Arguments:
 * head1      A pointer pointing to linked list 1
 * head2      A pointer pointing to linked list 2
 *
 * Returns:
 * A merged sparse array
 *
 * This function will merge two linked lists. Before merging, you 
 * should make a copy of "head1" so that you will still have the 
 * original array while modifying (merging) the second linked list. 
 *
 * Please refer to the README file for detailed instructions on how to
 * merge two lists.
 *
 * This function should not modify either "head1" or "head2". You only
 * need to make a clone of "head1".
 */
Node * List_add(Node * base, Node * adder)
{
  while(adder!=NULL)
    {
      base = List_insert_ascend(base, adder -> value, adder->index);
      adder = adder -> next;
    }
  return base;
}
Node * Index_add(Node *head)
{
  Node *curr;
  curr = head;
  while(curr!=NULL)
  {
    if(curr->next!=NULL)
    {
      if(curr->index == curr->next->index)
      {
        curr -> value+=curr->next->value;
        curr->next = List_delete(curr->next,curr->index);
      }
    }
    curr = curr->next;
  }
  return head;
}
Node *killzero(Node *head)
{
  Node *curr;
  curr = head;
  Node *temp;
  if(head==NULL)
    return NULL;
  if(head->value ==0)
  {
    curr = head -> next;
    head -> next = NULL;
    List_destroy(head);
    return curr;
  }
  while(curr->next!=NULL)
  {
    if(curr->next->value ==0)
    {
      temp = curr->next;
      curr -> next = curr->next->next;
      List_destroy(temp);
    }
    curr = curr->next;
  }
  return head;
}
Node * List_merge(Node * head1, Node * head2)
{
  Node *merger;
  merger = List_copy(head1);
  merger = List_add(merger, head2);
  merger = Index_add(merger);
  merger = killzero(merger);
  return merger;
}

