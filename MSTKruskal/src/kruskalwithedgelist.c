#include<stdio.h>
#include<stdlib.h>

typedef struct
{
		int fromID;
		int toID;
		int weight;
} edge;


void selectionsort(edge *array, int no_edges);
edge* inputstructarray(int no_edges);
int printarray(edge *array, int no_edges);
int swapelements(edge *array, int first, int second);
int findminium(edge *array, int beginIndex, int endIndex);
edge **createEmptyMST(int no_nodes);//Array of pointers to the edges contained in the MST
int numnodes(edge *graph, int no_edges, int print);
edge **Kruskal(int no_edges);
void initializeUnionFind(int no_nodes); //Initializes the data structure for Union Find with 2 arrays holding parent1 and size respectively.
int findRoot(int nodeID); //Finds the root of a given nodeID.
void Union(int node1, int node2); //Unifies two subsets into a single set.
int isLooping(int fromNode, int toNode); //Checks if adding an edge is gonna make it cyclic.


//Global Variable Declarations
edge *graph;
int *parent1, *SubsetSize;

int isLooping(int fromNode, int toNode){
	if(findRoot(fromNode) == findRoot(toNode))
	return 1; //YES, LOOPING!
	else
	return 0; //NO, NOT LOOPING!
}

void initializeUnionFind(int no_nodes){
	int de=0;
	parent1 = (int *)malloc(sizeof(int)*(no_nodes+1)); //Indexing starts from zeros. So.
	SubsetSize = (int *)malloc(sizeof(int)*(no_nodes+1));

	for (size_t i = 0; i < no_nodes+1; i++) {
	  parent1[i] = i;
	  SubsetSize[i]=1;
	}
	return;
}


int findRoot(int nodeID){
	if(parent1[nodeID]==nodeID)
	return nodeID;
	else
	return findRoot(parent1[nodeID]);
}

void Union(int node1, int node2){
	int root1, root2;
	root1 = findRoot(node1);
	root2 = findRoot(node2);
	if(SubsetSize[root1]>=SubsetSize[root2]){
	  parent1[root2]=root1;
		SubsetSize[root2]+=SubsetSize[root1];
	}
	else{
		parent1[root1]=root2;
		SubsetSize[root1]+=SubsetSize[root2];
	}
	return;
}

edge **createEmptyMST(int no_nodes){
		edge **emptymst;
		emptymst = (edge**)malloc(no_nodes * sizeof(edge*));
		return emptymst;
}

edge **Kruskal(int no_edges){
		edge **MST;
		int no_nodes;
		no_nodes = numnodes(graph, no_edges,0);
		selectionsort(graph,no_edges);


		////Array to keep track of all edges' inclusion in the MST
		int mst_edgeincluded[no_edges];
		for(int i=0;i<no_edges;i++)
				mst_edgeincluded[i]=0;


		//Arrays to keep track of parent1 and SubsetSize in UnionFind algorithm
		initializeUnionFind(no_nodes);

		int fromNode,toNode,i=0,no_mstedges=0;
		while(no_mstedges<no_nodes-1)//No of nodes in MST=no_nodes-1
		{
				fromNode = graph[i].fromID;
				toNode = graph[i].toID;
				if(!isLooping(fromNode,toNode)){
					mst_edgeincluded[i]=1;
					no_mstedges++;
					Union(fromNode,toNode);
				}
				i++;
		}
		MST = createEmptyMST(no_mstedges);
		int j=0;
		for (int i=0;i<no_edges;i++){
				if(mst_edgeincluded[i]){
						//Means the edge is included in MST,
						//add it to the list of edges in MST
						MST[j]=graph+i; //Pointer to the edge going into the list.
						j++;
				}
		}
		return MST;
}


int numnodes(edge *graph, int no_edges,int print){
		int re_nodearray[no_edges*2];
		/* Maximum possible nodes are no_edges*2, we will first create an array
		 * of unique nodes, and then make a nodearray from it. We cannot make a
		 * node array directly because we donot know the number of nodes*/
		for (size_t i = 0; i < no_edges*2; i++) {
			re_nodearray[i]=-1;
			/* code */
		}
		int fID;
		int tID;
		int no_uniquenodes=0;
		int flag1=0;
		int flag2=0;
	   	for(int i=0;i<no_edges;i++){
				flag1=0;
				flag2=0;
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
				if(flag2==0){
						/* If the tID node is unique,append it to the existing list of
						 * unique nodes by adding to the last position in the
						 * re_nodearray's end */
						re_nodearray[no_uniquenodes] = tID;
						no_uniquenodes++;
				}
		}
		if(print){
				for(int i=0;i<no_uniquenodes;i++)
						printf("-%d-",re_nodearray[i]);
		}
		return no_uniquenodes;
}



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
		int minindx;
		for(int i=0;i<no_edges;i++){
				printf("In for loop at index %d \n ",i);
				minindx = findminium(array,i,no_edges-1);
				swapelements(array,i,minindx);
		}
		return;
}

edge* inputstructarray(int no_edges){
        edge *array;
        int i=0;
        array = (edge *)malloc(no_edges * sizeof(edge));
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
		printf("\t\t 2) Create graph from Memory\n");
		printf("\t\t 3) Print \n ");
		printf("\t\t 4) Find MST\n");
		printf("\t\t 5) Exit \n" );
		printf(" \n ");
		printf(" -------------------------------------------------------------- \n \n ");
		scanf("%d", &choice);
		int rollno;
		int fromID;
		int toID, weight;
		int no=0;
		int no_edges;
		edge *principalnode;
		int no_nodes;
		edge **MST;
		edge *array;

		int edlist[10][3] = {{1,2,3},
												 {1,7,7},
												 {1,5,4},
												 {2,7,8},
												 {2,3,5},
												 {3,7,6},
												 {3,4,4},
												 {4,7,8},
												 {4,5,2},
												 {5,7,5},
						};
		switch(choice){
				case 1:
						printf("Enter the no of edges: \n");
						scanf("%d",&no_edges);
						graph = inputstructarray(no_edges);
						break;
				case 2:
						no_edges = 10;
			  		array = (edge *)malloc(no_edges * sizeof(edge));
						for (size_t i = 0; i < 10; i++) {
							array[i].fromID=edlist[i][0];
							array[i].toID=edlist[i][1];
							array[i].weight=edlist[i][2];
						}
						graph=array;

						break;

				case 3:
						printarray(graph,no_edges);
						break;
			  case 4:
						MST = Kruskal(no_edges);
					  int no_mstedges = numnodes( graph, no_edges, 0) -1;
						printf("\n\t\t****** MST of the given graph ****** \n");
						printf("\t   ***************************************************\n");
						printf("\t\t   SRC \t\t DEST \t\tWEIGHT\n");
						for (int i = 0; i  <no_mstedges; i ++) {
							printf(" \t\t    %d \t\t  %d \t\t  %d \n",MST[i]->fromID,MST[i]->toID,MST[i]->weight);
						}
						printf("\t   ***************************************************\n");
						break;
				case 5:
						return;
				default:
						printf("\n ------ Enter a valid choice ------ \n ");
						break	;
					}
		}
		return 0;
}

int main(){
		inputprompt();
}
