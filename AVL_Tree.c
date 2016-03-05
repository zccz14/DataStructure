//Root_of_AVL_Tree.c

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define REPEATTIME 100

typedef struct _atreenode{
	struct _atreenode *left, *right;
	int val, h;
}ANode;

// return the height of the current node pointer cnode
// height for empty pointer is -1
int AVL_H(ANode* cnode);

// update the height of the current node and return 1 for height changed , 0 for not
int AVL_updateh(ANode* cnode);

// make an RR rotation and return root node after rotation
ANode* rrrotate(ANode* cnode);

// make an RL rotation and return root node after rotation
ANode* rlrotate(ANode* cnode);

// make an LR rotation and return root node after rotation
ANode* lrrotate(ANode* cnode);

// make an LL rotation and return root node after rotation
ANode* llrotate(ANode* cnode);

// cauculate BF and make a rotation if need
// call updateh() at last
ANode* AVL_adjust(ANode* cnode, int *isrotated, int *isupdated);

// recursively insert a node num and return root node
ANode* AVL_insert(ANode* cnode, int num);

// delete a node num and return root node
ANode* AVL_delte(ANode* tree, int num);

// return the certain pointer to node with value num, if it doesn't exist return NULL;
ANode* AVL_find(ANode* tree, int num);

// function for test
int AVL_isbalance(ANode* tree);

int main(){
	
	int N, num, i, j, isrotated;
	ANode* tree = 0;
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
			tree = AVL_insert(tree, in[i]);
		}	
		//printf("%d\n", AVL_isbalance(tree));
		for(i = 0; i < N; i++){
			tree = AVL_delte(tree, out[i]);
		}	
	}
	stop = clock();
	
	duration = ((double)(stop - start));
	printf("repeat %d times, finished in %lf ms\n", REPEATTIME, duration);
	return 0;
	
}

int AVL_isbalance(ANode* tree){
	if(!tree) return 1;
	int min = AVL_H(tree->left) - AVL_H(tree->right);
	return  min < 2 && min > -2 && AVL_isbalance(tree->left) && AVL_isbalance(tree->right); 
}

int AVL_H(ANode* cnode){
	int res;
	if(cnode){
		res = cnode->h;
	}else{
		res = -1;
	}
	return res;
}

int AVL_updateh(ANode* cnode){
	int lh, rh, th;
	lh = AVL_H(cnode->left);
	rh = AVL_H(cnode->right);
	th = lh > rh ? lh + 1 : rh + 1;
	if(cnode->h != th){
		cnode->h = th;
		///*FOR DEBUG*/printf("%d's h updated as %d\n", cnode->val, th);
		return 1;
	}
	return 0;
}

ANode* rrrotate(ANode* cnode){
	ANode* R = cnode->right;
	ANode* B = R->left;
	
	R->left = cnode;
	cnode->right = B;
	
	// as we may apply rotations both in insertion and deletion we have to update concerning nodes after each rotation
	// same as other rotations
	AVL_updateh(cnode);
	AVL_updateh(R);
	
	return R;
	
}

ANode* rlrotate(ANode* cnode){
	ANode* R = cnode->right;
	ANode* RL = cnode->right->left;
	ANode* B = RL->left;
	ANode* C = RL->right;
	
	RL->left = cnode;
	RL->right = R;
	cnode->right = B;
	R->left = C;
	
	AVL_updateh(cnode);
	AVL_updateh(R);
	AVL_updateh(RL);
	
	return RL;
}

ANode* lrrotate(ANode* cnode){
	ANode* L = cnode->left;
	ANode* LR = cnode->left->right;
	ANode* B = LR->left;
	ANode* C = LR->right;
	
	LR->left = L;
	LR->right = cnode;
	L->right = B;
	cnode->left = C;
	
	//L->h -= 1;
	//cnode->h -= 2;
	//LR->h += 1;
	
	AVL_updateh(cnode);
	AVL_updateh(L);
	AVL_updateh(LR);
	
	return LR;
}

ANode* llrotate(ANode* cnode){
	ANode* L = cnode->left;
	ANode* B = L->right;
	L->right = cnode;
	cnode->left = B;

	AVL_updateh(cnode);
	AVL_updateh(L);
	
	return L;
}

ANode* AVL_adjust(ANode* cnode, int *isrotated, int *isupdated){
	if(!cnode){
		return 0;
	}
	//isrotated will be set 1 if an rotation happens
	//isupdated will be set 1 if h of tree changes, 0 if not 
	
	//judge whether to rotate and which rotation to apply
	if(AVL_H(cnode->left) - AVL_H(cnode->right) == 2){
		///*FOR DEBUG*/printf("trouble L caught at %d\n", cnode->val);
		if(AVL_H(cnode->left->left) >= AVL_H(cnode->left->right)){
			*isrotated = 1;
			cnode = llrotate(cnode);
		}else{
			*isrotated = 1;
			cnode = lrrotate(cnode);
		}
	}else if(AVL_H(cnode->left) - AVL_H(cnode->right) == -2){
		///*FOR DEBUG*/printf("trouble R caught at %d\n", cnode->val);
		if(AVL_H(cnode->right->left) > AVL_H(cnode->right->right)){
			*isrotated = 1;
			cnode = rlrotate(cnode);
		}else{
			*isrotated = 1;
			cnode = rrrotate(cnode);
		}
	}else{
		//update the height after if no rotation(as h will be updated during a rotation)
		*isupdated = AVL_updateh(cnode);
	}
	
	
	
	return cnode;
}

ANode* AVL_insert(ANode* tree, int num){
	static int isupdated = 1, isrotated = 0;
	isrotated = 0;
	ANode* cnode;
	
	// if an empty place is reached, we find the proper positon
	if(!tree) {
		cnode = (ANode*)malloc(sizeof(ANode));
		cnode->val = num;
		cnode->left = cnode->right = 0;
		cnode->h = 0;
		return cnode;
	};
	
	///*FOR DEBUG*/printf("%d finding pass %d\n", num, tree->val);
	
	//find down the positon 
	if(num < tree->val ){
		tree->left = AVL_insert(tree->left, num);
	}else{
		tree->right = AVL_insert(tree->right, num);
	}
		// for each insertion, we only rotate for at most once  
		// if h isn't updated, of course we don't need to rotate 	
	if(!isrotated && isupdated){
		tree = AVL_adjust(tree, &isrotated, &isupdated);
	}
	return tree;
	
}

ANode* AVL_find(ANode* tree, int num){
	if(!tree) return 0;
	if(tree->val == num){
		return tree;
	}else if( num < tree->val ){
		return AVL_find(tree->left, num);
	}else if( num > tree->val ){
		return AVL_find(tree->right, num);
	}
}

ANode* AVL_delte(ANode* tree, int num){
	static int isupdated = 1, isrotated = 0;
	isupdated = 1;
	ANode *i, *j;
	int t;
	if(!tree) {
		printf("delete %d failed\n", num);
		return 0;	
	}
	
	///*FOR DEBUG*/printf("%d deleting pass %d\n", num, tree->val);
	
	// find down the node
	if(num < tree->val ){
		tree->left = AVL_delte(tree->left, num);
	}else if(num > tree->val){
		tree->right = AVL_delte(tree->right, num);
	}else{
		// here the node is found, we check if it is a leaf.
		// if do, just delete it. 
		// if not, when left subtree is deeper, we find the biggest node in the left subtree and transpose it with the current node, then recursively AVL_delte it
		// when right subtree is deeper, we find the smallest node in the right subtree, then do the same thing.
		if(AVL_H(tree->left) == -1 && AVL_H(tree->right) == -1){
			free(tree);
			tree = 0;
		}else if(AVL_H(tree->left) < AVL_H(tree->right)){
			for(i = tree->right, j = i; i->left; j = i, i = i->left){
			}
			// find down the left subtree
			// here i is the biggest node 
			// if i is just tree->right, j = i;
			// otherwise j is the father of i
			
			//make transpositon
			t = tree->val;
			tree->val = i->val;
			i->val = t;
			
			if(j == i){
				tree->right = AVL_delte(i, num);
			}else{
				j->left = AVL_delte(i, num);
			}
		}else{
			// find down the right subtree
			// same as the left one
			for(i = tree->left, j = i; i->right; j = i, i = i->right){
			}
			t = tree->val;
			tree->val = i->val;
			i->val = t;
			if(j == i){
				tree->left = AVL_delte(i, num);
			}else{
				j->right = AVL_delte(i, num);
			}
		}
	}
	if(isupdated){
		// if h isn't updated, of course we don't need to rotate 
		tree = AVL_adjust(tree, &isrotated, &isupdated);
	}
	
	
	return tree;
}

