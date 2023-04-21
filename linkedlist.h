#pragma once
/*
* NOTE: This file is an adaptation of the learning material of the University of Tasmania
* KIT205, produced by Robert Ollington
* The intial code can be found in the following page
* https://mylo.utas.edu.au/d2l/le/content/566489/viewContent/4972074/View
* This version is modified by Anh Quan Doan for the first Assignment of KIT205
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include "avlTree.h"

typedef char* String;

typedef struct listNode {
	String unit_name;
	AVL student_in_unit;
	struct listNode* next;
} *ListNodePtr;

typedef struct list {
	ListNodePtr head;
} List;


List create_list();


void insert_list(List* self, String data);


ListNodePtr find_list(List* self, String data);


void delete_list(List* self, String data);


void destroy_list(List* self);

