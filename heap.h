#include <stdio.h>

#define INIT_SIZE 2


typedef struct Node
{
	int a;

} Node;

typedef struct 
{
	Node *nodes;
	int capacity;
	int size;
} Heap;