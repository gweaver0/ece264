#include <stdio.h>
#include <stdlib.h>
#include "pao9.h"

int main(int argc, char **argv)
{
  FILE* fp=NULL;
  HuffNode *root = NULL;
  if(argc!=3)
  {
    printf("There must be three arguments.\n");
    return EXIT_FAILURE;
  }
  fp = fopen(arg[1], "r");
  if(fp==NULL)
  {
    printf("Error reading file %s.\n", arg[1]);
    return EXIT_FAILURE;
  }
  root = makeTree(fp);
  fclose(fp);
  postOrderPrint(root, argv[2]);
  destroy(root);
  return EXIT_SUCCESS;  
}
