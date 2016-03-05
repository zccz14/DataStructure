//Splay_Tree.c

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define REPEATTIME 100

typedef struct _streenode{
	struct _streenode *left, *right;
	int val;
}SNode;

// zig rotation of the left subtree, return root node after rotation
SNode* lzig(SNode* cnode);

// zig rotation of the right subtree, return root node after rotation
SNode* rzig(SNode* cnode);

// zigzig operation of the left subtree, return root node after operation
SNode* lzigzig(SNode* cnode);

// zigzag rotation of the left subtree, return root node after rotation
SNode* lzigzag(SNode* cnode);

// zigzig operation of the right subtree, return root node after operation
SNode* rzigzig(SNode* cnode);

// zigzag rotation of the right subtree, return root node after rotation
SNode* rzigzag(SNode* cnode);

// judge which operation to adopt to make node num up
SNode* Splay_adjust(SNode* tree, int num, int isroot);

// return the certain pointer to node with value num, if it doesn't exist return NULL;
SNode* Splay_find(SNode* tree, int num);

// recursively insert a node num 
// during the return call adjust() to rotate node num up to the root
// return root node
SNode* Splay_insert(SNode* tree, int num);

// delete node tree and recursively delete down 
SNode* Splay_del(SNode* tree);

// call Splay_find() to find the node num 
// then call Splay_del() to delete it
SNode* Splay_delte(SNode *tree, int num);

int showtree(SNode* tree){
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
	
	int N, num, i, j;
	SNode* tree = 0;
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
			tree = Splay_insert(tree, in[i]);
		}
		//showtree(tree);
		for(i = 0; i < N; i++){
			tree = Splay_delte(tree, out[i]);
		}
	}
	stop = clock();
	
	duration = ((double)(stop - start));
	printf("repeat %d times, finished in %lf ms\n", REPEATTIME, duration);
	return 0;

}

SNode* rzig(SNode* cnode){
	SNode* R = cnode->right;
	SNode* B = R->left;
	
	R->left = cnode;
	cnode->right = B;
	
	return R;	
}

SNode* lzig(SNode* cnode){
	SNode* L = cnode->left;
	SNode* B = L->right;
	L->right = cnode;
	cnode->left = B;
	
	return L;
}

SNode* lzigzig(SNode* cnode){
	SNode* P = cnode->left;
	SNode* X = P->left;
	SNode* B = X->right;
	SNode* C = P->right;
	
	X->right = P;
	P->left = B;
	P->right = cnode;
	cnode->left = C;
	
	return X; 
}

SNode* rzigzig(SNode* cnode){
	SNode* P = cnode->right;
	SNode* X = P->right;
	SNode* B = P->left;
	SNode* C = X->left;
	
	X->left = P;
	P->right = C;
	P->left = cnode;
	cnode->right = B;
	
	return X; 
}

SNode* lzigzag(SNode* cnode){
	SNode* L = cnode->left;
	SNode* LR = cnode->left->right;
	SNode* B = LR->left;
	SNode* C = LR->right;
	
	LR->left = L;
	LR->right = cnode;
	L->right = B;
	cnode->left = C;
	
	return LR;
}

SNode* rzigzag(SNode* cnode){
	SNode* R = cnode->right;
	SNode* RL = cnode->right->left;
	SNode* B = RL->left;
	SNode* C = RL->right;
	
	RL->left = cnode;
	RL->right = R;
	cnode->right = B;
	R->left = C;
	
	return RL;
}

SNode* Splay_adjust(SNode* tree, int num, int isroot){
	if(!tree) return 0;
	
	// for root node check whether to apply zip
	if(isroot){
		if(tree->left && tree->left->val == num){
			return lzig(tree);
		}else if(tree->right && tree->right->val == num){
			return rzig(tree);
		}
	}
	
	//find the node num and judge which rotate to adopt(zigzag or zigzig)
	if(tree->left){
		if(tree->left->left && tree->left->left->val == num){
			///*FOR DEBUG*/printf("%d's 'lzigzig at %d\n", num, tree->val);
			return lzigzig(tree);
		}else if(tree->left->right && tree->left->right->val == num){
			///*FOR DEBUG*/printf("%d's 'lzigzag at %d\n", num, tree->val);
			return lzigzag(tree);
		}
	}
	if(tree->right){
		if(tree->right->right && tree->right->right->val == num){
			///*FOR DEBUG*/printf("%d's 'rzigzig at %d\n", num, tree->val);
			return rzigzig(tree);
		}else if(tree->right->left && tree->right->left->val == num){
			///*FOR DEBUG*/printf("%d's 'rzigzag at %d\n", num, tree->val);
			return rzigzag(tree);
		}
	}
	return tree;
}

SNode* Splay_find(SNode* tree, int num){
	// use degree to record how deep we are in order to judge whether tree is the root
	// tree is the root when degree == 0
	static int degree = -1;
	SNode* cnode;
	if(!tree) {
		return 0;
	};
	///*FOR DEBUG*/printf("%d finding pass %d\n", num, tree->val);
	degree++;
	// find down the positon 
	if(num < tree->val ){
		tree->left = Splay_find(tree->left, num);
	}else if(num > tree->val){
		tree->right = Splay_find(tree->right, num);
	}
	// if the node num is found, we just return, as we will rotate it up in ancestor nodes.
	
	// rotate it up after found
	tree = Splay_adjust(tree, num, !degree);
	degree--;
	return tree;
}



SNode* Splay_insert(SNode* tree, int num){
	// use degree to record how deep we are in order to judge whether tree is the root
	// tree is the root when degree == 0
	static int degree = -1;
	SNode* cnode;
	if(!tree) {
		cnode = (SNode*)malloc(sizeof(SNode));
		cnode->val = num;
		cnode->left = cnode->right = 0;
		return cnode;
	};
	degree++;
	///*FOR DEBUG*/printf("%d finding pass %d\n", num, tree->val);
	// find down the positon 
	if(num < tree->val ){
		tree->left = Splay_insert(tree->left, num);
	}else if(num > tree->val){
		tree->right = Splay_insert(tree->right, num);
	}
	// if the node num is found, we just return, as we will rotate it up in ancestor nodes.
	
	// rotate it up after found/inserted
	tree = Splay_adjust(tree, num, !degree);
	degree--;
	return tree;
}

SNode* Splay_delte(SNode* tree, int num){
	tree = Splay_find(tree, num);
	return Splay_del(tree);
}

SNode* Splay_del(SNode* tree){
	SNode *tnode;
	
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
	
	SNode *i, *j;
	int t;
	static dir = 1;
	
	//we use dir to control which subtree to delete down, after each calling make the direction inversed to make the tree more balanced
	dir = -dir;

	if(dir>0){
		// find the smallest node in the right subtree and transpose it with the current node, then recursively Splay_del it
		for(i = tree->right, j = i; i->left; j = i, i = i->left){
		}
		t = tree->val;
		tree->val = i->val;
		i->val = t;
		if(j == i){
			tree->right = Splay_del(i);
		}else{
			j->left = Splay_del(i);
		}
	}else{
		// find the biggest node in the left subtree and transpose it with the current node, then recursively Splay_del it
		for(i = tree->left, j = i; i->right; j = i, i = i->right){
		}
		t = tree->val;
		tree->val = i->val;
		i->val = t;
		if(j == i){
			tree->left = Splay_del(i);
		}else{
			j->right = Splay_del(i);
		}
	}
	return tree;
}
