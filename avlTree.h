#pragma once
typedef struct tree_node_avl {
	int id;
	struct tree_node_avl* left;
	struct tree_node_avl* right;
	int height;
} *NodePtr;


typedef struct avl {
	NodePtr root;
} AVL;


AVL new_avl();


NodePtr tree_search(AVL* self, int value);


void tree_in(AVL* self, int value);

void tree_delete(AVL* self, int value);


void tree_destroy(AVL* self);

//in order
void print_tree(AVL* tree);

int count_avl(AVL* self);

