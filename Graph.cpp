#include "Graph.h"
#include <iostream>
#include "coordindex.h"
#include <ctype.h>

using std::cout;
using std::endl;
using std::to_string;

void Tile::setNeighbor(Tile* t, char dir) {
	int test = tolower(dir);
	if (test != 'n' && test != 's' && test != 'w' && test != 'e')//must be correct input
		cout << "Failed to set neighbor, must enter one of the following directions: n(north), s(south), w(west), e(east)" << endl;

	else {
		if (t == NULL) {//if wanting to remove, check to see if tile is in neighbors before removal
			if (neighbors.empty())
				cout << "Already empty" << endl;

			else {
				//find out which one to remove exactly
				if (test == 'n')
					t=getNorth();
				if (test == 's')
					t=getSouth();
				if (test == 'w')
					t=getWest();
				if (test == 'e')
					t=getEast();

				//removal from neighbors
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
					t = NULL;
				}
			}
		}//done removal

		else {//wanting to insert
			neighbors.push_back(t);
		}//done insert, now adjust pointers
		if (test == 'n')
			setNorth(t);
		if (test == 's')
			setSouth(t);
		if (test == 'w')
			setWest(t);
		if (test == 'e')
			setEast(t);
	}

}

string Tile::getStrNeighbors() {
	string output = to_string(getIndex())+": <";

	if(getNorth()==NULL)
		output += "N: None |";	
	else
		output += "N: " + to_string(getNorth()->getIndex())+" |";

	if (getSouth() == NULL)
		output += "S: None |";
	else
		output += "S: " + to_string(getSouth()->getIndex())+" |";

	if (getWest() == NULL)
		output += "W: None |";
	else
		output += "W: " + to_string(getWest()->getIndex())+" |";

	if (getEast() == NULL)
		output += "E: None |";
	else
		output += "E: " + to_string(getEast()->getIndex())+" |";

	output += ">   ";

	//now add the vector to the output
	string vect = "   |||   <";

	//this code here was meant to be used for a list to hold the neighbors, but i couldnt get it working 
	/*if (neighbors.empty())
		;
	else {
		iter = neighbors.begin();
		while (iter != neighbors.end()) {
			vect += to_string(*iter->getIndex());
			++iter;
		}
	}*/
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
		makeNeighbor(index, temp,'n');
	}

	if (index < totalTiles - sqrtOfTiles) {
		temp = &tiles.at(index + sqrtOfTiles);
		makeNeighbor(index, temp, 's');
	}
	if (index % sqrtOfTiles != 0) {
		temp = &tiles.at(index - 1);
		makeNeighbor(index, temp, 'w');
	}
	if ((index + 1) % sqrtOfTiles != 0) {
		temp = &tiles.at(index + 1);
		makeNeighbor(index, temp, 'e');
	}

}


void Map::makeNeighbor(int index, Tile *to_insert, char dir){
	int r = 0, c = 0;
	try{
		tiles.at(index).setNeighbor(to_insert, dir);
		/*//test code
		if (dir == 'n') {
			 r = indexToRownum(index, sqrtOfTiles);
			 c = indexToColnum(index, sqrtOfTiles);
			 tiles.at(coordToIndex(r - 1, c, sqrtOfTiles)).setNeighbor(tiles.at(index).getSouth(), 's');
		}//end test code*/
	}
	catch (std::out_of_range e){
		cout << "Out of range." << endl;
	}
}

void Map::removeNeighbor(int index, char dir){
	tiles.at(index).setNeighbor(NULL, dir);
}

//precond: since this makes a wall as the robot drives, it makes sense that the two indices should be right next to each other
//PRE COND: either the row or the columns must be equal
void Map::makeWall(int r1, int c1, int r2, int c2) {  //1:robot position   2: target position
	int target = coordToIndex(r2, c2, sqrtOfTiles);
	int orig = coordToIndex(r1, c1, sqrtOfTiles);
	int rowdif= r2 - r1;
	int coldif = c2 - c1;

	if (abs(rowdif + coldif) != 1)
		cout << "Invalid parameters to build wall" << endl;

	else if (rowdif == 0) { //when in the same row

		if (coldif == 1) {  //col2 leads by one, target to the east
			removeNeighbor(orig, 'e');//remove the neighbor of this tile from the east
			removeNeighbor(target, 'w'); //removes the neighbor of the target tile to the robot
		}

		if (coldif == -1) {  //col2 lags by one, target to the west
			removeNeighbor(orig, 'w');//remove the neighbor of this tile from the west
			removeNeighbor(target, 'e'); //removes the neighbor of the target tile to the robot
		}
	}

	else if (coldif == 0) { //when in the same col

		if (rowdif == 1) {  //row2 leads by one, target to the south
			removeNeighbor(orig, 's');
			removeNeighbor(target, 'n'); 
		}

		if (rowdif == -1) {  //row2 lags by one, target to the north
			removeNeighbor(orig, 'n');
			removeNeighbor(target, 's');
		}
	}

}

void Map::printAdjList(){
	for (int i = 0; i < totalTiles; i++)
		cout << tiles.at(i).getStrNeighbors() << endl;
	cout << "--------------------------  \n";
}
/*
KEY:
	--- and | are valid connections
	P is the robot
	A B C D are the ghostses
	* is a regular pellet
	@ is a power pellet
	% is a bonus(?)
	? are unknowns
	# is a wall
*/
void Map::printMap() {

	for (int i = 0; i < sqrtOfTiles; i++){ 
		string output1 = "", output2="";  //output1->current row  output2->southern connections
		
		if (i == 0) {
			for (int k = 0; k < sqrtOfTiles; k++) 
				output1 += "  "+to_string(k) + " ";
			
			cout << output1 << endl;
			output1 = "";
		} 
		for (int j = 0; j < sqrtOfTiles; j++) {
			if(j==0)
				output1 += to_string(i) + " ";

			if(tiles.at(j+i*(sqrtOfTiles)).getGhost()!=NULL)
				output1 += tiles.at(j + i*(sqrtOfTiles)).getGhost()->getSymb();
			else
				output1 += tiles.at(j+i*(sqrtOfTiles)).getEnt()->getSymb();
			//if above tile connection is null, wall
			if (tiles.at(j+i*sqrtOfTiles).getEast() == NULL)
				output1 += "   ";
			else
				output1 += "---";
			
			if (tiles.at(j+i*sqrtOfTiles).getSouth() == NULL)
				output2 += "    ";
			else
				output2 += "  | ";
		}
		cout << output1 << endl;
		cout << output2 << endl;
	}
}


vector<int> Map::BFS(int r1, int c1, int r2, int c2) {
	bool* visited= new bool[totalTiles]; //every tile is set to not visited at first
	list<int> queue; //a waitlist to visit neighbors
	list<int>::iterator it;
	vector<Tile*> temp;
	list<int> indices; //neighbor indices
	map<int, int> pairs;  //each pair will be (child, parent)
	vector<int> path;//final path

	int child = 0;
	int parent = coordToIndex(r1, c1, sqrtOfTiles);
	
	for (int i = 0; i < totalTiles; i++)
		visited[i] = false;

	//push the current tile into the visited pile, input value should be first pair into map
	visited[parent] = true;
	queue.push_back(parent);

	while (!queue.empty()) { //while there are still tiles to look through
		//take the current tile and add its neighbors to the end of the queue
		//cout << "queu" << endl;
		parent = queue.front();
		queue.pop_front();
		temp = tiles.at(parent).getNeighbors();
		//cout << parent << endl;

		for (int i = 0; i < temp.size(); i++) //gets the tile indices
			indices.push_back(temp.at(i)->getIndex());
		
		//filters out whats been visited or not, then adds to the queue and makes a pair
		for (it = indices.begin(); it != indices.end(); it++) {
			//cout << *it << endl;
		    if (!visited[*it]) {
				visited[*it] = true;
				queue.push_back(*it);
				pairs.insert({*it, parent});
			}

			//if found the desired tile, start tracing back
			if (*it == coordToIndex(r2, c2, sqrtOfTiles)) {
				child = *it;
			}				
		}

	}
	while (parent != coordToIndex(r1, c1, sqrtOfTiles)) {
		path.push_back(child);
		parent = pairs[child];
		path.push_back(parent);
		child = parent;
	}
	cout << "BFS from (" << r1 << ", " << c1 << ") to (" << r2 << ", " << c2 << ") " << endl;
	for (int i = 0; i < path.size(); i++) {
		cout << path.at(i) << ", ";
		if ((i + 2) % 2 == 1)
			cout << endl;
	}
	return path;
}

void Map::deleteTile(int r, int c){
	int temp = coordToIndex(r, c, sqrtOfTiles); //break the neighbors' connections to this	
	try {
		removeNeighbor(temp, 'e');//remove the neighbor of this tile from the east
		removeNeighbor(temp + 1, 'w'); //removes the neighbor of the target tile to the robot
		removeNeighbor(temp, 'w');//remove the neighbor of this tile from the west
		removeNeighbor(temp - 1, 'e'); //removes the neighbor of the target tile to the robot
		removeNeighbor(temp, 's');
		removeNeighbor(temp+sqrtOfTiles, 'n');
		removeNeighbor(temp, 'n');
		removeNeighbor(temp-sqrtOfTiles, 's');	

	}
	catch (std::out_of_range& e) {

	}
}

void Map::initialize() {
	tiles.at(4).setEnt(&pp);
	tiles.at(7).setEnt(&pp);
	makeWall(1, 0, 2, 0);
	makeWall(3, 0, 3, 1);
	makeWall(1, 1, 1, 2);
	makeWall(0, 3, 1, 3);
	makeWall(1, 2, 2, 2);
	makeWall(2, 3, 2, 4);
	makeWall(2, 1, 3, 1);
	makeWall(3, 2, 3, 3);
	makeWall(3, 3, 4, 3);
}

//will be returning vector after more details are worked out
vector<int> Map::look(int row, int col) { //returns vectors of tiles from N->E->S->W, divided by a NULL to represent new direction
	vector<int> scanning;
	int r = row, c = col, dest = 0;
	bool deadend = false;
	dest = coordToIndex(r, c, sqrtOfTiles);
	//north loop
	while (!deadend) {
		if (tiles.at(dest).getNorth() != NULL) {
			--r;
			dest = coordToIndex(r, c, sqrtOfTiles);
		}
		else
			deadend = true;
	}
	scanning.push_back(coordToIndex(row, c, sqrtOfTiles));
	scanning.push_back(dest);

//south loop
	deadend = false, r = row, c = col, dest = coordToIndex(row, col, sqrtOfTiles);//reset vars

	while (!deadend) {
		if (tiles.at(dest).getSouth() != NULL) {
			++r;
			dest = coordToIndex(r, c, sqrtOfTiles);
		}
		else
			deadend = true;
	}
	scanning.push_back(dest);


//east loop
	deadend = false, r = row, c = col, dest = coordToIndex(row, col, sqrtOfTiles);//reset vars

	while (!deadend) {
		if (tiles.at(dest).getEast() != NULL) {
			++c;
			dest = coordToIndex(r, c, sqrtOfTiles);
		}
		else
			deadend = true;
	}
	scanning.push_back(dest);

//WEST loop
	deadend = false, r = row, c = col, dest = coordToIndex(row, col, sqrtOfTiles);//reset vars

	while (!deadend) {
		if (tiles.at(dest).getWest() != NULL) {
			--c;
			dest = coordToIndex(r, c, sqrtOfTiles);
		}
		else
			deadend = true;
	}
	scanning.push_back(dest);


	/*cout << "Indices: ";
	for (int i = 0; i < scanning.size(); i++)
		cout <<scanning.at(i)<< ", ";
	cout << endl; */

	return scanning;
}
	
bool Map::hasDied(int r_pac, int c_pac, int r_ghost, int c_ghost) {
	int pacPos = coordToIndex(r_pac, c_pac, sqrtOfTiles);
	if (r_pac == r_ghost) {
		//cout << "same row" << endl;
		if (c_pac - c_ghost == 1) {//if the ghost is to the left, check if there is wall on the left
			if (getTileAt(pacPos).getWest() != NULL) {
				return true;
			}
		}
		if (c_pac - c_ghost == -1) {
			if (getTileAt(pacPos).getEast() != NULL)
				return true;
		}
	}

	if (c_pac == c_ghost) {
		//cout << "same col" << endl;
		if (r_pac - r_ghost == 1) {//if the ghost is to the north
			//cout << "ghost is above" << endl;
			if (getTileAt(pacPos).getNorth() != NULL)
				//cout << "RRRRRRRRRRR" << endl;
				return true;
		}
		if (r_pac - r_ghost == -1) {
			if (getTileAt(pacPos).getSouth() != NULL)
				return true;
		}
	}
	
	return false;
	
}