#include"list.h"
#include"utility.h"

//-------------list----------------
List* create_list(int lim){
	List* new_ = (List*)malloc(sizeof(List));
	if (new_ == NULL) return NULL;
	new_->list = (int*)calloc(sizeof(int),lim);
	if (new_->list == NULL) return NULL;
	new_->size = lim;
	new_->len = 0;
	return new_;
}

void delete_list(List* list){
	free(list->list);
	free(list);
}

int push_back_list(List* list,int num){
	if(list->size == list->len) return 0;
	list->list[list->len] = num;
	list->len += 1;
	return 1;
}

void print_list(List list){
	for(int i = 0;i<min_(list.size,list.len);i++)printf("%d ",list.list[i]);
	putchar('\n');
}