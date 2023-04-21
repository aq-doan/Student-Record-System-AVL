#pragma once
/*
* NOTE: This file is an adaptation of the learning material of the University of Tasmania
* KIT205, produced by Robert Ollington
* The intial code can be found in the following page
* https://mylo.utas.edu.au/d2l/le/content/566489/viewContent/4972074/View
* This version is modified by Anh Quan Doan for the first Assignment of KIT205
*/
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

