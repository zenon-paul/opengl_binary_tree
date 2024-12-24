#ifndef SIMULATION_GRAPHIC_H_
#define SIMULATION_GRAPHIC_H_
#include"binary_tree.h"
#include"tree_graphic.h"

#define WINDOW_HIGHT 800
#define WINDOW_WIDTH 800

extern Tree current_tree_on_display;
extern Tree* tree_list;

void glfwMainLoop();

void init_OpenGL(int argc, char** argv);

#endif