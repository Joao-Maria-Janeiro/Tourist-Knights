#include <stdlib.h>
#include <stdio.h>

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

int leftChild(int index, int * items){
  return items[getLeftChildIndex(index)];
}

int rightChild(int index, int * items){
  return items[getRightChildIndex(index)];
}

int parent(int index, int * items){
  return items[getParentIndex(index)];
}

void swap(int index1, int index2, int * items){
  int temp = items[index1];
  items[index1] = items[index2];
  items[index2] = temp;
}

//TODO maybe do the "ensureExtraCapacity function"

int peek(int size, int * items){
  if(size == 0){
    return -1;
  }else{
    return items[0];
  }
}

int pop(int size, int * items){
  if(size == 0){
    return -1;
  }else{
    int item = items[0];
    items[0] = items[size - 1];
    size--;
    //TODO maybe remove the element from the array, do a realloc? or a new malloc
    heapifyDown();
    return item;
  }
}


void add(int item, int * items, int size){
  //TODO allocate memmory or maybe do some other implementation that instead of reallocing 1 by 1 just allocs like 50/100 and then only reallocs if those are full and then it would realloc after
  items[size] = item;
  size++;
  heapifyUp();
}

void heapifyUp(int size, int * items){
  int index = size - 1;
  while((hasParent(index) == 1) && parent(index) > items[index]){
    swap(getParentIndex(index), index);
    index = getParentIndex(index);
  }
}

void heapifyDown(int size, int * items){
  int index = 0;
  while(hasLeftChild(index) == 1){
    int smallerChildrenIdx = getLeftChildIndex(index);
    if((hasRightChild(index) == 1) && (rightChild(index) < leftChild(index))){
      smallerChildrenIdx = getRightChildIndex(index);
    }

    if(items[index] < items[smallerChildrenIdx]){
      break;
    }else{
      swap(index, smallerChildrenIdx);
    }
    index = smallerChildrenIdx;
  }
}
