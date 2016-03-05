#include<stdio.h>
#include"Binary_Search_Tree.h"
#include"Splay_Tree.h"
#include"AVL_Tree.h"


// function for test
int showtree(Node* tree){
	if(!tree) return;
	printf("%d ", tree->val);
	if(tree->left){
		printf("left ");
		showtree(tree->left);	
	}
	if(tree->right){
		printf("right ");
		showtree(tree->right);
	}
	printf("up ");
	return 0;
}

int main(){
	
}
