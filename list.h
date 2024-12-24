#ifndef LIST_H_
#define LIST_H_
#include<stdio.h>
#include<stdlib.h>

typedef struct list{
	int* list;
	int size;
	int len;
}List;

List* create_list(int lim);
void delete_list(List* list);
int push_back_list(List* list,int num);
void print_list(List list);

#endif