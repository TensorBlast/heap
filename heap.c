#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"


Heap init_heap()
{
	Heap heap;
	heap.nodes = (Node *) malloc(sizeof(Node)*INIT_SIZE);
	heap.capacity = INIT_SIZE;
	heap.size = 0;

	return heap;
}

int comparator(Node a, Node b)
{
	return a.a - b.a;
}

void insertKey(Heap *h, int k, int (*compare)(Node a, Node b));

void swapNodes(Node * a, Node * b);

void printHeap(Heap h);

void minHeapify(Heap *h, int i,int (*compare)(Node a, Node b));

int extractMin(Heap *h,int (*compare)(Node a, Node b));

int main()
{
	Heap h = init_heap();

	insertKey(&h, 5, (*comparator));
	insertKey(&h, 3,(*comparator));
	insertKey(&h, 1,(*comparator));
	insertKey(&h, 6,(*comparator));
	insertKey(&h, 9,(*comparator));
	insertKey(&h, 2,(*comparator));
	printHeap(h);

	printf("%d\n",extractMin(&h, (*comparator)));
	printf("%d\n",extractMin(&h, (*comparator)));
	return 0;
}



void insertKey(Heap *h, int k, int (*compare) (Node a, Node b))
{
	if (h->size==h->capacity) {
		printf("Heap is full\n");
		printf("Increasing capacity...\n");
		h->nodes = realloc(h->nodes, sizeof(Node)*h->capacity*2);

		h->capacity*=2;
	}

	int i = h->size;
	if (h->size==0) {
		h->nodes[h->size++].a = k;
	}
	else {
		h->nodes[h->size++].a = k;

		while (i !=0 && (*compare)(h->nodes[(i-1)/2],h->nodes[i])>0) {
			swapNodes(&h->nodes[(i-1)/2], &h->nodes[i]);
			i = (i-1)/2;
		}
	}

}

void printHeap(Heap h)
{
	int i;
	for (i = 0; i < h.size; i++)
		printf("%d\n", h.nodes[i].a);
}

void swapNodes(Node * a, Node * b)
{

	Node temp;
	memcpy(&temp, a, sizeof(Node));
	memcpy(a,b,sizeof(Node));
	memcpy(b,&temp,sizeof(Node));


}

void minHeapify(Heap *h, int i, int (*compare)(Node a, Node b))
{
	int l = 2*i+1;
	int r = 2*i+2;

	int smallest = i;

	if (l<h->size && (*compare)(h->nodes[l], h->nodes[i])<0)
		smallest = l;

	if (r < h->size && (*compare)(h->nodes[r], h->nodes[smallest])<0)
		smallest = r;

	if (smallest != i)
	{
		swapNodes(&h->nodes[i], &h->nodes[smallest]);
		minHeapify(h, smallest, comparator);
	}
}

int extractMin(Heap *h,int (*compare)(Node a, Node b))
{
	if (h->size<=0)
		return -1;

	int root = h->nodes[0].a;
	h->size--;
	h->nodes[0] = h->nodes[h->size];
	minHeapify(h, 0, comparator);

	return root;
}