#include"simulation_graphic.h"
#include"binary_tree.h"
#include"tree_analysis.h"

int main(int argc, char** argv) {
	int mode = 0;
	scanf("%d", &mode);
	if (mode == 1) {
		report_trees("result2.csv");
	}
	else {
		init_OpenGL(argc, argv);
		glfwMainLoop();
		glfwTerminate();
	}
}