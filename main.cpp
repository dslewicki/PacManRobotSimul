//^used to draw nice things
#include "Graph.h"




int main(){
	//GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	Graph grid(100);
	grid.build();
	grid.printAdjList();
	grid.printGrid();
	return 0;
}