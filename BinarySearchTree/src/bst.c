#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

struct node
{
		int key;
		struct node *parent;
		struct node *left;
    struct node *right;
};

typedef struct node node;
node *Tree;

void insert(int new_key);
node* search(node *subtree, int new_key);
node* minimum(node *tree);
node* maximum(node *tree);
void transplant(node *from, node *by);
int delete(int new_key);
void print_inorder(node *tree);
void print_preorder(node *tree);
void print_postorder(node *tree);
int inputprompt(void);

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

void insert(int new_key){
  node *temp;
  node *x,*y;
  temp = (node *)malloc(sizeof(node));
  temp->key=new_key;
  temp->right = NULL;
  temp->left = NULL;


  if(Tree==NULL){ //Tree is empty.
    Tree = temp;
    Tree->parent = NULL;
  }
  else{ //Tree is not empty
    x = Tree;
    while(x!=NULL){
      y=x;
      if(new_key<x->key){
        x=x->left;
      }
      else{
        x=x->right ;
      }
    }
    temp->parent = y; //Reached the would-be parent node.
    if (new_key<y->key)
    y->left = temp;
    else
    y->right = temp;
  }
}

node* search(node *subtree, int new_key){
  if (subtree==NULL || subtree->key==new_key)
  return subtree;
  if(new_key<subtree->key)
  return search(subtree->left, new_key);
  else
  return search(subtree->right, new_key);
}

node* minimum(node *tree){
  node *temp;
  temp = tree;
  while(temp->left!=NULL)
  temp = temp->left;
  return temp;
}

node* maximum(node *tree){
  node *temp;
  temp = tree;
  while(temp->right!=NULL)
  temp = temp->right;
  return temp;
}

void transplant(node *from, node *by){
  //Doesn't guarantee right placement according to order.
  //Should be taken care of by the caller.


  //Setting by's parents to point to null in by's place.
  //Works only if by is not NULL.
  if(by!=NULL){
  if(by->parent!=NULL){
  if(by->parent->right==by)
  by->parent->right = NULL;
  else
  by->parent->left=NULL;
  }
  }



  //Moving by to From's position.
  if (from->parent == NULL)
  Tree=by;
  else if(from->parent->right==from)
  from->parent->right=by;
  else
  from->parent->left=by;

  //Setting the new by's parent.
  if (by!=NULL)
  by->parent = from->parent;

}

int delete(int new_key){
  node *z;
  node *y;
  z = search(Tree, new_key);
  if(z==NULL)
  return 0;

  //Case1: If left child is NULL.
  if(z->left==NULL)
  transplant(z,z->right);


  //Case2: If right child is NULL
  else if(z->right==NULL)
  transplant(z,z->left);
  //Case3a: If right child is not NULL, but has no left child->Implying it is the smallest element greater than the node being deleted.
  else{
  if(z->right->left==NULL){
    y=z->right;
    transplant(z, z->right);
    y->left = z->left;
    y->left->parent = y;
  }
  //Case3b: If right child is not NULL, but has left child-> Implying the smallest element greater than the node being deleted is somewhere down the tree.
  else{
    y = minimum(z);
    transplant(y,y->right);

    transplant(z, y);
    y->right = z->right;
    y->right->parent = y;

    y->left = z->left;
    y->left->parent = y;

  }
  //For both the cases, find the node with minimum value,i.e with no left child while traversing left all the time.
  }
   return 1;
}

void print_inorder(node *tree){
   if(tree!=NULL){
     print_inorder(tree->left);
     printf("  %d  ",tree->key);
     print_inorder(tree->right);
   }
}
void print_preorder(node *tree){
  if(tree!=NULL){
    printf("  %d  ", tree->key);
    print_preorder(tree->left);
    print_preorder(tree->right);
  }
}
void print_postorder(node *tree){
  if(tree!=NULL){
  print_postorder(tree->left);
  print_postorder(tree->right);
  printf("  %d  ", tree->key);
  }
}



int inputprompt(void){
		int choice;
		while(1)
		{
    printf("\n");
		printf(" -------------------------------------------------------------- \n \n ");
		printf("                       Enter the choice: \n");
		printf("\t\t 1) Insert Elements \n ");
		printf("\t\t 2) Search Element \n ");
		printf("\t\t 3) Delete Element \n ");
		printf("\t\t 4) Find Minimum \n ");
		printf("\t\t 5) Find Maximum \n");
		printf("\t\t 6) Print Inorder \n");
		printf("\t\t 7) Print Preorder \n");
		printf("\t\t 8) Print PostOrder \n");
    printf("\n");



		printf(" \n ");
		printf(" -------------------------------------------------------------- \n \n ");
		scanf("%d", &choice);
    int new_key;
    int result;
    node *res;

		switch(choice){
				case 1:
            printf("Enter the element insert: \n");
            scanf("%d",&new_key);
            insert(new_key);
						break;

				case 2:
            printf("Enter the element to search: \n");
            scanf("%d",&new_key);
            res = search(Tree, new_key);
            if(res)
            printf("Element found. \n");
            else
            printf("Element not found. \n");
            break;

				case 3:
            printf("Enter the element to delete: \n");
            scanf("%d",&new_key);
            result = delete(new_key);
            if(result)
            printf("Succesfully deleted %d \n", new_key);
            else
            printf("Couldn't find the element. \n");
						break;

				case 4:
            res=minimum(Tree);
            printf("The minimum of the tree is %d \n", res->key);
						break;
				case 5:
            res=maximum(Tree);
            printf("The maxium of the tree is %d \n", res->key);
						break;
        case 6:
            print_inorder(Tree);
            break;
        case 7:
            print_preorder(Tree);
            break;
        case 8:
            print_postorder(Tree);
            break;
				default:
						printf("\n ------ Enter a valid choice ------ \n ");
						break;
					}
		}
		return 0;
}

int main(){
  signal(SIGSEGV, handler);
  inputprompt();
}
