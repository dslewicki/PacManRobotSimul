#include "Graph.h"
#include <iostream>
#include "coordindex.h"
#include <ctype.h>

using std::cout;
using std::endl;
using std::to_string;

void Tile::setNeighbor(Tile* t, char dir) {
	int test = tolower(dir);
	if (test != 'u' && test != 'd' && test != 'l' && test != 'r')
		cout << "Failed to set neighbor, must enter one of the following directions: u(up), d(down), l(left), r(right)" << endl;

	else {
		if (test == 'u')
			setUp(t);
		if (test == 'd')
			setDown(t);
		if (test == 'l')
			setLeft(t);
		if (test == 'r')
			setRight(t);
	}
}

string Tile::getNeighbors() {
	string neighbors = to_string(getIndex())+": <";

	if(getUp()==NULL)
		neighbors += "Up: None |";	
	else
		neighbors += "Up: " + to_string(getUp()->getIndex())+" |";

	if (getDown() == NULL)
		neighbors += "Down: None |";
	else
		neighbors += "Down: " + to_string(getDown()->getIndex())+" |";

	if (getLeft() == NULL)
		neighbors += "Left: None |";
	else
		neighbors += "Left: " + to_string(getLeft()->getIndex())+" |";

	if (getRight() == NULL)
		neighbors += "Right: None |";
	else
		neighbors += "Right: " + to_string(getRight()->getIndex())+" |";

	neighbors += ">";

	return neighbors;
}

void Map::meetNGreet(){
	for (int i = 0; i < totalTiles; i++)
		visitNeighbors(i);
}


void Map::visitNeighbors(int index) {
	Tile* temp;

	if (index > sqrtOfTiles - 1) {
		temp = &tiles.at(index - sqrtOfTiles);
		addNeighbor(index, temp,'u');
	}

	if (index < totalTiles - sqrtOfTiles) {
		temp = &tiles.at(index + sqrtOfTiles);
		addNeighbor(index, temp, 'd');
	}
	if (index % sqrtOfTiles != 0) {
		temp = &tiles.at(index - 1);
		addNeighbor(index, temp, 'l');
	}
	if ((index + 1) % sqrtOfTiles != 0) {
		temp = &tiles.at(index + 1);
		addNeighbor(index, temp, 'r');
	}

}


void Map::addNeighbor(int index, Tile *t, char dir){
	try{
		tiles.at(index).setNeighbor(t, dir);
	}
	catch (std::out_of_range e){
		cout << "Out of range." << endl;
	}

}

void Map::removeNeighbor(int index, char dir){
	tiles.at(index).setNeighbor(NULL, dir);
}


void Map::printAdjList(){
	for (int i = 0; i < totalTiles; i++)
		cout << tiles.at(i).getNeighbors() << endl;
	cout << "--------------------------  \n";
}

void Map::test(){
	cout << indexToRownum(3, 4) << "  "<<indexToColnum(3, 4);
	//removeNeighbor(coordToIndex(2, 0, sqrtOfTiles), &tiles.at(3));
}