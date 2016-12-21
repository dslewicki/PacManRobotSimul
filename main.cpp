#include "Graph.h"
#include <iostream>

using std::cout;

//todo:  implement an effective vision range for the "robot",[possibly redo the grid

int main(){

	Map map(16);
	map.meetNGreet();


	map.makeWall(0, 0, 0, 1);
	map.makeWall(1, 0, 2, 0);
	map.makeWall(1, 1, 1, 2);
	map.makeWall(1, 2, 1, 3);
	map.makeWall(3, 0, 3, 1);
	map.makeWall(2, 2, 3, 2);
	
	map.BFS(3, 1, 1, 3);

	map.printMap();
	map.printAdjList();

	return 0;
}