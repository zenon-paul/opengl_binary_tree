#ifndef TREE_GRAPHIC_H_
#define TREE_GRAPHIC_H_

#include"GL/freeglut.h"
#include"GLFW/glfw3.h"
#include"binary_tree.h"
#include"position.h"
#include"charactor.h"

#define TREE_POSITION_OFFSET_X 100
#define TREE_POSITION_OFFSET_Y 100

typedef struct node_graphic{
    XYi pos;
    float box_color[3];
    float char_color[3];
    float edge_color[3];
    int val;
}NodeGraphic;

typedef struct tree_graphic{
    Tree binary_tree;
    int edge_thin;
}TreeGraphic;

NodeGraphic* pNodeGraphic(void* p);

void render_node(GLFWwindow* window,NodeGraphic node);

void update_tree_position(Tree root, int width, int hight);

XYi set_tree_position(Tree root, int hight, int min_dist);

void set_tree_color(Tree root, float* char_color, float* edge_color, float* box_color);

void render_tree(GLFWwindow* window, Tree current, Tree parent);

void initialize_graphical_tree(Tree root);

void delete_graphical_tree(Tree root);

void copy_key_on_graphic_val(Tree root);

void print_pos(Tree root);

#endif