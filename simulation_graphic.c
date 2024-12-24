#include"GL/freeglut.h"
#include"GLFW/glfw3.h"
#include <stdio.h>
#include<stdlib.h>
#include"list.h"
#include"binary_tree.h"
#include"utility.h"
#include"tree_analysis.h"
#include"tree_graphic.h"
#include"simulation_graphic.h"
#include"tree_graphic.h"

GLFWwindow* window1;
GLFWwindow* window2;

int window_hight = WINDOW_HIGHT;
int window_width = WINDOW_WIDTH;

int window2_origin_x = 0;
int window2_origin_y = 0;
int window2_box_x = WINDOW_HIGHT;
int window2_box_y = WINDOW_WIDTH;

Tree* tree_list;
Tree current_tree_on_display;

int current_tree = -1;

void update_current_tree_on_display(GLFWwindow* window, Tree root) {
	current_tree_on_display = root;
	float char_color[3] = { 0.0,0.0,0.0 };
	float edge_color[3] = { 0.8,0.8,0.8 };
	float box_color[3] = { 1.0,1.0,1.0 };

	if (is_AVL_tree(root)) {
		char_color[0] = 0.0;
		char_color[1] = 0.0;
		char_color[2] = 0.7;
	}
	if (is_complete_binary_tree(root)) {
		char_color[0] = 0.7;
		char_color[1] = 0.0;
		char_color[2] = 0.0;
	}

	initialize_graphical_tree(current_tree_on_display);
	copy_key_on_graphic_val(current_tree_on_display);
	XYi tree_size = set_tree_position(current_tree_on_display, 100, 16);
	set_tree_color(current_tree_on_display, char_color, edge_color, box_color);

	window2_origin_x = -TREE_POSITION_OFFSET_X - tree_size.x / 2;
	window2_origin_y = -TREE_POSITION_OFFSET_Y -tree_size.y;

	window2_box_x = tree_size.x / 2 + TREE_POSITION_OFFSET_X;
	window2_box_y = tree_size.y + TREE_POSITION_OFFSET_Y;
}

Tree* generate_trees() {
	int num;
	printf("Permutation Generator: input a number> ");
	do {} while (scanf("%d", &num) != 1);
	Tree* trees = get_different_trees(num);

	analyze_all_tree_hight(trees);
	analyze_AVL_tree_hight(trees);
	analyze_complete_binary_tree_hight(trees);

	return trees;
}


void render1(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)w, 0.0, (double)h);
	window_hight = h;
	window_width = w;

	glClearColor(0.0, 0.21, 0.38, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}

void render2(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(window2_origin_x, (double)(-window2_origin_x), window2_origin_y, (double)(100));
	

	glClearColor(0.5, 0.5, 0.5, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);

	render_tree(window2, current_tree_on_display, current_tree_on_display);

	glFlush();
}

void mouse_callback(GLFWwindow* pwin, int button, int action, int mods) {
	if (action != GLFW_PRESS) {
		return;
	}

	if (current_tree == -1) {
		printf("click display_window\n");
		tree_list = generate_trees();
		current_tree = 0;
		return;
	}
	

	if (pwin == window2) {
		if (tree_list[current_tree] == NULL) {
			for (int i = 0; tree_list[i] != NULL; i++) delete_tree(tree_list[i]);
			free(tree_list);
			printf("click display_window\n");
			tree_list = generate_trees();
			current_tree = 0;
		}
		else {
			glClearColor(0.3, 0.21, 0.38, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			delete_graphical_tree(current_tree_on_display);
		}
		printf("[%d]\n",current_tree);
		update_current_tree_on_display(window2, tree_list[current_tree]);
		current_tree++;
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			while (tree_list[current_tree] != NULL && is_AVL_tree(tree_list[current_tree]) == 0) current_tree++;
		}
	}
}

void glfwMainLoop() {
	while (glfwWindowShouldClose(window2) == GL_FALSE) {
		int width, height;

		glfwGetFramebufferSize(window2, &width, &height);
		glfwMakeContextCurrent(window2);
		render2(width, height);
		glfwSwapBuffers(window2);

		glfwWaitEvents();
	}
}

void init_OpenGL(int argc, char** argv) {
	glutInit(&argc, argv);
	if (glfwInit() == GL_FALSE) return 0;
	window2 = glfwCreateWindow(WINDOW_HIGHT, WINDOW_WIDTH, "display_window", NULL, NULL);

	glfwSetMouseButtonCallback(window2, mouse_callback);

}

