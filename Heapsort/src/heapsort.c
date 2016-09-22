#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* inputintarray(int size);
int printarray(int *array, int size);
int parent(int i);
int right_child(int i);
int left_child(int i);
void max_heapify(int i);
void build_maxheap(int i);
void heapSort(void);
void swapelements(int first, int second);



int *A;
int heapsize;
int length;

int parent(int i){
  return floor(i/2);
}

int right_child(int i){
  return (i*2)+1;
}

int left_child(int i){
  return (i*2);
}

void max_heapify(int i){
  int l,r,max;
  l = left_child(i);
  r = right_child(i);
  if((l<=(heapsize))&&(A[i]<A[l]))
  max = l;
  else
  max = i;
  if((r<=(heapsize))&&(A[max]<A[r]))
  max = r;
  if (max!=i){
    //Swapping A[i] with A[max]
    swapelements(max, i);
    //Further max_heapifying the rest of the node
    max_heapify(max);
  }
}

void build_maxheap(int i){
  for (int i = floor(heapsize/2); i >=  1; i--) {
    max_heapify(i);
  }
}

void heapSort(void){
  int length;
  build_maxheap(1);
  length= heapsize;
  for(int i=length;i>1;i--){
    swapelements(1,i);
    heapsize--;
    max_heapify(1);
  }
}


int* inputarray(int size){
        int *array;
        int i=1;
        array = (int *)malloc((size+1) * sizeof(int));//Because first element is empty to work the 2n convention.
        printf("Enter array of numbers \n ");
        while (i <= size && scanf("%d", &array[i++]) == 1){}
        return array;
}

int printarray(int *array,int size){

        printf(" \n Printing array \n ");
        for(int i=1;i<=size;i++)
                printf(" %d ",array[i]);
        printf(" \n ");
        return 0;
}


void swapelements(int first, int second){
        int temp;
        temp = A[first];
        A[first] = A[second];
        A[second] = temp;
        return;
}

int main(){
        A = inputarray(10);
        heapsize = 10;
        printarray(A,10);
        heapSort();
        printarray(A,10);
}
