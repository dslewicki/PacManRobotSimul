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
	//bool visited[MAP_SIZE];

	//for (int i=0;i<MAP_SIZE;i++)
		//visited[i] = 0;

	world.meetNGreet();
	world.initialize();

//testing the robot
	//assumes that pacbot's location is instantly known

	//variables for the controls
	Pac pac;
	world.setEntAt(0, &pac);
	memory.setEntAt(0, &pac);
	//visited[0] = true;

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

		//look and update the map
		scanned = world.look(row,col); 
		//connect each path from each direction
		//places the found entities into the memory map
		//deriving information from look()
		


		//every 2 numbers represent points from a direction, so the first 2 numbers are in the north direction
		r1=indexToRownum(scanned[0], world.getSqrtTiles());
		r2=indexToRownum(scanned[1], world.getSqrtTiles());
		c1 = indexToColnum(scanned[0], world.getSqrtTiles());

		//from r1 to r2, establish a valid path and identify any entities
		for (int i = r1-1; i > r2; --i) {
			int origin = coordToIndex(i+1, c1, world.getSqrtTiles());
			memory.setEntAt(origin, world.getEntAt(origin));
			memory.makeNeighbor((origin), world.getTileAt(origin).getNorth(), 'n');
		}
			//if the current scanned tile's ent has not changed, do not update
			/*if (memory.getTileAt(scanned.at(i).getIndex()).getEnt() == scanned.at(i).getEnt())
				;
			else
				memory.setTileAt(scanned.at(i).getIndex(), scanned.at(i));*/
		
		

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

		cout << "Total Points: " << total << "	Time: " << time << endl;
		memory.printMap();
		//world.printMap();
	}

	return 0;
}