#include "Graph.h"
#include <iostream>
#include <conio.h>
#include "coordindex.h"

#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27
#define KB_TAB 15
#define KB_SPACE 32

using std::cout;
using std::endl;

//todo: remake the grid, and implement a way to mirror one side of the map to the other

int main(){

//building the maze, initialization
	const int MAP_SIZE = 25;
	Map world(MAP_SIZE); //this is the actual map
	Map memory(MAP_SIZE); //TEMPORARY: robot's memory
	Map& toWorld = world;
	bool visited[MAP_SIZE];//an array to keep track which tiles have been visited

	for (int i=0;i<MAP_SIZE;i++)
		visited[i] = 0;

	world.meetNGreet();
	world.initialize();

//testing the robot
	//variables for the controls
	//sets up the pacbot and the ghostbots locations

	//original position indices
	int pacPosOrig = 0,
		g1PosOrig = 14;

	//rows and columns
	int r_pac = indexToRownum(pacPosOrig, world.getSqrtTiles());
	int c_pac = indexToColnum(pacPosOrig, world.getSqrtTiles());
	int r_ghost = indexToRownum(g1PosOrig, world.getSqrtTiles());
	int c_ghost = indexToColnum(g1PosOrig, world.getSqrtTiles());

//robots being placed in the maps
	Pac pac;
	world.setEntAt(pacPosOrig, &pac);
	memory.setEntAt(pacPosOrig, &pac);
	visited[0] = true;

	//when a ghost is initialized, make sure to put it in the memory map as well
	Ghost g1;
	g1.setSymb('A');
	world.setGhostAt(g1PosOrig, &g1);
	memory.setGhostAt(g1PosOrig, &g1);

	//vector<int> scanned;
	Entity empty;
	int row = 0,
		col = 0,
		current = 0,
		origin = 0,
		KB_code = 0,
		pv = 0,
		total = 0,
		time = 0,
		lives = 3;
	bool gameover = false;
	

	//variables for the look() results
	//int r1, r2, c1, c2;

	//print out starting map
	memory.look(toWorld, world.look(row, col), visited);//scanned = world.look(row, col);
	world.printMap();
	memory.printMap();

	//controls

	while (KB_code != KB_ESCAPE && !gameover) {
		KB_code = _getch();//scans the keyboard input as an int
		if (KB_code == 224)
			KB_code = _getch();//need to call it twice or it wont work properly (im serious)
		printf("KB_code = %i \n", KB_code);

		origin = coordToIndex(row, col, world.getSqrtTiles());
		//processes the controls
		switch (KB_code)
		{

		case KB_SPACE://increment simulation time by 1, basically just tap and watch
 /* the actual pacman wave phases
 Scatter for 7 seconds, then Chase for 20 seconds.
 Scatter for 7 seconds, then Chase for 20 seconds.
Scatter for 5 seconds, then Chase for 20 seconds.
 Scatter for 5 seconds, then switch to Chase mode permanently.
 */
			if (time == 0 || time == 27 || time == 54 || time == 79)
				;//set the movephase to scatter
	   else if (time == 7 || time == 34 || time == 59 || time == 84)
				;//set the movephase to chase
			break;

		//cases for the arrows are manual movements
		case KB_LEFT:
			--col;
			current = coordToIndex(row, col, world.getSqrtTiles());
			if (current == -1) {
				cout << "Out of bounds" << endl;
				++col;
				break;
			}

			//TODO: update the ghost's/pacbot location(r,c) and make it appear on the map
			//attempt a move, making sure to check if path exists in that direction
			if (world.getTileAt(current).getEast() != NULL) {
				//first get the point value from dest before moving
				pv = world.getEntAt(current)->getPntVal();
				world.setEntAt(current, &pac);
				//make the tile you just left marked as traveled
				world.setEntAt(origin, &empty);

				//the ghost location is known at all times
				//memory.setGhostAt()
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
		}//end of controls
	
		if (KB_code != 224) {//TODO: cause of bug 001, adjust if clause
			total += pv;
			++time;
			//}

			r_pac = indexToRownum(current, world.getSqrtTiles());
			c_pac = indexToColnum(current, world.getSqrtTiles());

			cout << r_pac << ", " << c_pac << " : " << r_ghost << ", " << c_ghost << endl;
			if (world.hasDied(r_pac, c_pac, r_ghost, c_ghost)) {
				--lives;
				//remove all the ghost from its current position and places it back into the original
			}
		}
		if (lives == 0)
			gameover = true;

		//look and update the map
		memory.look(toWorld, world.look(row, col), visited);//scanned = world.look(row, col);
		cout << "Total Points: " << total << "	Time: " << time << "	Lives: "<< lives<<endl;
		memory.printMap();
		//world.printMap();
	}//end of game

	cout << "\a Total Points: " << total << "	Time: " << time << "	Lives: " << lives << endl;
	cout << "L O S E R " << endl;

	return 0;
}