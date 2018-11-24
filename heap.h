#ifndef _HEAP_H
#define _HEAP_H

#include "structs.h"

int getLeftChildIndex(int parentIndex);
int getRightChildIndex(int parentIndex);
int getParentIndex(int childIndex);


int hasLeftChild(int index, int size);
int hasRightChild(int index, int size);
int hasParent(int index);


Node leftChild(int index, Node * items);
Node rightChild(int index, Node * items);
Node parent(int index, Node * items);


void swap(int index1, int index2, Node * items);

//TODO maybe do the "ensureExtraCapacity function"

Node peek(int size, Node * items);
Node pop(int *size, Node * items);


void add(Node item, Node * items, int *size);

void heapifyUp(int size, Node * items);

void heapifyDown(int size, Node * items);

void printHeap(int size, Node * items);

#endif
