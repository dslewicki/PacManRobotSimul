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

	Map world(16); //this is the actual map
	Map memory(16); //TEMPORARY: robot's memory
	bool visited[16];


	world.meetNGreet();
	world.initialize();
	world.deleteTile(1, 1);

//testing the robot
	//assumes that pacbot's location is instantly known
	Pac pac;
	world.setEntAt(0, &pac);
	memory.setEntAt(0, &pac);
	visited[0] = true;

	vector<Tile> scanned;
	Entity empty;
	int row = 0;
	int col = 0;
	int dest = 0;
	int origin = 0;

	int KB_code = 0;

	int pv = 0;
	int total= 0;
	int time = 0;

	//print out starting map
	scanned = world.look(row, col, visited);
	world.printMap();
	memory.printMap();
	//memory.printAdjList();

	//controls
	while (KB_code != KB_ESCAPE) {
		KB_code = _getch();
		printf("KB_code = %i \n", KB_code);

		origin = coordToIndex(row, col, world.getSqrtTiles());


		//look and update the map
		scanned = world.look(row,col,visited); 
		//connect each path from each direction
		int nullcount=0;
		//places the found entities into the memory map


		
		for (int i = 0; i < scanned.size(); i++){
			//if the current scanned tile's ent has not changed, do not update
			if (memory.getTileAt(scanned.at(i).getIndex()).getEnt() == scanned.at(i).getEnt())
				;
			else
				memory.setTileAt(scanned.at(i).getIndex(), scanned.at(i));
		}
		

		switch (KB_code)
		{

		case KB_LEFT:
			--col;
			dest = coordToIndex(row, col, world.getSqrtTiles());
			if (dest == -1) {
				cout << "Out of bounds" << endl;
				++col;
				break;
			}
			//attempt a move, making sure to check if path exists in that direction
			if (world.getTileAt(dest).getEast() != NULL) {
				//first get the point value from dest before moving
				pv = world.getEntAt(dest)->getPntVal();
				world.setEntAt(dest, &pac);
				//make the tile you just left marked as traveled
				world.setEntAt(origin, &empty);

				memory.setEntAt(dest, &pac);
				memory.setEntAt(origin, &empty);
				visited[dest] = true;
			}
			else ++col;


			break;

		case KB_RIGHT:
			++col;
			dest = coordToIndex(row, col, world.getSqrtTiles());
			if (dest == -1) {
				cout << "Out of bounds" << endl;
				--col;
				break;
			}

			//attempt a move, making sure to check if path exists in that direction
			if (world.getTileAt(dest).getWest() != NULL) {
				//first get the point value from dest before moving
				pv = world.getEntAt(dest)->getPntVal();
				world.setEntAt(dest, &pac);
				//make the tile you just left marked as traveled
				world.setEntAt(origin, &empty);

				memory.setEntAt(dest, &pac);
				memory.setEntAt(origin, &empty);
				visited[dest] = true;
			}
			else --col;

			break;

		case KB_UP:
			--row;
			dest = coordToIndex(row, col, world.getSqrtTiles());
			if (dest == -1) {
				cout << "Out of bounds" << endl;
				++row;
				break;
			}
			//attempt a move, making sure to check if path exists in that direction
			if (world.getTileAt(dest).getSouth() != NULL) {
				//first get the point value from dest before moving
				pv = world.getEntAt(dest)->getPntVal();
				world.setEntAt(dest, &pac);
				//make the tile you just left marked as traveled
				world.setEntAt(origin, &empty);

				memory.setEntAt(dest, &pac);
				memory.setEntAt(origin, &empty);
				visited[dest] = true;
			}
			else ++row;

			break;

		case KB_DOWN:
			++row;
			dest = coordToIndex(row, col, world.getSqrtTiles());

			if (dest == -1) {
				--row;
				cout << "Out of bounds" << endl;
				break;
			}
			//attempt a move, making sure to check if path exists in that direction
			if (world.getTileAt(dest).getNorth() != NULL) {
				//first get the point value from dest before moving
				pv = world.getEntAt(dest)->getPntVal();
				world.setEntAt(dest, &pac);
				//make the tile you just left marked as traveled
				world.setEntAt(origin, &empty);

				memory.setEntAt(dest, &pac);
				memory.setEntAt(origin, &empty);
				visited[dest] = true;
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