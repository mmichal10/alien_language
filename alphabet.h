#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE NODE;

typedef struct NODE{
	char value;
	int children;
	NODE **childrenPtr;
}NODE;

int find(NODE *root, char *pattern);
int add(NODE *root, char *pattern);
int possibilities(NODE *root, char *pattern);
void cleanUp(NODE *root);
int bracketLength(char *expression);
