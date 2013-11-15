#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pa09.h"

HuffNode *makeTree(FILE *fp)
{
  char *code=NULL;
  int *bigcode=NULL;
  char ch=fgetc(fp);
  int length = 0, i, j,k=0, biglength, done =0, onecount = 0, zerocount =0, dontread =0;
  int myByte[8] = {0,0,0,0,0,0,0,0};
  HuffNode *templeft;
  HuffNode *tempright;
  Stack *mystack;
  HuffNode *mytree;
  mystack = malloc(sizeof(Stack));
  mystack -> next = NULL;
  //mytree = malloc(sizeof(HuffNode));
  if(getBit(ch,0))
  {
    printf("This is a binary file.\n");
    fseek(fp, 0, SEEK_SET);
    ch =fgetc(fp);
    while(onecount>zerocount||length<2)
    {
      for(i =0; i<8;i++)
      {
        dontread--;
        if(dontread<0)
        {
          if(getBit(ch,i)==1)
          {
            dontread = 8;
            onecount++;
          }
          else
            zerocount++;
        }
      }
      length++;
      ch=fgetc(fp);
    }
    fseek(fp, 0, SEEK_SET);
    biglength = 8*length;
    bigcode = malloc(sizeof(int)*biglength);
    for(i = 0; i<length;i++)
    {
      ch = fgetc(fp);
      for(j=0; j<8; j++)
      {
        bigcode[k] = getBit((unsigned char) ch, j);
        k++;
      }
    }
    length = 0;
    for(i = 0; i<biglength; i++)
    {
      if(bigcode[i]==1)
      {
        i+=8;
        length++;
      }
      length++;
    }
    code = malloc(sizeof(char)*length+1);
    k=0;
    for(i = 0; k<length; i++)
    {
      if(bigcode[i]==1)
      {
        code[k] = '1';
        k++;
        for(j = 0; j<8; j++)
        {
          i++;
          myByte[j] = bigcode[i];
        }
        code[k] = ascii(myByte);
        k++;
      }
      else
      {
        code[k] = '0';
        k++;
      }
    }
    free(bigcode);
    code[length]='\0';
  }
  else
  {
    printf("This is a character file.\n");
    fseek(fp, 0, SEEK_SET);
    ch=fgetc(fp);
    while(onecount>zerocount||length<2)
    {
      length++;
      if(ch=='1')
        onecount++;
      if(ch=='0')
        zerocount++;
      ch=fgetc(fp);
    }
    fseek(fp, 0, SEEK_SET);
    code = malloc(sizeof(char)*length+1);
    for(k=0; k<length; k++)
     code[k]=fgetc(fp);
    code[length] = '\0';
  }
  printf("\nThe code is: %s\n", code);
  k = 0;
  while(!done&&k<length)
  {
    printf("\nThe size of the stack is: %i and then ", lengthStack(mystack));
    ch = code[k];
    k++;
    if(ch == '1')
    {
      mystack = pushStack(mystack, makeNode((int)(code[k]), NULL, NULL));
      k++;
      printf("a node is said to be pushed to the stack");
    }
    else
    {
      if(lengthStack(mystack)==1)
      {
        done = 1;
        if(mystack->next!=NULL)
          {
            if(mystack->next->next!=NULL)
              free(mystack->next->next);
            free(mystack->next);
          }
        free(mystack);
        free(code);
        return mytree;
      }
      tempright = getTop(mystack)->node;
      mystack = popStack(mystack);
      templeft = getTop(mystack)->node;
      mystack = popStack(mystack);
      mytree = makeNode(0,templeft,tempright);
      printf("two trees have been popped from the stack and merged; stack size is %i", lengthStack(mystack));
      mystack = pushStack(mystack, mytree);
    }
  }
  free(code);
  return mytree;
}
void postOrderPrint(HuffNode *root,char *filename)
{
  FILE *fp;
  fp = fopen(filename, "w");
  postOrderPrintHelp(root,fp);
  fclose(fp);
}
void postOrderPrintHelp(HuffNode *root, FILE* fp)
{
  // Base case: empty subtree

  if (root == NULL) 
    return;

    // Recursive case: post-order traversal
    // Visit left

  fprintf(fp,"Left\n");
  postOrderPrintHelp(root->left, fp);
  fprintf(fp,"Back\n");
    // Visit right
  fprintf(fp,"Right\n");
  postOrderPrintHelp(root->right,fp);
  fprintf(fp,"Back\n");
  // Visit node itself (only if leaf)
  if (root->left == NULL && root->right == NULL)
    fprintf(fp,"Leaf: %c\n", root->value);
}
void destroy(HuffNode *root)
{
  if(root==NULL)
    return;
  if(root->left!=NULL)
    destroy(root->left);
  if(root->right!=NULL)
    destroy(root->right);
  free(root);
}
char ascii(int num[8])
{
  return (128*num[0]+64*num[1]+32*num[2]+16*num[3]+8*num[4]+4*num[5]+2*num[6]+num[7]);
}
int getBit(unsigned char myByte, int spot)
{
  const unsigned char identityer = 0x80; //byte made of leading 1 following by 7 zeroes
  unsigned char mask=identityer>>spot;
  return ((myByte&mask)==mask);
}
Stack *pushStack(Stack *myStack, HuffNode *root)
{
  Stack *mynext;
  mynext = malloc(sizeof(Stack));
  //mynext -> next = malloc(sizeof(Stack));
  mynext -> next = myStack;
  //mynext -> node = malloc(sizeof(HuffNode));
  mynext -> node = root;
  return mynext;
}
Stack *popStack(Stack *myStack)
{
  Stack *temp;
  temp = myStack;
  if(myStack==NULL)
    return NULL;
  if(myStack->next == NULL)
    {
      free(myStack);
      return NULL;
    }
  temp = myStack->next;
  free(myStack);
  return temp; 
}
Stack *getTop(Stack *myStack)
{
  return myStack;
}
int lengthStack(Stack *myStack)
{
  int length = -1;
  Stack *curr;
  curr = myStack;
  if(myStack ==NULL)
    return 0;
  while(curr!=NULL)
  {
    curr = curr->next;
    length++;
  }
  return length;
}
HuffNode *makeNode(int value, HuffNode *left, HuffNode * right)
{
  HuffNode *node;
  node = malloc(sizeof(HuffNode));
  node -> value = value;
  //node -> left = malloc(sizeof(HuffNode));
  //node -> right = malloc(sizeof(HuffNode));
  node ->left = left;
  node ->right = right;
  return node;
}
