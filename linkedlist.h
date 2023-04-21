#pragma once

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

