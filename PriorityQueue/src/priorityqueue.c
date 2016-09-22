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
int heap_maximum(void);
int heap_extractmaximum(void);
void heap_increasekey(int i,int key);
void max_heapinsert(int key);
int inputprompt(void);




int *A;
int heapsize;
int length;

int heap_extractmaximum(void){
  if(heapsize<1)
  {
  printf("Heap overflow, error.");
  return -1;
  }
  int max;
  max = A[1];
  A[1] = A[heapsize];
  heapsize--;
  max_heapify(1);
  return max;
}

void heap_increasekey(int i, int key){
  if(key<A[i])
  {
    printf("Key value lesser than current key.");
    return;
  }
  A[i]=key;
  while((i>1)&&(A[parent(i)] < A[i])){
    swapelements(i, parent(i));
    i = parent(i);
  }
}

void max_heapinsert(int key){
  heapsize = heapsize+1;
  A[heapsize] = -1000;
  heap_increasekey(heapsize, key);
}

int heapmaximum(void){
  return A[1];
}

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
        array = (int *)malloc((size+100) * sizeof(int));//Because first element is empty to work the 2n convention.
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

int inputprompt(void){
		int choice;
		while(1)
		{
    printf("\n");
		printf(" -------------------------------------------------------------- \n \n ");
		printf("                       Enter the choice: \n");
		printf("\t\t 1) Insert Queue Element \n ");
		printf("\t\t 2) Query Maximum Key\n");
		printf("\t\t 3) Extract-Maximum Key\n");
		printf("\t\t 4) Increase Key\n");
    printf("\n");



		printf(" \n ");
		printf(" -------------------------------------------------------------- \n \n ");
		scanf("%d", &choice);
    int new_key;
    int result;
    int id;
    heapsize = 0;

		switch(choice){
				case 1:
            printf("Enter the element insert: \n");
            scanf("%d",&new_key);
            max_heapinsert(new_key);
						break;

				case 2:
            printf("The maximum key in the heap is: %d \n", heap_maximum());
            break;

				case 3:
            result = heap_extractmaximum();
            if (result!=-1){
              printf("Heap element with key %d is extracted \n", result);
            }
            break;

				case 4:
            printf("Enter the node where key is being updated. \n");
            scanf("%d",&id);
            printf("Enter the raised key. Note that it must be more than current. \n");
            scanf("%d",&new_key);
            heap_increasekey(id, new_key);
            printf("Increased the key of %d node to %d", id, new_key);
						break;
            
				default:
						printf("\n ------ Enter a valid choice ------ \n ");
						break;
					}
		}
		return 0;
}

int main(){
        heapsize = 10;
        printarray(A,10);
        heapSort();
        printarray(A,10);
}
