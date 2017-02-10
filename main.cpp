#include "Graph.h"
#include <iostream>
#include <conio.h>
#include "coordindex.h"

#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27

using std::cout;
using std::endl;

//todo:  implement an effective vision range for the "robot",[possibly redo the grid

int main(){

//building the maze, initialization
	const int MAP_SIZE = 25;
	Map world(MAP_SIZE); //this is the actual map
	Map memory(MAP_SIZE); //TEMPORARY: robot's memory
	bool visited[MAP_SIZE];//an array to keep track which tiles have been visited

	for (int i=0;i<MAP_SIZE;i++)
		visited[i] = 0;

	world.meetNGreet();
	world.initialize();

//testing the robot
	//assumes that pacbot's location is instantly known

	//variables for the controls
	Pac pac;
	world.setEntAt(0, &pac);
	memory.setEntAt(0, &pac);
	visited[0] = true;

	vector<int> scanned;
	Entity empty;
	int row = 0;
	int col = 0;
	int current = 0;
	int origin = 0;
	int KB_code = 0;
	int pv = 0;
	int total= 0;
	int time = 0;

	//variables for the look() results
	int r1, r2, c1, c2;

	//print out starting map
	scanned = world.look(row, col);
	world.printMap();
	memory.printMap();

	//controls
	while (KB_code != KB_ESCAPE) {
		KB_code = _getch();
		printf("KB_code = %i \n", KB_code);

		origin = coordToIndex(row, col, world.getSqrtTiles());

		//processes the controls
		switch (KB_code)
		{

		case KB_LEFT:
			--col;
			current = coordToIndex(row, col, world.getSqrtTiles());
			if (current == -1) {
				cout << "Out of bounds" << endl;
				++col;
				break;
			}
			//attempt a move, making sure to check if path exists in that direction
			if (world.getTileAt(current).getEast() != NULL) {
				//first get the point value from dest before moving
				pv = world.getEntAt(current)->getPntVal();
				world.setEntAt(current, &pac);
				//make the tile you just left marked as traveled
				world.setEntAt(origin, &empty);

				memory.setEntAt(current, &pac);
				memory.setEntAt(origin, &empty);
				//visited[origin] = true;
			}
			else ++col;


			break;

		case KB_RIGHT:
			++col;
			current = coordToIndex(row, col, world.getSqrtTiles());
			if (current == -1) {
				cout << "Out of bounds" << endl;
				--col;
				break;
			}

			//attempt a move, making sure to check if path exists in that direction
			if (world.getTileAt(current).getWest() != NULL) {
				//first get the point value from dest before moving
				pv = world.getEntAt(current)->getPntVal();
				world.setEntAt(current, &pac);
				//make the tile you just left marked as traveled
				world.setEntAt(origin, &empty);

				memory.setEntAt(current, &pac);
				memory.setEntAt(origin, &empty);
				//visited[current] = true;
			}
			else --col;

			break;

		case KB_UP:
			--row;
			current = coordToIndex(row, col, world.getSqrtTiles());
			if (current == -1) {
				cout << "Out of bounds" << endl;
				++row;
				break;
			}
			//attempt a move, making sure to check if path exists in that direction
			if (world.getTileAt(current).getSouth() != NULL) {
				//first get the point value from dest before moving
				pv = world.getEntAt(current)->getPntVal();
				world.setEntAt(current, &pac);
				//make the tile you just left marked as traveled
				world.setEntAt(origin, &empty);

				memory.setEntAt(current, &pac);
				memory.setEntAt(origin, &empty);
				//visited[current] = true;
			}
			else ++row;

			break;

		case KB_DOWN:
			++row;
			current = coordToIndex(row, col, world.getSqrtTiles());

			if (current == -1) {
				--row;
				cout << "Out of bounds" << endl;
				break;
			}
			//attempt a move, making sure to check if path exists in that direction
			if (world.getTileAt(current).getNorth() != NULL) {
				//first get the point value from dest before moving
				pv = world.getEntAt(current)->getPntVal();
				world.setEntAt(current, &pac);
				//make the tile you just left marked as traveled
				world.setEntAt(origin, &empty);

				memory.setEntAt(current, &pac);
				memory.setEntAt(origin, &empty);
				//visited[current] = true;
			}
			else --row;
			break;
		}//end of switch

		if (KB_code != 224){
			total += pv;
			++time;
		}

		//look and update the map
		scanned = world.look(row, col);
		//connect each path from each direction
		//places the found entities into the memory map
		//deriving information from look()

	//NORTH LOOK
		r1 = indexToRownum(scanned.at(0), world.getSqrtTiles());//robot position rownum
		r2 = indexToRownum(scanned.at(1), world.getSqrtTiles());//destination of north rownum
		c1 = indexToColnum(scanned.at(0), world.getSqrtTiles());//robot position colnum
		//cout << "r1= " << r1 << ", r2= " << r2 << ", c1= " << c1 << endl;
		//from r1 to r2, establish a valid path and identify any entities
		for (int i = 0; i <= r1 - r2; i++) {//e.g. from index 5 to index 2, subtract their rownums and count that many times
			int north = coordToIndex(r1 - i, c1, world.getSqrtTiles());//look at the tile above
			memory.setEntAt(north, world.getEntAt(north));//see whats inside
			Tile insert = world.getTileAt(north);
			if (visited[north] == false) {//if the robot has not moved here, pretend it does not see the other sides
				insert.setEast(NULL);
				insert.setWest(NULL);
				visited[scanned.at(0)] = true;
			}
			memory.setTileAt(north, insert);
		}

//SOUTH LOOK
		r1 = indexToRownum(scanned.at(0), world.getSqrtTiles());
		r2 = indexToRownum(scanned.at(2), world.getSqrtTiles());//row of south destination
		c1 = indexToColnum(scanned.at(0), world.getSqrtTiles());
		for (int i = 0; i <= r2 - r1; i++) {
			int south = coordToIndex(r1 + i, c1, world.getSqrtTiles());//look at the tile above
			memory.setEntAt(south, world.getEntAt(south));//see whats inside
			Tile insert = world.getTileAt(south);
			if (visited[south] == false) {//if the robot has not moved here, pretend it does not see the other sides
				insert.setEast(NULL);
				insert.setWest(NULL);
				visited[scanned.at(0)] = true;
			}
			memory.setTileAt(south, insert);
		}

//EAST LOOK
		r1 = indexToRownum(scanned.at(0), world.getSqrtTiles());
		c1 = indexToColnum(scanned.at(0), world.getSqrtTiles());
		c2 = indexToColnum(scanned.at(3), world.getSqrtTiles());//colnum of destination east
		for (int i = 0; i <= c2 - c1; i++) {
			int east = coordToIndex(r1, c1+i, world.getSqrtTiles());//look at the tile above
			memory.setEntAt(east, world.getEntAt(east));//see whats inside
			Tile insert = world.getTileAt(east);
			if (visited[east] == false) {//if the robot has not moved here, pretend it does not see the other sides
				insert.setNorth(NULL);
				insert.setSouth(NULL);
				visited[scanned.at(0)] = true;
			}
			memory.setTileAt(east, insert);
		}

//WEST LOOK
		r1 = indexToRownum(scanned.at(0), world.getSqrtTiles());
		c1 = indexToColnum(scanned.at(0), world.getSqrtTiles());
		c2 = indexToColnum(scanned.at(4), world.getSqrtTiles());//colnum of destination west
		for (int i = 0; i <= c1 - c2; i++) {
			int west = coordToIndex(r1, c1 - i, world.getSqrtTiles());//look at the tile above
			memory.setEntAt(west, world.getEntAt(west));//see whats inside
			Tile insert = world.getTileAt(west);
			if (visited[west] == false) {//if the robot has not moved here, pretend it does not see the other sides
				insert.setNorth(NULL);
				insert.setSouth(NULL);
				visited[scanned.at(0)] = true;
			}
			memory.setTileAt(west, insert);
		}

		cout << "Total Points: " << total << "	Time: " << time << endl;
		memory.printMap();
		//world.printMap();
	}

	return 0;
}