#include "Graph.h"
#include <iostream>
#include "coordindex.h"
#include <ctype.h>

using std::cout;
using std::endl;
using std::to_string;

void Tile::setNeighbor(Tile* t, char dir) {
	int test = tolower(dir);
	if (test != 'u' && test != 'd' && test != 'l' && test != 'r')//must be correct input
		cout << "Failed to set neighbor, must enter one of the following directions: u(up), d(down), l(left), r(right)" << endl;

	else {
		if (t == NULL) {//if wanting to remove, check to see if tile is in neighbors before removal
			if (neighbors.empty())
				cout << "Already empty" << endl;

			else {

				//find out which one to remove exactly
				if (test == 'u')
					t=getUp();
				if (test == 'd')
					t=getDown();
				if (test == 'l')
					t=getLeft();
				if (test == 'r')
					t=getRight();

				if (t == NULL)//if trying to remove a tile that doesnt exist, dont
					cout << "Tile does not exist, cannot remove" << endl;

				else {//begin search thru vector to remove that tile			
					iter = neighbors.begin();
					while (iter != neighbors.end()) {
						if (*iter == t)
							iter = neighbors.erase(iter);
						else
							++iter;
					}
				}
			}
		}//done removal

		else {//wanting to insert
			neighbors.push_back(t);
		}//done insert

		//adjust the pointers
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

string Tile::getStrNeighbors() {
	string output = to_string(getIndex())+": <";

	if(getUp()==NULL)
		output += "Up: None |";	
	else
		output += "Up: " + to_string(getUp()->getIndex())+" |";

	if (getDown() == NULL)
		output += "Down: None |";
	else
		output += "Down: " + to_string(getDown()->getIndex())+" |";

	if (getLeft() == NULL)
		output += "Left: None |";
	else
		output += "Left: " + to_string(getLeft()->getIndex())+" |";

	if (getRight() == NULL)
		output += "Right: None |";
	else
		output += "Right: " + to_string(getRight()->getIndex())+" |";

	output += ">   ";

	//now add the vector to the output
	string vect = "   |||   <";
	for (int i = 0; i < getNeighbors().size(); i++) {
		vect += to_string(getNeighbors().at(i)->getIndex())+", ";
	}
	vect += ">";
	output += vect;

	return output;
}

void Map::meetNGreet(){
	for (int i = 0; i < totalTiles; i++)
		visitNeighbors(i);
}


void Map::visitNeighbors(int index) { //connects all the tiles to their respective neighbors, map is assumed wall-less at first
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
		cout << tiles.at(i).getStrNeighbors() << endl;
	cout << "--------------------------  \n";
}

void Map::test(){//put test functions in here
	removeNeighbor(coordToIndex(2, 0, sqrtOfTiles), 'd');
}