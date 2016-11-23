#include "Entities.h"
#include <vector>
#include <iterator>
#include <string>

using std::vector;
using std::string;

/*
Contains the definitions of the following classes:
	Tile: A tile of the map, contains an Entity value that can hold dots, Ghostses, SuperPac, etc.  Also holds a list of neighboring Tiles.
	Map: The actual map itself, which contains a vector(a better array) of Tiles, and can display what the hell is happening (eventually)
*/

class Tile{
	Entity *val;
	int indexVal;
	vector<Tile*> neighbors;
	vector<Tile*>::iterator iter;

public:
	Tile(int index):indexVal(index) {}
	Tile(Entity* ent,int index) : val(ent), indexVal(index){} //will be used when entities are ready

	int getIndex() { return indexVal; }
	vector<Tile*> getNeighbors() { return neighbors; }
	void addNeighbor(Tile*);
	void removeNeighbor(Tile*);
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
	
	//below two functions call tiles functions
	void addNeighbor(int, Tile*);
	void removeNeighbor(int, Tile*); 

	void BFS();  
	void printAdjList();
	void printMap();

	string printNeighbors(int);
	void test();  
};