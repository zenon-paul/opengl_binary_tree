
#include"GL/freeglut.h"
#include"GLFW/glfw3.h"
#include"tree_graphic.h"
#include"position.h"
#include<stdio.h>
#include"charactor.h"


NodeGraphic* pNodeGraphic(void* p) {
    return  (NodeGraphic*)p;
}

void render_val(GLFWwindow* window, NodeGraphic node) {
    glfwMakeContextCurrent(window);//get window active
    char buf[10];
    snprintf(buf, 10, "%d", node.val);
    glColor3fv(node.char_color);
    glRasterPos2i(node.pos.x, node.pos.y);
    for (int i = 0; buf[i] != '\0'; i++) glutBitmapCharacter(UserFont, buf[i]);
}

void render_box(GLFWwindow* window, NodeGraphic node) {
    glfwMakeContextCurrent(window);//get window active
    
    int val_len = 1;
    int tmp = node.val;
    while (tmp / 10) {
        val_len++;
        tmp /= 10;
    }

    glBegin(GL_POLYGON);
    glColor3fv(node.box_color);
    glVertex2i(node.pos.x,node.pos.y);
    glVertex2i(node.pos.x,node.pos.y+ UserFontSizeH);
    glVertex2i(node.pos.x+UserFontSizeW*val_len,node.pos.y+UserFontSizeH);
    glVertex2i(node.pos.x+UserFontSizeW*val_len,node.pos.y);
    glEnd();
}

void render_edge(GLFWwindow* window,NodeGraphic a,NodeGraphic b) {
    glfwMakeContextCurrent(window);//get window active
    
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3fv(a.edge_color);
    glVertex2i(a.pos.x+UserFontSizeW/2,a.pos.y+UserFontSizeH/2);
    glColor3fv(b.edge_color);
    glVertex2i(b.pos.x+UserFontSizeW/2, b.pos.y+UserFontSizeH/2);
    glEnd();
}


void render_node(GLFWwindow* window,NodeGraphic node){
    glfwMakeContextCurrent(window);//get window active
    //render_box(window,node);
    render_val(window,node);
    glFlush();
}

void render_tree(GLFWwindow* window,Tree current,Tree parent) {
    if (current == NULL) return;
    render_tree(window,current->left,current);
    render_tree(window,current->right,current);

    render_edge(window, *pNodeGraphic(current->pointer), *pNodeGraphic(parent->pointer));
    render_node(window,*pNodeGraphic(current->pointer));

}

void update_tree_position(Tree root,int width,int hight) {
    //printf("<%d,%d>\n",pNodeGraphic(root->pointer)->pos.x, pNodeGraphic(root->pointer)->pos.y);
    if(root->left != NULL) {
        pNodeGraphic(root->left->pointer)->pos.x = -width + pNodeGraphic(root->pointer)->pos.x;
        pNodeGraphic(root->left->pointer)->pos.y = -hight + pNodeGraphic(root->pointer)->pos.y;
        //printf("<%d,%d>\n", pNodeGraphic(root->left->pointer)->pos.x, pNodeGraphic(root->left->pointer)->pos.y);
        update_tree_position(root->left, (int)(width / 2), hight);
    }
    if(root->right != NULL) {
        pNodeGraphic(root->right->pointer)->pos.x = width + pNodeGraphic(root->pointer)->pos.x;
        pNodeGraphic(root->right->pointer)->pos.y = -hight + pNodeGraphic(root->pointer)->pos.y;
        //printf("<%d,%d>\n", pNodeGraphic(root->right->pointer)->pos.x, pNodeGraphic(root->right->pointer)->pos.y);
        update_tree_position(root->right, (int)(width / 2), hight);
    }
}

int calculate_tree_min_width(Tree root, int min_dist) {
    int tree_hight = calculate_hight(root) - 1;
    int tree_width = 0;
    for (int i = 0; i < tree_hight; i++) tree_width = tree_width * 2 + min_dist;
    return tree_width + min_dist;
}

XYi set_tree_position(Tree root,int hight,int min_dist) {
    XYi tree_size;
    int tree_min_width = calculate_tree_min_width(root, min_dist);
    int tree_hight = calculate_hight(root) - 1;
    pNodeGraphic(root->pointer)->pos.x = 0;
    pNodeGraphic(root->pointer)->pos.y = 0;
    update_tree_position(root, tree_min_width / 4, hight);
    tree_size.x = tree_min_width;
    tree_size.y = hight * tree_hight;
    return tree_size;
}

void set_tree_color(Tree root, float* char_color, float* edge_color, float* box_color) {
    if (root == NULL) return;
    set_tree_color(root->left, char_color, edge_color, box_color);
    set_tree_color(root->right, char_color, edge_color, box_color);

    for (int i = 0; i < 3; i++) (pNodeGraphic(root->pointer)->char_color)[i] = char_color[i];
    for (int i = 0; i < 3; i++) (pNodeGraphic(root->pointer)->edge_color)[i] = edge_color[i];
    for (int i = 0; i < 3; i++) (pNodeGraphic(root->pointer)->box_color)[i] = box_color[i];
}


void initialize_graphical_tree(Tree root) {
    if (root == NULL) return;
    initialize_graphical_tree(root->left);
    initialize_graphical_tree(root->right);
    NodeGraphic* new_ = (NodeGraphic*)malloc(sizeof(NodeGraphic));
    root->pointer = (void*)new_;
}

void delete_graphical_tree(Tree root) {
    if (root == NULL) return;
    delete_graphical_tree(root->left);
    delete_graphical_tree(root->right);
    if (root->pointer == NULL) return;
    free(root->pointer);
}

void copy_key_on_graphic_val(Tree root) {
    if (root == NULL) return;
    copy_key_on_graphic_val(root->left);
    copy_key_on_graphic_val(root->right);
    if (root->pointer == NULL) return;
    pNodeGraphic(root->pointer)->val = root->key;
}
