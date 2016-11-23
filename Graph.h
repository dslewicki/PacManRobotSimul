#include "Entities.h"
#include <vector>
#include <iterator>
#include <string>

using std::vector;
using std::string;

/*
Contains the definitions of the following classes:
	Tile: A tile of the map, contains an Entity value that can hold dots, Ghostses, SuperPac, etc.  Also holds pointers to nearby tiles.
	Map: The actual map itself, which contains a vector(a better array) of Tiles, and can display what the hell is happening (eventually)
*/

class Tile{
	Entity *val;
	int indexVal;
	Tile* up;
	Tile* down;
	Tile* left;
	Tile* right;
	vector<Tile*> neighbors;
	vector<Tile*>::iterator iter;  //navigates thru the vector

public:
	Tile(int index):indexVal(index) {}
	Tile(Entity* ent,int index) : val(ent), indexVal(index){} //will be used when entities are ready

	int getIndex() { return indexVal; }
	vector<Tile*> getNeighbors() { return neighbors; }

	Tile* getUp()		{ return up; }
	Tile* getDown()		{ return down; }
	Tile* getLeft()		{ return left; };
	Tile* getRight()	{ return right; };

	void setUp(Tile* t) { up = t; }
	void setDown(Tile* t) { down = t; }
	void setLeft(Tile* t) { left = t; }
	void setRight(Tile* t) { right = t; }

	void setNeighbor(Tile*, char);
	string getStrNeighbors();
	//void removeNeighbor(Tile*, char);
};

class Map{
	int totalTiles;
	int sqrtOfTiles;  //effectively the length/width of the grid, this will be used in all sorts of calculations
	vector<Tile> tiles;
	void visitNeighbors(int); //designed tile connects to nearby tiles and adds to neighbors list

public://the constructor sets up each tile, but does not "connect" them (no neighbors detected)
	Map(int numOfVertices) :totalTiles(numOfVertices), sqrtOfTiles(sqrt(numOfVertices)) {
		tiles.reserve(totalTiles);
		for (int i = 0; i < numOfVertices; i++) {
			Tile insert(i);
			tiles.push_back(insert);
		}
	} 

	void meetNGreet(); //every tile in the map connects to their neighbors
	
	void addNeighbor(int, Tile*, char); //adds a neighbor(Tile*) to tiles(int) and specifies where neighbor is(char)
	void removeNeighbor(int, char); //which direction should i cut off?

	void BFS();  //finds the shortest path to wherever
	void printAdjList();  //prints out the adjacency list
	void printMap(); //will be used in the gui(?)

	void test();  //just a function for testing
};