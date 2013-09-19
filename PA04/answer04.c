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



/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */

void printer(int **thing, int n)
{
  int outer, inner=0;
  for(outer = 0; thing[outer][0] != -1; outer++)
  {
    printf("= ");
    for(inner = 0; thing[outer][inner] != 0; inner++)
      {
        if(inner == 0)
          printf("%i ", thing[outer][inner]);
        else
          printf("+ %i ", thing[outer][inner]);
      }
    printf("\n");
  }
}
int **part(int n)
{
  int **thing;
  int **temp;
  int i, j, k, outer, inner, spot = 0;

  // Initializes MAXLENGTH^2  x (n+1) array with -1 in last row and 0 in all other rows
  thing = malloc(MAXLENGTH*MAXLENGTH * sizeof(int *));
  for(outer = 0; outer < MAXLENGTH*MAXLENGTH; outer++)
  {
    thing[outer] = malloc((n+1)*sizeof(int));
    for(inner = 0; inner < n+1; inner++)
    {
      thing[outer][inner]= 0;
    }
    if(outer == MAXLENGTH*MAXLENGTH - 1)
        thing[outer][0]= -1;
  }

  //escape case
  if(n ==1)
  {
    thing[0][0] = 1;
    thing[1][0] = -1;
    return thing;
  }
  
  //Row terminator is 0. Column terminator is -1. All other entries are meanignful.
  for(i = 1; i < n; i++)
    {
      temp = part(n-i);
      //thing[spot] = i + temp[j]
      for(j = 0; temp[j][0] !=-1; j++)
      {
        thing[spot][0] = i;
        for(k = 0; temp[j][k] != 0; k++)
        {
          thing[spot][k+1] = temp[j][k];
        }
        spot++;
      }  
      free(temp);
    }
  thing[spot][0] = n;
  thing[spot+1][0] = -1;
  return thing;
}
void partitionAll(int value)
{
  int **thing;
  thing = part(value);
  printf("partitionAll %d\n", value);
  printer(thing, value);
  free(thing);
  
}
/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */

int **incrpart(int n)
{
  int **thing;
  int **temp;
  int i, j, k, outer, inner, spot = 0;
      
  // Initializes MAXLENGTH^2  x (n+1) array with -1 in last row and 0 in all other rows
  thing = malloc(MAXLENGTH*MAXLENGTH * sizeof(int *));
  for(outer = 0; outer < MAXLENGTH*MAXLENGTH; outer++)
  {
    thing[outer] = malloc((n+1)*sizeof(int));
    for(inner = 0; inner < n+1; inner++)
    {
      thing[outer][inner]= 0;
    }  
    if(outer == MAXLENGTH*MAXLENGTH - 1)
        thing[outer][0]= -1;
  }
  
  //escape case
  if(n ==1)
  {
    thing[0][0] = 1;
    thing[1][0] = -1;
    return thing;
  }

  
  //Row terminator is 0. Column terminator is -1. All other entries are meanignful.
  for(i = 1; i < n; i++)
    {
      temp = incrpart(n-i);
      for(j = 0; temp[j][0] !=-1; j++)
      {
        if(temp[j][0] > i)
        {
          thing[spot][0] = i;  
          for(k = 0; temp[j][k] != 0; k++)
          {
          thing[spot][k+1] = temp[j][k];
          }
        spot++;
        }
      }
      free(temp);
    }
  thing[spot][0] = n;
  thing[spot+1][0] = -1;
  return thing;
} 
void partitionIncreasing(int value)
{
  int **thing;
  thing = incrpart(value);
  printf("partitionIncreasing %d\n", value);
  printer(thing, value);
  free(thing);
}

/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitionDecreasing(int value)
{
  printf("partitionDecreasing %d\n", value);
  

}

/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partitionOdd(int value)
{
  printf("partitionOdd %d\n", value);
  
}

/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionEven(int value)
{
  printf("partitionEven %d\n", value);

}

/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partitionOddAndEven(int value)
{
  printf("partitionOddAndEven %d\n", value);
  
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



void partitionPrime(int value)
{
  printf("partitionPrime %d\n", value);

}
