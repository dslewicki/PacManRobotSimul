#include "Graph.h"
#include <iostream>
#include "coordindex.h"

using std::cout;
using std::endl;
using std::to_string;


void Tile::addNeighbor(Tile* t) {
	neighbors.push_back(t);
}

void Tile::removeNeighbor(Tile* t) {
	if (neighbors.empty())
		cout << "Cannot remove, is already empty." << endl;
	else {
		iter = neighbors.begin();
		while (iter != neighbors.end()) {
			if (*iter == t)
				iter = neighbors.erase(iter);
			else
				++iter;
		}
	}
}

void Map::meetNGreet(){
	for (int i = 0; i < totalTiles; i++)
		visitNeighbors(i);
}



void Map::visitNeighbors(int index) {
	Tile* temp;

	if (index > sqrtOfTiles - 1) {
		temp = &tiles.at(index - sqrtOfTiles);
		addNeighbor(index, temp);
	}

	if (index < totalTiles - sqrtOfTiles) {
		temp = &tiles.at(index + sqrtOfTiles);
		addNeighbor(index, temp);
	}
	if (index % sqrtOfTiles != 0) {
		temp = &tiles.at(index - 1);
		addNeighbor(index, temp);
	}
	if ((index + 1) % sqrtOfTiles != 0) {
		temp = &tiles.at(index + 1);
		addNeighbor(index, temp);
	}
}


void Map::addNeighbor(int index, Tile *t){
	try{
		tiles.at(index).addNeighbor(t);
	}
	catch (std::out_of_range e){
		cout << "Out of range." << endl;
	}

}

void Map::removeNeighbor(int index, Tile* t){
	tiles.at(index).removeNeighbor(t);
}

string Map::printNeighbors(int index){
	string list = " ";

	for (int i = 0; i < tiles.at(index).getNeighbors().size(); i++){
		list += to_string(tiles.at(index).getNeighbors().at(i)->getIndex());
		list += ", ";
	}
	return list;
}

void Map::printAdjList(){
	for (int i = 0; i < totalTiles; i++)
		cout << to_string(tiles.at(i).getIndex()) << ":    <" << printNeighbors(i) << ">" << endl;
	cout << "--------------------------  \n";
}

void Map::test(){
	cout << indexToRownum(3, 4) << "  "<<indexToColnum(3, 4);
	//removeNeighbor(coordToIndex(2, 0, sqrtOfTiles), &tiles.at(3));
}