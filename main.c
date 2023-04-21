#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include "linkedlist.h"
#include "avlTree.h"
/*
* NOTE: This file is an adaptation of the learning material of the University of Tasmania
* KIT205, produced by Robert Ollington
* The intial code can be found in the following page
* https://mylo.utas.edu.au/d2l/le/content/566489/viewContent/4972074/View
* This version is modified by Anh Quan Doan for the first Assignment of KIT205
*/

#define LOWER_SELECTION 0
#define HIGHER_SELECTION 7

//ask the student id
int ask_id() {
	int id_main;
	printf("Enter student id:\n");
	scanf("%ld", &id_main);
	return id_main;
}

//ask the unit name
char* ask_unit() {
	char range[100];

	printf("Enter course:\n");
	scanf("%s", range);
	int string_len = strlen(range) + 1;

	String unit_main = malloc(sizeof(char) * string_len);
	strcpy(unit_main, range);

	return unit_main;
}

void menu(List* self, int input) {
	String unit_add = NULL;
	int id_add = NULL;
	ListNodePtr temp;
	String unenrol_unit;
	int unenrol_id;
	String summary_unit;
	int count;
	ListNodePtr node_summary;
	String unit_specific;
	int student_enrolled_unit;
	ListNodePtr node_current;
	switch (input) {
	case 1:
		id_add = ask_id();
		unit_add = ask_unit();
		if (find_list(self, unit_add) == NULL) {
			insert_list(self, unit_add);
		}
		tree_in(&find_list(self, unit_add)->student_in_unit, id_add);
		break;
	case 2:
		unenrol_id = ask_id();
		unenrol_unit = ask_unit();
		tree_delete(&find_list(self, unenrol_unit)->student_in_unit, unenrol_id);
		break;


	case 3:
		unit_specific = ask_unit();

		print_tree(&find_list(self, unit_specific)->student_in_unit);
		break;

	case 4:
		student_enrolled_unit = ask_id();
		node_current = self->head;
		while (node_current != NULL)
		{
			if (tree_search(&node_current->student_in_unit, student_enrolled_unit))
			{
				printf("%s\n", node_current->unit_name);
			}
			node_current = node_current->next;
		}
		break;
	case 5:

		node_summary = self->head;

		while (node_summary != NULL)
		{
			printf("%s %d\n", node_summary->unit_name, count_avl(&node_summary->student_in_unit));
			node_summary = node_summary->next;
		}
		break;
	}
}


void main() {
	List list_of_unit = create_list();
	int input;
	//display menu
	printf("\nPlease pick an option(1-5). if you want to to exit pick 0.\n");
	printf("1. Enrol a student in a unit\n2. Un-enrol a student from a unit\n");
	printf("3. Print an ordered list of students enrolled in a specific unit\n");
	printf("4. Print an ordered list of units that a specific student is enrolled in\n");
	printf("5. Print an ordered summary of all units and the number of students enrolled in each\n");
	printf("0. Quit the application\n");

	do {
		printf("\nEnter your option: ");
		scanf("%d", &input); //read input
		menu(&list_of_unit, input); //process the option
	} while (input != 0); //quit

	if (list_of_unit.head != NULL) {
		destroy_list(&list_of_unit);
	}

}

//test function for linkedlist functions
void test_linkedlist() {
	List list = create_list(); //test create_list()
	if (list.head == NULL) {
		printf("create_list() succcess\n");
	}
	else {
		printf("create_list() failed.\n");
	}

	// Test insert_list
	insert_list(&list, "KIT123");
	insert_list(&list, "KIT200");
	int compare = strcmp(&list.head->unit_name, "KIT123");
	int compare2 = strcmp(list.head->next->unit_name, "KIT200");
	//compare whether the input is equal to the expected 
	if (list.head != NULL && compare == 0 && compare2 == 0) {
		printf("insert_list() success.\n");
	}
	else {
		printf("insert_list() failed.\n");
	}

	// Test find_list function
	ListNodePtr current = find_list(&list, "KIT200");
	int compare3 = strcmp(current->unit_name, "KIT200");
	if (current != NULL && compare3 == 0) {
		printf("find_list success.\n");
	}
	else {
		printf("find_list failed.\n");
	}
	//for the case that the list does not have the subject
	current = find_list(&list, "12344");
	if (current == NULL) {
		printf("find_list success.\n");
	}
	else {
		printf("find_list failed.\n");
	}

	//test destroy
	destroy_list(&list);
	if (list.head == NULL) { //if the list is empty
		printf("destroy_list sucess.\n");
	}
	else {
		printf("destroy_list failed.\n");
	}
}
void test_avltree() {
	AVL tree = new_avl();

	//sample values
	tree_in(&tree, 5);
	tree_in(&tree, 3);
	tree_in(&tree, 7);
	tree_in(&tree, 1);
	tree_in(&tree, 4);
	tree_in(&tree, 6);
	tree_in(&tree, 9);

	// Test the search function
	if (tree_search(&tree, 4)) {
		printf("tree_search() success.\n");
	}
	else {
		printf("tree_search() failed.\n");
	}

	// Test count 
	if (count_avl(&tree) == 7) {
		printf("count_avl() success.\n");
	}
	else {
		printf("count_avl() failed.\n");
	}

	// Test print 
	printf("Expect 1 3 4 5 6 7 9\n");
	print_tree(&tree);

	//test calculate_branch_min and get_tree_height
	printf("Minimum value in AV:: %d\n", calculate_branch_min(tree));
	printf("Height AVL: %d\n", get_tree_height(tree));

	// Test delete 
	tree_delete(&tree, 5);
	printf("Expect 1 3 4 6 7 9\n");
	print_tree(&tree);

	tree_destroy(&tree);
	if (&tree == NULL) {
		printf("destroy_tree success.\n");
	}
	else {
		printf("destroy_tree failed.\n");
	}
}

