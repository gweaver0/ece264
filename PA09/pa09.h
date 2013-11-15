#ifndef PA09_H
#define PA09_H

typedef struct _huffnode {
    int value; 
    struct _huffnode * left;
    struct _huffnode * right;
} HuffNode;

typedef struct _stack {
    struct _stack * next;
    HuffNode * node;
} Stack;

HuffNode *makeTree(FILE *fp);
void postOrderPrint(HuffNode *root, FILE *fp);
void destroy(HuffNode *root);
char ascii(int num[8]);
int getBit(unsigned char myByte, int spot);
Stack *pushStack(Stack *myStack, HuffNode *root);
Stack *popStack(Stack *myStack);
Stack *getTop(Stack *myStack);
int lengthStack(Stack *myStack);
HuffNode *makeNode(int value, HuffNode *left, HuffNode *right);
#endif
