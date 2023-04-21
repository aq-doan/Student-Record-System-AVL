#include <stdlib.h>
#include <stdio.h>
#include "avlTree.h"

//function to create a new avl
AVL new_avl() {
	AVL temp;
	temp.root = NULL;
	return temp;
}

//function to find the max value
int max_value(int left, int right) {
	return(left > right) ? left : right;
}

NodePtr calculate_branch_min(NodePtr self) {
	if (self == NULL) {
		return NULL;
	}
	while (self->left != NULL) {
		self = self->left;
	}
	return self;
}

int get_tree_height(NodePtr self) {
	//variable for the left and right height of avl (initialise to 0)
	int l = 0;
	int r = 0;

	if (self == NULL) {
		return -1;
	}
	else {
		r = get_tree_height(self->right);
		l = get_tree_height(self->left);
		return max_value(l, r) + 1;
	}

}



int balance_tree(NodePtr self) {
	//get the height for both side of the AVL 
	int left_height = get_tree_height(self->left);
	int right_height = get_tree_height(self->right);
	//for the case that the tree is null
	if (self == NULL) {
		return 0;
	}
	else {
		return left_height - right_height;
	}
}


NodePtr rotation_r(NodePtr self) {
	NodePtr new_root = self->left;

	self->left = new_root->right;

	new_root->right = self;

	self->height = max_value(get_tree_height(self->left), get_tree_height(self->right)) + 1;
	new_root->height = max_value(get_tree_height(new_root->left), get_tree_height(new_root->right)) + 1;

	return new_root;
}


NodePtr rotation_l(NodePtr self) {
	NodePtr new_root = self->right;

	self->right = new_root->left;

	new_root->left = self;

	self->height = max_value(get_tree_height(self->left), get_tree_height(self->right)) + 1;
	new_root->height = max_value(get_tree_height(new_root->left), get_tree_height(new_root->right)) + 1;


	return new_root;
}


//function to rebalance the avl based on rebalance factor
NodePtr rebalance_avl(NodePtr self, int data) {
	int count;
	self->height = max_value(get_tree_height(self->left), get_tree_height(self->right)) + 1;
	count = balance_tree(self);

	if (count > 1) {
		if (get_tree_height(self->left->left) >= get_tree_height(self->left->right)) {
			self = rotation_r(self);
		}
		else {
			self->left = rotation_l(self->left);
			self = rotation_r(self);
		}
	}
	else if (count < -1) {
		if (get_tree_height(self->right->right) >= get_tree_height(self->right->left)) {
			self = rotation_l(self);
		}
		else {
			self->right = rotation_r(self->right);
			self = rotation_l(self);
		}
	}

	return self;
}

//insert a node into the tree
/*
* This function was created with reference to ChatGPT https://chat.openai.com/
* Where the generated verion was using while-loop
* NodePtr in_node_tree(NodePtr self, int data) {
	if (self == NULL) {
		self = malloc(sizeof(*self));
		self->id = data;
		self->height = 1;
		self->left = self->right = NULL;
		return self;
	}

	NodePtr curr = self;
	while (1) {
		if (data < curr->id) {
			if (curr->left == NULL) {
				curr->left = malloc(sizeof(*curr->left));
				curr->left->id = data;
				curr->left->height = 1;
				curr->left->left = curr->left->right = NULL;
				break;
			}
			curr = curr->left;
		} else if (data > curr->id) {
			if (curr->right == NULL) {
				curr->right = malloc(sizeof(*curr->right));
				curr->right->id = data;
				curr->right->height = 1;
				curr->right->left = curr->right->right = NULL;
				break;
			}
			curr = curr->right;
		} else {
			break; // value already exists in the tree
		}
	}

	return rebalance_avl(self, data);
}

*/
NodePtr in_node_tree(NodePtr self, int data) {
	if (self == NULL) {
		self = malloc(sizeof * self);
		self->id = data;
		self->height = 1;
		self->left = self->right = NULL;
		return self;
	}
	if (data < self->id) {
		self->left = in_node_tree(self->left, data);
	}
	else if (data > self->id) {
		self->right = in_node_tree(self->right, data);
	}
	else {
		return self;
	}

	self->height = max_value(get_tree_height(self->left), get_tree_height(self->right)) + 1;

	//check balance
	int balance = balance_tree(self);

	//will need to examine left-left, left-right, right-right and right-left cases
	if (balance > 1 && data < self->left->id) {
		return rotation_r(self);
	}

	if (balance < -1 && data > self->right->id) {
		return rotation_l(self);
	}

	if (balance > 1 && data > self->left->id) {
		self->left = rotation_l(self->left);
		return rotation_r(self);
	}

	if (balance < -1 && data < self->right->id) {
		self->right = rotation_r(self->right);
		return rotation_l(self);
	}

	return self;
}


//recursive function
void tree_in(AVL* self, int data) {
	self->root = in_node_tree(self->root, data);
}



//count number of node in avl
int count_avl_node(NodePtr self) {
	if (self == NULL) {
		return 0;
	}
	else {
		return 1 + count_avl_node(self->left) + count_avl_node(self->right);
	}

}

int count_avl(AVL* self) {
	return count_avl_node(self->root);
}

//destroy
void destroy_tree_node(NodePtr self) {

	if (self != NULL) {
		destroy_tree_node(self->left);
		destroy_tree_node(self->right);

		free(self);
	}
}

//destroy avl
void tree_destroy(AVL* self) {
	destroy_tree_node(self->root);
}

NodePtr search_avl_node(NodePtr self, int data) {
	return (self == NULL || data == self->id) ? self :
		(data < self->id) ? search_avl_node(self->left, data) :
		search_avl_node(self->right, data);
}


NodePtr tree_search(AVL* self, int data) {
	return search_avl_node(self->root, data);
}

//function to delete a node in avl
NodePtr delete_node(NodePtr self, int value) {
	NodePtr successor = NULL;
	if (self == NULL) {
		return NULL;
	}

	if (self->id == value) {
		if (self->left != NULL && self->right != NULL) {
			successor = calculate_branch_min(self->right);
			self->id = successor->id;
			self->right = delete_node(self->right, self->id);
		}
		else {
			self = self->left ? self->left : self->right;
			free(self->left ? self->left : self->right);
		}
	}
	else if (value < self->id) {
		self->left = delete_node(self->left, value);
	}
	else {
		self->right = delete_node(self->right, value);
	}

	return self;
}

//function to delete a node in avl
void tree_delete(AVL* self, int value) {
	self->root = delete_node(self->root, value);
}


//print tree in in-order
//This function is the adapted version of print bst provided by tutorial from KIT205 UTAS
void print_order_avl_node(NodePtr self) {
	if (self != NULL) {
		print_order_avl_node(self->left);
		printf("%d\n", self->id);
		print_order_avl_node(self->right);
	}
}
//print tree in in-order
void print_tree(AVL* self) {
	print_order_avl_node(self->root);
}