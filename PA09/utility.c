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
  int length = 0, i, j,k=0, biglength, done =0;
  int myByte[8] = {0,0,0,0,0,0,0,0};
  HuffNode *templeft;
  HuffNode *tempright;
  Stack *mystack;
  HuffNode *mytree;
  mystack = malloc(sizeof(Stack));
  mytree = malloc(sizeof(HuffNode));
  if(getBit(ch,0))
  {
    printf("This is a binary file.\n");
    fseek(fp, 0, SEEK_SET);
    while((ch=fgetc(fp))!='\n')
    {
      printf("%c", ch);
      length++;
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
    printf("\n%s\n",code);
  }
  else
  {
    printf("This is a character file.\n");
    fseek(fp, 0, SEEK_SET);
    while((ch=fgetc(fp))!='\n')
    {  
      printf("%c", ch);
      length++;
    }
    fseek(fp, 0, SEEK_SET);
    code = malloc(sizeof(char)*length+1);
    fgets(code, length, fp);
    code[length] = '\0';
    printf("\n%s\n",code);
  }
  k = 0;
  while(!done&&k<length)
  {
    ch = code[k];
    k++;
    if(ch == '1')
    {
      mystack = pushStack(mystack, makeNode((int)(code[k]), NULL, NULL));
      k++;
    }
    else
    {
      if(lengthStack(mystack)<2)
      {
        printf("Invalid specs for Huffman tree.\n");
        return NULL;
      }
      tempright = getLast(mystack);
      popStack(mystack);
      templeft = getLast(mystack);
      popStack(mystack);
      mytree = makeNode(0,templeft,tempright);
      if(lengthStack(mystack)==0)
        done = 1;
      else
        mystack = pushStack(mystack, mytree);
    }
  }
  return mytree;
}
void postOrderPrint(HuffNode *root, char *filename)
{
  return;
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
  unsigned char mask=identityer>>spot;
  return ((myByte&mask)==mask);
}
Stack *pushStack(Stack *myStack, HuffNode *root)
{
  Stack *mynext;
  Stack  *temp;
  temp = myStack;
  mynext = malloc(sizeof(Stack));
  mynext -> next = malloc(sizeof(Stack));
  mynext -> next = NULL;
  mynext -> node = malloc(sizeof(HuffNode));
  mynext -> node = root;
  while(temp!=NULL)
    temp = temp->next;
  temp = mynext;
  return myStack;
}
void popStack(Stack *myStack)
{
  Stack *temp = myStack;
  if(temp==NULL)
  {
    free(temp);
    return;
  }
  while(temp->next!=NULL)
    temp = temp->next;
  free(temp); 
}
HuffNode *getLast(Stack *myStack)
{
  Stack *temp = myStack;
  if(temp->next == NULL)
    return myStack->node;
  while(temp->next!=NULL)
    temp = temp->next;
  return temp->node;
}
int lengthStack(Stack *myStack)
{
  int length = 0;
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
  node -> left = malloc(sizeof(HuffNode));
  node -> right = malloc(sizeof(HuffNode));
  node ->left = left;
  node ->right = right;
  return node;
}
