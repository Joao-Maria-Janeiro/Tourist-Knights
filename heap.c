#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "heap.h"

#define INT_MAX 255

//O ACERVO É UM VETOR DE NODES(GUARDA O PONTO E O CUSTO TOTAL)

int getLeftChildIndex(int parentIndex){
  return 2 * parentIndex +1;
}

int getRightChildIndex(int parentIndex){
  return 2 * parentIndex +2;
}

int getParentIndex(int childIndex){
  return (childIndex - 1) / 2;
}

int hasLeftChild(int index, int size){
  if(getLeftChildIndex(index) < size){
    return 1;
  }else{
    return 0;
  }
}

int hasRightChild(int index, int size){
  if(getRightChildIndex(index) < size){
    return 1;
  }else{
    return 0;
  }
}

int hasParent(int index){
  if(getParentIndex(index) >= 0){
    return 1;
  }else{
    return 0;
  }
}

Node leftChild(int index, Node * items){
  return items[getLeftChildIndex(index)];
}

Node rightChild(int index, Node * items){
  return items[getRightChildIndex(index)];
}

Node parent(int index, Node * items){
  return items[getParentIndex(index)];
}

void swap(int index1, int index2, Node * items){
  Node temp = items[index1];
  items[index1] = items[index2];
  items[index2] = temp;
}



void swapC(int index1, int index2, Node * items, int** heapPositions){
  Node temp = items[index1];
  items[index1] = items[index2];
  items[index2] = temp;

  heapPositions[items[index2].point.x][items[index2].point.y] = index1;
  heapPositions[items[index1].point.x][items[index1].point.y] = index2;
}

Node pop(int *size, Node * items){
  if(*size == 0){
    //Talvez tenha de ser alterado, o retorno tem de ser um node que valha "NULL"
    Node empty;
    empty.point.x=-1;
    empty.point.y=-1;
    empty.Weight = INT_MAX;
    return empty;
  }else{
    Node item = items[0];
    items[0] = items[*size - 1];
    (*size)--;
    //TODO maybe remove the element from the array, do a realloc? or a new malloc
    heapifyDown(*size, items);
    return item;
  }
}

void add(Node item, Node * items, int *size, int *allocatedSize){
  items[*size] = item;
  (*size)++;
  heapifyUp(*size, items);
}

void heapifyUp(int size, Node * items){
  int index = size - 1;
  while((hasParent(index) == 1) && (parent(index, items)).Weight > (items[index]).Weight){
    swap(getParentIndex(index), index, items);
    index = getParentIndex(index);
  }
}

void heapifyDown(int size, Node * items){
  int index = 0;
  while(hasLeftChild(index, size) == 1){
    int smallerChildrenIdx = getLeftChildIndex(index);
    if((hasRightChild(index, size) == 1) && ((rightChild(index, items)).Weight < (leftChild(index, items)).Weight)){
      smallerChildrenIdx = getRightChildIndex(index);
    }

    if(items[index].Weight < items[smallerChildrenIdx].Weight){
      break;
    }else{
      swap(index, smallerChildrenIdx, items);
    }
    index = smallerChildrenIdx;
  }
}

Node popC(int *size, Node * items, int** heapPositions){
  if(*size == 0){
    //Talvez tenha de ser alterado, o retorno tem de ser um node que valha "NULL"
    Node empty;
    empty.point.x=-1;
    empty.point.y=-1;
    empty.Weight = INT_MAX;
    return empty;
  }else{
    Node item = items[0];
    items[0] = items[*size - 1];
    (*size)--;
    //TODO maybe remove the element from the array, do a realloc? or a new malloc
    heapifyDownC(*size, items, heapPositions);
    return item;
  }
}

void addC(Node item, Node * items, int *size, int *allocatedSize, int** heapPositions){
  items[*size] = item;
  heapPositions[item.point.x][item.point.y] = *size;
  (*size)++;
  heapifyUpC(*size, items, heapPositions);
}

void heapifyUpC(int size, Node * items, int ** heapPositions){
  int index = size - 1;
  while((hasParent(index) == 1) && (parent(index, items)).Weight > (items[index]).Weight){
    swapC(getParentIndex(index), index, items, heapPositions);
    index = getParentIndex(index);
  }
}

void heapifyDownC(int size, Node * items, int ** heapPositions){
  int index = 0;
  while(hasLeftChild(index, size) == 1){
    int smallerChildrenIdx = getLeftChildIndex(index);
    if((hasRightChild(index, size) == 1) && ((rightChild(index, items)).Weight < (leftChild(index, items)).Weight)){
      smallerChildrenIdx = getRightChildIndex(index);
    }

    if(items[index].Weight < items[smallerChildrenIdx].Weight){
      break;
    }else{
      swapC(index, smallerChildrenIdx, items, heapPositions);
    }
    index = smallerChildrenIdx;
  }
}

void printHeap(int size, Node * items) {
  for(int i=0; i<size; i++) {
    printf("(%d, %d) -> %d\n", items[i].point.x, items[i].point.y, items[i].Weight);
  }
}
