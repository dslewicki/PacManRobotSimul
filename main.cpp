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

	//building the maze

	Map map(16);
	map.meetNGreet();

	/*map.makeWall(0, 0, 0, 1);
	map.makeWall(1, 0, 2, 0);
	map.makeWall(1, 1, 1, 2);
	map.makeWall(1, 2, 1, 3);
	map.makeWall(3, 0, 3, 1);
	map.makeWall(2, 2, 3, 2);*/
	
	map.deleteTile(1, 1);
	//map.BFS(3, 1, 1, 3);

	//map.printMap();
	//map.printAdjList();

	//testing the robot

	//assumes that pacbot's location is instantly known
	Pac pac;
	map.setEntAt(0, &pac);

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
	map.printMap();

	//controls
	while (KB_code != KB_ESCAPE) {
		KB_code = _getch();
		printf("KB_code = %i \n", KB_code);
		
		origin = coordToIndex(row, col, map.getSqrtTiles());

		switch (KB_code)
		{

		case KB_LEFT:
				--col;
				dest = coordToIndex(row, col, map.getSqrtTiles());
				if (dest == -1) {
					cout << "Out of bounds" << endl;
					++col;
					break;
				}
			//attempt a move, making sure to check if path exists in that direction
			if (map.getTileAt(dest).getEast() != NULL) {
				//first get the point value from dest before moving
				pv = map.getEntAt(dest)->getPntVal();
				map.setEntAt(dest, &pac);
				//make the tile you just left marked as traveled
				map.setEntAt(origin, &empty);
			}
			else ++col;


			break;

		case KB_RIGHT:
				++col;
				dest = coordToIndex(row, col, map.getSqrtTiles());
				if (dest == -1) {
					cout << "Out of bounds" << endl;
					--col;
					break;
				}

			//attempt a move, making sure to check if path exists in that direction
			if (map.getTileAt(dest).getWest() != NULL) {
				//first get the point value from dest before moving
				pv = map.getEntAt(dest)->getPntVal();
				map.setEntAt(dest, &pac);
				//make the tile you just left marked as traveled
				map.setEntAt(origin, &empty);
			}
			else --col;
				
			break;

		case KB_UP:
				--row;
				dest = coordToIndex(row, col, map.getSqrtTiles());
				if (dest == -1) {
					cout << "Out of bounds" << endl;
					++row;
					break;
				}
			//attempt a move, making sure to check if path exists in that direction
			if (map.getTileAt(dest).getSouth() != NULL) {
				//first get the point value from dest before moving
				pv = map.getEntAt(dest)->getPntVal();
				map.setEntAt(dest, &pac);
				//make the tile you just left marked as traveled
				map.setEntAt(origin, &empty);
			}
			else ++row;

			break;

		case KB_DOWN:
				++row;
				dest = coordToIndex(row, col, map.getSqrtTiles());
				
				if (dest == -1) {
					--row;
					cout << "Out of bounds" << endl;
					break;
				}
			//attempt a move, making sure to check if path exists in that direction
			if (map.getTileAt(dest).getNorth() != NULL) {
				//first get the point value from dest before moving
				pv = map.getEntAt(dest)->getPntVal();
				map.setEntAt(dest, &pac);
				//make the tile you just left marked as traveled
				map.setEntAt(origin, &empty);
			}
			else --row;


			break;
		}
		total += pv;
		++time;

		cout << "Total Points: " << total << "	Time: " << time << endl;
		map.printMap();
	}

	return 0;
}