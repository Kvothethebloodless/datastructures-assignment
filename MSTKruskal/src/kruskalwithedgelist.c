#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
		int fromID;
		int toID;
		int weight;
} edge;

typedef struct{
		int nodeID;
		bool inMST;//Indicator of presence or absence in the MST
} node;


void selectionsort(edge *array, int no_edges);
edge* inputstructarray(int no_edges);
int printarray(edge *array, int no_edges);
int swapelements(edge *array, int first, int second);
int findminium(edge *array, int beginIndex, int endIndex);
bool iscyclic(int edgeID);
node *nodearray(int no_edges);//Array with all the unique nodes as structs.
edge **createEmptyMST(int no_nodes);//Array of pointers to the edges contained in the MST
void addtoMST(int edgeID, edge **MST);



edge *graph;


node *nodearray(int no_edges){
		node *nodearray;
		int re_nodearray[no_edges*2]; 
		/* Maximum possible nodes are no_edges*2, we will first create an array 
		 * of unique nodes, and then make a nodearray from it. We cannot make a 
		 * node array directly because we donot know the number of nodes*/
		int fID;
		int tID;
		int no_uniquenodes=0;
		int flag1=0;
		int flag2=0;
	   	for(int i=0;i<no_edges;i++){
				fID = graph[i].fromID;
				tID = graph[i].toID;
				for(int j=0;j<no_uniquenodes;j++){
						if (fID==re_nodearray[j])//"From" node's presence has been found
								flag1=1;
						if (tID==re_nodearray[j])//"To" node's presence has been found
								flag2=1;
						if (flag1==1 && flag2==1)//Both nodes presence has been found.
								break;
				}	
				if(flag1==0){
						/* If the fID node is unique,append it to the existing list of
						 * unique nodes by adding to the last position in the
						 * re_nodearray's end */
						re_nodearray[no_uniquenodes] = fID;
						no_uniquenodes++; //Increase the number of unique nodes.
				}
				if(flag2==1){
						/* If the tID node is unique,append it to the existing list of
						 * unique nodes by adding to the last position in the
						 * re_nodearray's end */
						re_nodearray[no_uniquenodes] = tID;
						no_uniquenodes++;
				}
		}
		nodearray = (node *)malloc(no_uniquenodes * sizeof(node));

				

				

		








int swapelements(edge *array, int first, int second){
		int temp_fromID;
		int temp_toID;
		int temp_weight;
		temp_fromID  = array[first].fromID;
		temp_toID = array[first].toID;
		temp_weight = array[first].weight;

		array[first].fromID = array[second].fromID;
		array[first].toID = array[second].toID;
		array[first].weight = array[second].weight;

		array[second].fromID = temp_fromID;
		array[second].toID = temp_toID;
		array[second].weight = temp_weight;

		return 0;
	}

int findminium(edge *array, int beginIndex, int endIndex){
		int temp;
		temp = array[beginIndex].weight;
		int i;
		int minindx=beginIndex;
		for (i=beginIndex; i<=endIndex; i++){
				if (array[i].weight<temp)
				{
						temp=array[i].weight;
						minindx = i;
				}
		}
		return minindx;
}

void selectionsort(edge *array, int no_edges){
		int index=0;
		int minindx;
		for(int i=0;i<no_edges;i++){
				printf("In for loop at index %d \n ",i);
				printarray(array,no_edges);
				minindx = findminium(array,i,no_edges-1);
				swapelements(array,i,minindx);
		}
		return;
}

edge* inputstructarray(int no_edges){
        edge *array;
        int i=0;
        array = (edge *)malloc(no_edges * no_edgesof(edge));
        printf("Enter edge info \n ");
		for (int j=0;j<no_edges;j++){
				printf(" %d th input in the order: fromID toID weight \n", j+1);
				scanf("%d %d %d", &array[j].fromID, &array[j].toID, &array[j].weight);
		}
        return array;
}

int printarray(edge *array,int no_edges){

        printf(" \n Edge Array \n ");
        for(int i=0;i<no_edges;i++)
		{
                printf(" %d %d %d ",array[i].fromID, array[i].toID, array[i].weight);
        printf(" \n ");
		}
        return 0;
}

int inputprompt(void){
		int choice;
		while(1)
		{
		printf(" -------------------------------------------------------------- \n \n ");
		printf("                       Enter the choice: \n");
		printf("\t\t 1) Create graph\n ");
		printf("\t\t 2) Print \n ");
		printf("\t\t 3) Sort edge array\n  ");
		printf("\t\t 4) Exit \n" );
		printf(" \n ");
		printf(" -------------------------------------------------------------- \n \n ");
		scanf("%d", &choice);
		int rollno;
		int fromID;
		int toID, weight;
		int no=0;
		int no_edges;
		edge *principalnode;
		switch(choice){
				case 1:
						printf("Enter the no of edges: \n");
						scanf("%d",&no_edges);
						graph = inputstructarray(no_edges);
						break;
				case 2:
						printarray(graph,no_edges);
						break;
				case 3:
						selectionsort(graph,no_edges);
						break;
			    case 4:
						return;
				default:
						printf("\n ------ Enter a valid choice ------ \n ");
						break;
					}
		}
		return;
}

int main(){
		inputprompt();
}
