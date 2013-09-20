/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void printer(int *arr, int ind)
{
  int count;
  printf("= ");
  for(count = 0; count < ind; count++)
    {
      if(count == 0)
        printf("%i ", arr[count]);
      else
        printf("+ %i ", arr[count]);
    }
    printf("\n");
}

void part(int n, int *arr, int ind)
{
  int i;
  if(n==0)
  {
    printer(arr, ind);
    return;
  }
  for(i = 1; i<=n; i++)
  {
    arr[ind] = i;
    part(n-i, arr, ind+1);
  }
}
void partitionAll(int value)
{
  int *thing;
  thing = malloc(value*sizeof(int));
  printf("partitionAll %d\n", value);
  part(value, thing, 0);
  free(thing);
}

void incrpart(int n, int *arr, int ind)
{
  int i;
  if(n==0)
  {
    printer(arr, ind);
    return;
  }
  for(i = 1; i<=n; i++)
  {
    if(ind==0||i>arr[ind-1])
    {
      arr[ind] = i;
      incrpart(n-i, arr, ind+1);
    }
  }
}
void partitionIncreasing(int value)
{
  int *thing;
  thing = malloc(value*sizeof(int));
  printf("partitionIncreasing %d\n", value);
  incrpart(value, thing, 0);
  free(thing);
}

void decrpart(int n, int *arr, int ind)                             
{
  int i;
  if(n==0)
  {
    printer(arr, ind);
    return;
  }
  for(i = n; i>=1; i--)
  {
    if(ind==0||i<arr[ind-1])
    {
      arr[ind] = i;
      decrpart(n-i, arr, ind+1);
    }
  }  
}
void partitionDecreasing(int value)
{
  int *thing;
  thing = malloc(value*sizeof(int));
  printf("partitionDecreasing %d\n", value);
  decrpart(value, thing, 0);
  free(thing);
}


void oddpart(int n, int *arr, int ind)
{
  int i;
  if(n==0)
  {
    printer(arr, ind);
    return;
  }
  for(i = 1; i<=n; i++)
  {
    if((i%2)!=0)
    {
      arr[ind] = i;
      oddpart(n-i, arr, ind+1);
    }
  }  
}
void partitionOdd(int value)
{
  int *thing;
  thing = malloc(value*sizeof(int));
  printf("partitionOdd %d\n", value);
  oddpart(value, thing, 0);
  free(thing);
}

void evpart(int n, int *arr, int ind)
{
  int i;                                                                       
  if(n==0)                   
  {
    printer(arr, ind);
    return;
  }
  for(i = 1; i<=n; i++)
  {
    if((i%2)==0)
    {
      arr[ind] = i;
      evpart(n-i, arr, ind+1);
    }
  }
}
void partitionEven(int value)
{
  int *thing;
  thing = malloc(value*sizeof(int));
  printf("partitionEven %d\n", value);
  evpart(value, thing, 0);
  free(thing);
}

void evopart(int n, int *arr, int ind) 
{
  int i;                                                 
  if(n==0)
  {                          
    printer(arr, ind);
    return;
  }
  for(i = 1; i<=n; i++)
  {
    if((i%2)!=(ind%2))
    {
      arr[ind] = i;
      evopart(n-i, arr, ind+1); 
    }
  }
}
void partitionOddAndEven(int value)
{
  int *thing;
  thing = malloc(value*sizeof(int));
  printf("partitionOddAndEven %d\n", value);
  evopart(value, thing, 0); 
  free(thing);
}

/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


int isPrime(int y)
{
  int x;
  if(y ==1)
    return 0;
  for(x = 2; x < ((int)sqrt(y))+1; x++)
  {
    if((y%x)==0)
      return 0;
  }
  return 1;
}
void ppart(int n, int *arr, int ind)
{
  int i;
  if(n==0)
  {
    printer(arr, ind);
    return;
  }
  for(i = 1; i<=n; i++)
  {
    if(isPrime(i))
    {
      arr[ind] = i;
      ppart(n-i, arr, ind+1);
    }
  }  
} 
void partitionPrime(int value)
{
  int *thing;
  thing = malloc(value*sizeof(int));
  printf("partitionPrime %d\n", value);
  ppart(value, thing, 0);
  free(thing);
}
