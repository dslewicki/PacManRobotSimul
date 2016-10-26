#include <GL/glew.h>
#include <GLFW/glfw3.h>
//^used to draw nice things
#include "Graph.h"






int main(){
	Graph grid(9);
	grid.build();
	grid.printGraph();
	grid.test();
	grid.printGraph();

	return 0;
}