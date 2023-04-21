/*
* NOTE: This file is an adaptation of the learning material of the University of Tasmania
* KIT205, produced by Robert Ollington
* The intial code can be found in the following page
* https://mylo.utas.edu.au/d2l/le/content/566489/viewContent/4972074/View
* This version is modified by Anh Quan Doan for the first Assignment of KIT205
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linkedlist.h"



List create_list() {
	List temp;
	temp.head = NULL;
	return temp;
}



//function to insert a node into a list in in-order format (alphabetical order)
void insert_list(List* self, String data) {
	ListNodePtr list = self->head;
	ListNodePtr p = NULL; //previous list
	int length_string = strlen(data) + 1;

	ListNodePtr new_node = malloc(sizeof * new_node);
	new_node->unit_name = malloc(length_string * sizeof(String));

	strcpy(new_node->unit_name, data);

	new_node->student_in_unit.root = NULL;

	new_node->next = NULL;

	while (list != NULL && strcmp(list->unit_name, data) < 0) {
		p = list;
		list = list->next;
	}

	if (list == self->head) {
		new_node->next = list;
		self->head = new_node;
	}
	else {
		new_node->next = list;
		p->next = new_node;
	}
}

//find list by traversing
ListNodePtr find_list(List* self, String target) {
	ListNodePtr current = self->head;
	while (current != NULL)
	{
		int compare = strcmp(current->unit_name, target);
		if (compare == 0)
		{
			return current;
		}
		else
		{
			current = current->next;
		}
	}
	return NULL;
}


//delete a node by traversing 
void delete_list(List* self, String data) {
	ListNodePtr list = self->head;
	ListNodePtr p = NULL;

	if (self->head == NULL) {
		return;
	}

	while (list != NULL) {
		int compare = strcmp(list->unit_name, data);
		if (compare == 0) {
			if (p == NULL) {
				self->head = list->next;

				tree_destroy(&list->student_in_unit);
				free(list->unit_name);
				list->unit_name = NULL;

				free(list);
				list = self->head;
			}
			else {
				p->next = list->next;

				tree_destroy(&list->student_in_unit);
				free(list->unit_name);
				list->unit_name = NULL;
				free(list);

				list = p->next;
			}
		}
		else {
			p = list;
			list = list->next;
		}
	}
}

//free memory
void destroy_list(List* self) {
	ListNodePtr list_node = self->head;
	while (list_node != NULL) {
		ListNodePtr n = list_node;
		list_node = list_node->next;

		tree_destroy(&n->student_in_unit); //free in list of students
		free(n->unit_name);// free the unit
		free(n);
	}
	self->head = NULL; //empty the list
}
