#ifndef TREE_ANALYSIS
#define TREE_ANALYSIS
#include"binary_tree.h"

void analyze_all_tree_hight(Tree* trees);
void analyze_AVL_tree_hight(Tree* trees);
void analyze_complete_binary_tree_hight(Tree* trees);
void report_trees(const char* file_name);
#endif