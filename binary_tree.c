#include"binary_tree.h"
#include"list.h"
#include"utility.h"

//----------- tree ---------------------
Tree create_tree(int key){
    Tree new_ = (struct Node*)malloc(sizeof(struct Node));
	if (new_ == NULL) return NULL;

    new_->key = key;
    new_->left = NULL;
    new_->right = NULL;
	new_->pointer = NULL;

    return new_;
}

void delete_tree(Tree node){
    if(node != NULL){
        delete_tree(node->left);
        delete_tree(node->right);
        free(node);
    }
}

int count_children(Tree root){
	if (root == NULL) return 0;
	else return count_children(root->left) + count_children(root->right) + 1;
}

int calculate_hight(Tree root){
	if(root == NULL) return 0;
	return max_(calculate_hight(root->left),calculate_hight(root->right))+1;
}

int is_AVL_tree(Tree root) {
	int left_hight = calculate_hight(root->left);
	int right_hight = calculate_hight(root->right);
	int diff = left_hight - right_hight;
	if ((-1 <= diff) && (diff <= 1)) {
		int left = 1;
		int right = 1;
		if (root->left != NULL) left = is_AVL_tree(root->left);
		if (root->right != NULL) right = is_AVL_tree(root->right);
		if ((left == 1) && (right == 1)) return 1;
		else return 0;
	}
	else return 0;
}

int is_complete_binary_tree(Tree root) {
	int left_children_num = count_children(root->left);
	int right_children_num = count_children(root->right);
	int diff = left_children_num - right_children_num;
	if ((-1 <= diff) && (diff <= 1)) {
		int left = 1;
		int right = 1;
		if(root->left != NULL) left = is_complete_binary_tree(root->left);
		if(root->right != NULL) right = is_complete_binary_tree(root->right);
		if ((left == 1) && (right == 1)) return 1;
		else return 0;
	}
	else return 0;
}

void insert_node(Tree* root,Tree node){
    if(*root == NULL) {
		*root = node;
		return;
	}
    if(node->key <= (*root)->key) insert_node(&((*root)->left),node);
    else insert_node(&((*root)->right),node); 
}

static Tree extract_max(Tree root){
	if(root->right == NULL) return root; 
	else return extract_max(root->right);
}

static Tree extract_min(Tree root){
	if(root->left == NULL) return root;
	else return extract_min(root->left);
}

void delete_node_from_tree(Tree* root,int key){
    if(*root == NULL) return;
	if((*root)->key < key) delete_node_from_tree(&((*root)->left),key);  
	else if((*root)->key > key) delete_node_from_tree(&(*root)->left,key);
    else{
		if((*root)->left == NULL){
			*root = (*root)->right;
			free(*root);
			root = NULL;
		}
		else{
			Tree left_tree_max = extract_max((*root)->left);
			Tree tmp = left_tree_max->left;
			left_tree_max->left = (*root)->left;
			left_tree_max->right = (*root)->right;
			free(*root);
			*root = left_tree_max;
			((*root)->left)->right = tmp;
		}
	}
}

void search_pre(Tree root){
	if (root == NULL) return;
	printf("key:%d\n",root->key);
	search_pre(root->left);
	search_pre(root->right);
}

void search_pre_with_depth(Tree root,int depth){
	if (root == NULL) return;
	printf("key:%d d:%d\n",root->key,depth);
	search_pre_with_depth(root->left,depth+1);
	search_pre_with_depth(root->right,depth+1);
}

void search_middle(Tree root){
	if (root == NULL) return;
	search_middle(root->left);
	printf("key:%d\n",root->key);
	search_middle(root->right);
}

void search_post(Tree root){
	if (root == NULL) return;
	search_post(root->left);
	search_post(root->right);
	printf("key:%d\n",root->key);
}


void get_key_record(Tree root,List* list){
	if (root == NULL) return;
	push_back_list(list,root->key);
	get_key_record(root->left,list);
	get_key_record(root->right,list);
}

Tree* get_different_trees(int n) {
	int fact = factorial(n);
	int different_tree_num = 0;

	Tree* result = (Tree*)malloc(sizeof(Tree) * (fact + 1));
	if (result == NULL) return 0;
	for (int i = 0; i < (fact + 1); i++) result[i] = NULL;

	int **plist = (int**)malloc(sizeof(int*) * fact);
	if (plist == NULL) {
		free(result);
		return 0;
	}
	
	for (int i = 0; i < fact; i++) plist[i] = (int*)malloc(sizeof(int) * n);

	int* is_exist = (int*)calloc(fact,sizeof(int));
	if (is_exist == NULL) {
		free(result);
		for (int i = 0; i < fact; i++) free(plist[i]);
		free(plist);
		return 0;
	}

	set_permutation_list(plist, n);

	for (int i = 0; i < fact;i++) {
		Tree current = create_tree(plist[i][0]);
		Tree* current_p = &current;
		int current_id = 0;
		List* keyrecord = create_list(n);


		for (int j = 1; j < n; j++) insert_node(current_p, create_tree(plist[i][j]));

		get_key_record(current, keyrecord);
		current_id = permutation_num(keyrecord->list, keyrecord->len);

		delete_list(keyrecord);

		if (is_exist[current_id]) {
			free(current);
			continue;
		}
		else {
			is_exist[current_id] = 1;
			result[different_tree_num] = current;
			different_tree_num++;
		}
	}

	for (int i = 0; i < fact; i++) free(plist[i]);
	free(plist);
	free(is_exist);

	return result;
}