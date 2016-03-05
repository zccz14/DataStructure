//Binary_Search_Tree.c

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define REPEATTIME 100



typedef struct _btreenode{
	struct _btreenode *left, *right;
	int val; 
}BNode;

// insert a node num and return root node
// tree can only be a root node( or there will be bugs )
BNode* BST_insert(BNode* tree, int num);

// delete a node num and return root node, it will find the proper node and call del() to delete it, if delete failed return 0;
BNode* BST_delte(BNode* tree, int num);

// return the certain pointer to node with value num, if it doesn't exist return NULL;
BNode* BST_find(BNode* tree, int num);

// delete node tree and recursively delete down
BNode* BST_del(BNode* tree);

int main(){
	int N, num, i, j;
	BNode* tree = 0;
	clock_t start, stop;
	double duration;
	
	scanf("%d", &N);
	int in[10001];
	int out[10001];
	
	for(i = 0; i < N; i++){
		scanf("%d", &in[i]);	
	}
	
	for(i = 0; i < N; i++){
		scanf("%d", &out[i]);	
	}
	
	start = clock();
	for(j = 0; j < REPEATTIME; j++){
		for(i = 0; i < N; i++){
			tree = BST_insert(tree, in[i]);
		}
		for(i = 0; i < N; i++){
			tree = BST_delte(tree, out[i]);
		}	
	}
	stop = clock();
	
	duration = ((double)(stop - start));
	printf("repeat %d times, finished in %lf ms\n", REPEATTIME, duration);
	return 0;
}

BNode* BST_insert(BNode* tree, int num){
	BNode *cnode, *t;

	// create cnode
	cnode = malloc(sizeof(BNode));
	cnode->val = num;
	cnode->left = cnode->right = 0;

	if(!tree){
		return cnode;
	}

	t = tree;
	
	// find the proper positon iteratively and insert cnode
	while(1){
		if(num < t->val){
			if(t->left){
				t = t->left;
			}else{
				t->left = cnode;
				break;
			}
		}else{
			if(t->right){
				t = t->right;
			}else{
				t->right = cnode;
				break;
			}
		}
	}
	return tree;
}

BNode* BST_delte(BNode* tree, int num){
	BNode *t, *i;
	if(!tree) return 0;
	if(tree->val == num) return BST_del(tree);
	
	// find the father of node num and delete num, as we have to update father of num after deletion
	i = tree;
	while(i){
		if(i->left && num == i->left->val){
			i->left = BST_del(i->left);
			return tree;
		}else if(i->right && num == i->right->val){
			i->right = BST_del(i->right);
			return tree;
		}else{
			if(num < i->val){
				i = i->left;
			}else{
				i = i->right;
			}
		}
	}
	return 0;
}

BNode* BST_del(BNode* tree){
	BNode *tnode;
	
	// if one of tree's children is NULL, we simple delete tree and return the other child( work even tree is a leaf)
	if(!tree){
		return 0;
	}else if(!tree->left){
		tnode = tree->right;
		free(tree);
		return tnode;
	}else if(!tree->right){
		tnode = tree->left;
		free(tree);
		return tnode;
	}
	
	BNode *i, *j;
	int t;
	static dir = 1;
	
	// notice that here both of tree's children exists
	// use dir to control which subtree to delete down, after each calling make the direction inversed to make the tree more balanced
	dir = -dir;

	if(dir>0){
		// find the smallest node in the right subtree and transpose it with the current node, then recursively Splay_del it
		for(i = tree->right, j = i; i->left; j = i, i = i->left){
		}
		t = tree->val;
		tree->val = i->val;
		i->val = t;
		if(j == i){
			tree->right = BST_del(i);
		}else{
			j->left = BST_del(i);
		}
	}else{
		// find the biggest node in the left subtree and transpose it with the current node, then recursively Splay_del it
		for(i = tree->left, j = i; i->right; j = i, i = i->right){
		}
		t = tree->val;
		tree->val = i->val;
		i->val = t;
		if(j == i){
			tree->left = BST_del(i);
		}else{
			j->right = BST_del(i);
		}
	}
	return tree;
}

BNode* BST_find(BNode* tree, int num){
	BNode* t = tree;
	
	//// find node num iteratively
	while(t){
		if(num < t->val){
			t = t->left;
		}else if(num > t->val){
			t = t->right;
		}else{
			break;
		}
	}
	return t;
}

