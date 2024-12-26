#include"simulation_graphic.h"
#include"binary_tree.h"
#include"tree_analysis.h"
const char* file_name = "result.csv";

int main(int argc, char** argv) {
	char mode;
	printf("Select mode [a/b]\na - analize binary trees and make csv file.\nb - start graphical mode\n");
	if (scanf("%c", &mode) == EOF) {
		printf("invalid input\n");
		return 0;
    }
	if (mode == 'a') {
		report_trees(file_name);
	}
	else if(mode == 'b'){
		init_OpenGL(argc, argv);
		printf("Click display_window\n");
		glfwMainLoop();
		glfwTerminate();
	}
}