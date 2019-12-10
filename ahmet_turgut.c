
//author: Ahmet TURGUT 150117046
//email: turgutahmt@gmail.com

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define treeSpace 10 //use in printTree(){}function

typedef struct node{ //tree struct 
	
	int data;
	struct node *left;
	struct node *right;

}node;

typedef struct list{ //list struct for node
	
	struct node *node;
	struct list *next;
	
}list;


int size=0;//size of node
int sizeB=2;//size of before length list
int forloop=1;//how many times the loop will run in print function

list *find(list *control){ //find the possible list. For example you have list and list have two node {15,12}. You can choose 1 node after 12 but this node need to be {15 or 12} left right child. 
							// 15's right child 17 , 12's left child 8. Now possibleList {17,8}. You can create list {15,12,8} and {15,12,17}. This mean is you can find possible list. call in print(){} function. 
	
	list *iter;
	list *possible=NULL;
	list *temp=control;
	char TF='T';
		while(temp!=NULL){
		TF='T';
			if(temp->node->right!=NULL){ //check right node
					iter=control;
					while(iter!=NULL){if(iter->node->data==temp->node->right->data){TF='F';break;}
						iter=iter->next;
					}
				if(TF=='T'){
					if(possible==NULL){
						
							possible=(list*)malloc(sizeof(list));
							possible->node=temp->node->right;
							possible->next=NULL;
							
						}
						else{
							iter=possible;
							while(iter->next!=NULL){iter=iter->next;}
							iter->next=(list*)malloc(sizeof(list));
							iter->next->node=temp->node->right;
							iter->next->next=NULL;
					}
				}TF='T';	
			} if(temp->node->left!=NULL){ //check left node
				
				iter=control;
				
					while(iter!=NULL){if(iter->node->data==temp->node->left->data){TF='F';break;}
						iter=iter->next;
					}
					if(TF=='T'){
						if(possible==NULL){
							possible=(list*)malloc(sizeof(list));
							possible->node = temp->node->left;
							possible->next=NULL;
						}
						else{
							iter=possible;
							while(iter->next!=NULL){iter=iter->next;}
							iter->next=(list*)malloc(sizeof(list));
							iter->next->node=temp->node->left;
							iter->next->next=NULL;
						}
					}		
			}
			temp=temp->next;
		}

	return possible;
}
node *insert(node *root,int key){// insert a node in tree.

	if(root==NULL){
		root=(node*)malloc(sizeof(node));
		root->data=key;
		root->left=NULL;
		root->right=NULL;
		return root;	
	}
	
	if(root->data < key){
		root->right=insert(root->right,key);
		return root;
	}
		root->left=insert(root->left,key);
		return root;
}

list* print(list *L){ //This function goal is create a linkedlist. Call find(){} function. You can find possible list and add end of the list.
	if(size>11){
		printf("Please wait, calculating.\n");//This goal is if enter too much node in program. Check "program is running?".
	}
	
	list *howMany;
	int forloopAfter=0;

	for(int j=0;j<forloop;j++){
		
		list *temp=NULL;
		list *iter=L;
	
	
	for(int k=0;k<sizeB;k++){//clone list but for before size.
		if(temp==NULL){
			temp=(list*)malloc(sizeof(list));
			temp->node=iter->node;
			iter=iter->next;
			temp->next=NULL;
		}else{
			list *titan=temp;
			while(titan->next!=NULL){
				titan=titan->next;
			}
			titan->next=(list*)malloc(sizeof(list));
			titan->next->node=iter->node;
			titan->next->next=NULL;
			iter=iter->next;
		}
	}
	
	iter=L;
	list *sentor=find(temp);

	while(iter->next!=NULL){
		iter=iter->next;
	}
	
	while(sentor!=NULL){//add possible list's node in the end of list.
		list *yaz=temp;
		forloopAfter++;
		for(int k=0;k<sizeB;k++){
			iter->next=(list*)malloc(sizeof(list));
			iter->next->node=yaz->node;
			iter=iter->next;
			yaz=yaz->next;
		}
		iter->next=(list*)malloc(sizeof(list));iter->next->node=sentor->node;iter->next->next=NULL;iter=iter->next;
		sentor=sentor->next;
	}
	
	
	
		list *del,*del2;
			for(int k=0;k<sizeB;k++){//free 
			del=L;
			del2=L->next;
			free(del);
			L=del2;
			}
			
	}

	forloop=forloopAfter;
	return L;
}
node  *input(node *root){//input function
	char control;
	int key;
	printf("Please enter numbers : ");
	do{
		scanf("%d%c",&key,&control);
		root=insert(root,key);
		size++;
	}while(control != '\n');
	
	return root;
}
list *left_right(list *LR,node *root,char c){ //create a list root and left child or root and right child. So, send in print(){} function this lists.
	
	if(root==NULL){
		printf("You don't have root");return NULL;
	}
	if(c=='L'){
		
		if(root->left!=NULL){
			LR=(list*)malloc(sizeof(list));
			LR->node=root;
			LR->next=(list*)malloc(sizeof(list));
			LR->next->node=root->left;
			LR->next->next=NULL;
			return LR;
		}else return LR;
		
	}else{
		if(root->right!=NULL){
			LR=(list*)malloc(sizeof(list));
			LR->node=root;
			LR->next=(list*)malloc(sizeof(list));
			LR->next->node=root->right;
			LR->next->next=NULL; 
			return LR;
		}else return LR;
	}
	
}
void printTreeC(struct node *root, int space) { //print tree function

    if (root == NULL) 
        return; 
    space += treeSpace; 
    printTreeC(root->right, space); 
    printf("\n"); 
    for (int j = treeSpace; j < space; j++) printf(" "); 
    printf("%d\n", root->data); 
    printTreeC(root->left, space); 
} 
  
void printTree(struct node *root) { 
	printTreeC(root, 0); 
} 
int main(){
	
  		node *root=NULL;
  		root=input(root);
  		list *L;
  		list *R;
		int total=1;
		if(root->left==NULL&&root->right==NULL){
			printf("You have 1 node and this is: %d",root->data);
			printf("\n Total count of sequence : 1");
		}else{
			
			L=NULL;
			R=NULL;
	  		L=left_right(L,root,'L');//root and left child
	  		R=left_right(R,root,'R');//root and right child
	  		
			  if(L!=NULL){
			  	
	  			for(int k=sizeB;k<size;k++){ //for left sequences
					L=print(L);
					sizeB++;
				}
	
				while(L!=NULL){ //print left sequences
					printf("%d :",total);total++;
					for(int k=0;k<size;k++){
						printf("%d ",L->node->data);L=L->next;
					}printf("\n");
				}
			  }
			  
			
			sizeB=2;
			forloop=1;
			if(R!=NULL){
				for(int k=sizeB;k<size;k++){ //for right sequences
				R=print(R);
				sizeB++;
			}
				
			while(R!=NULL){//print right sequences
				printf("%d :",total);total++;
				for(int k=0;k<size;k++){
					printf("%d ",R->node->data);R=R->next;
				}printf("\n");
			}
			}
			
			printf("\n Total count of sequence : %d",total-1);
		}
	printf("\n\n\n Tree:");
	printTree(root);//call printTree function for write a tree
			
	return 0;
}

