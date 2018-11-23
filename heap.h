#ifndef _HEAP_H
#define _HEAP_H


int getLeftChildIndex(int parentIndex);
int getRightChildIndex(int parentIndex);
int getParentIndex(int childIndex);


int hasLeftChild(int index, int size);
int hasRightChild(int index, int size);
int hasParent(int index);


int leftChild(int index, int * items);
int rightChild(int index, int * items);
int parent(int index, int * items);


void swap(int index1, int index2, int * items);

//TODO maybe do the "ensureExtraCapacity function"

int peek(int size, int * items);
int pop(int size, int * items);


void add(int item, int * items, int size);

void heapifyUp(int size, int * items);

void heapifyDown(int size, int * items);

#endif
