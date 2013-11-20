
#include "pa10.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Returns a pointer to a new empty stack.
 */
Stack * Stack_create()
{
  Stack *base;
  base = malloc(sizeof(Stack));
  base -> list = NULL;
  return base;
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you _must_ free the entire contained linked-list.
 * Also, you must safely to _nothing_ if stack == NULL. 
 */
void Stack_destroy(Stack * stack)
{
  ListNode *curr;
  ListNode *head;
  if(stack==NULL)
    return;
  head = stack -> list;
  while(head!=NULL)
  {
    curr = head;
    while(curr->next!=NULL)
      curr = curr-> next;
    free(curr);
  }
  free(stack);
}

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
    return (stack->list==NULL);
}

/**
 * Pop the front 'value' from the stack.
 *
 * More precisely, this function must do two things:
 * (1) Return the value of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 */
int Stack_pop(Stack * stack)
{
    int value;
    ListNode *temp;
    if(Stack_isEmpty(stack))
      return -1;
    value = stack -> list -> value;
    temp = stack -> list -> next;
    free(stack ->list);
    stack -> list = temp;
    return value;
}

/**
 * Push an 'value' onto the front of the stack.
 *
 * More precisely, this function must:
 * (1) Create a new ListNode with 'value' for it's value.
 * (2) Push that new ListNode onto the front of the stack's list.
 */
void Stack_push(Stack * stack, int value)
{
  ListNode *new;
  new = malloc(sizeof(ListNode));
  new -> value = value;
  new -> next = stack -> list;
  stack -> list = new;
}

/**
 * Sort 'array' of length 'len' using Donald Knuth's "StackSort"
 *
 * To do this, you must implement the following pseudo-code:
 * (1) Maintain a 'write_index'. This is where you'll write values to
 *     as you sort them. It starts off as zero.
 * (2) Initialize an empty stack
 * (3) For each input value 'x':
 *     (3.a) While the stack is nonempty and 'x' is larger than the 
 *           front 'value' on the stack, pop 'value' and:
 *           (3.a.i) Write 'value' to array[write_index], and 
 *                   increment write_index.
 *     (3.b) Push x onto the stack.
 * (4) While the stack is nonempty, pop the front 'value' and follow
 *     step (3.a.i).
 *
 * The output should be a sorted array if, and only if, the array
 * is stack-sortable. You can find files full of stack-sortable and
 * stack-unsortable arrays in the 'expected' folder.
 */
void stackSort(int * array, int len)
{
  int i= 0, j=0;
  int *sorted;
  Stack *stack;
  sorted = malloc(sizeof(int)*len);
  stack = Stack_create();
  for(i =0; i<len; i++)
  {
    while(!Stack_isEmpty(stack)&& array[i]>stack->list->value)
    {
      sorted[j] = Stack_pop(stack);
      j++;
    }
    Stack_push(stack, array[i]);
  }
  while(!Stack_isEmpty(stack))
  {
    sorted[j] = Stack_pop(stack);
    j++;
  }
  for(i = 0; i<len; i++)
    array[i] = sorted[i];
  free(sorted);
  Stack_destroy(stack);
}

/**
 * Return TRUE (1) if the 'array' of length 'len' is stack-sortable.
 *
 * To do this you must:
 * (1) If 'len' is less than 3, return TRUE.
 * (2) Find the maximum value in 'array'.
 * (3) Partition array into two parts: left of max, and right of max.
 * (4) The maximum value in left must be smaller than the minimum
 *     value in right. (Otherwise return FALSE.)
 * (5) Return TRUE if both left and right are stack-sortable.
 *
 * The 'expected' directory contains files for all sortable and 
 * unsortable sequences of length len. You must return TRUE for every
 * sequence in the sortable files, and you must return FALSE for every
 * sequence in the unsortable files.
 */
int inrange(int thing, int len)
{
  return (thing>0&&thing<len);
}
int isStackSortableHelp3(int *array, int len)
{
  int flag, i, j;
  for(i=0; i< len; i++)
    for(j=0; j<len; j++)    
      array[i]+=array[j];
  for(i=0; i<len;i++)
    if(array[i]<0)
      flag = FALSE;
  return flag;
}
int isStackSortableHelp2(int *array, int len)
{
  int i, flag = TRUE;
  stackSort(array, len);
  for(i = 0; i< len - 1; i++)
    if(array[i]>array[i+1])
      flag = FALSE;
  return flag;
}
int isStackSortableHelp(int * array, int bottom, int top, int len, int flag)
{
  int maxindex, max, i, min, maxindexA, minindex;
  return isStackSortableHelp2(array, len);
  if(inrange(bottom, len)&&inrange(top, len)&&bottom<=top)
  {
    maxindex = bottom;
    max = array[bottom];
    for(i=bottom; i<=top; i++)
    {
      if(array[i]>max)
      {
        max = array[i];
        maxindex = i;
      }
    }
    maxindexA = bottom;
    max = array[bottom];
    for(i=bottom; i<=maxindex-1; i++)            
    { 
      if(array[i]>max)
      {
        max = array[i];
        maxindexA = i;
      }
    } 
    minindex = maxindex + 1;
    min = array[maxindex + 1];
    for(i=maxindex +1; i<=top; i++)
    {
      if(array[i]<min)
      {
        min = array[i];
        minindex = i;
      }
    }
    if(max > min)
      flag = FALSE;
    return flag;
    flag = isStackSortableHelp(array, bottom, maxindex -1, len, flag);
    flag = isStackSortableHelp(array, maxindex+1, top, len, flag);
    return flag;
  }
  return flag;
}
int isStackSortable(int * array, int len)
{
  return isStackSortableHelp(array, 0, len - 1, len, TRUE);
}

/**
 * Generates (and prints) all the unique binary tree shapes of size k
 *
 * To do this, you must:
 * (1) Create an array with the elements [0..k-1] inclusive.
 * (2) Find all the permutations of this array.
 * (3) In the base-case of your permute function, you must test if the
 *     permutation is "stack-sortable"
 * (4) If the permutation is "stack-sortable", then build a binary
 *     tree, and print it using the "Tree_printShape(...)" function.
 *
 * Your genShapes() function must NOT produce duplicate tree shapes.
 * The correct outputs for sizes [1..9] are in the 'expected' 
 * directory.
 */
void genShapes(int k)
{

}




