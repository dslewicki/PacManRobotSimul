#include "Graph.h"
#include <iostream>

using std::cout;

//todo, make the removal sync with neighbors:: create another remove function
//find a way to display the grid

int main(){
//test code
	Map map(16);
	map.meetNGreet();
	map.makeWall(2, 0, 2, 1);
	map.printMap();
	map.printAdjList();

	return 0;
}