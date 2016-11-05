#include "Graph.h"
#include <iostream>
#include "coordindex.h"

using std::cout;
using std::endl;
using std::to_string;


/*
Will visit each vertex and add neighbors to its neighborlist
if the vertex is in the top row, do not add upper neighbors
if the vertex is on the sides, do not add that side neighbor
if the vertex is on the bottom, do not add bottom neighbors
ALTERNATIVELY: GET GUD AND USE TRY CATCH TO ALLOW
*/

//Will visit each vertex and add neighbors to its neighborlist
void Graph::build(){
	for (int i = 0; i < totalVertices; i++)
		addNeighbors(i);
}



void Graph::addNeighbors(int index){ //connects tile(index) to its neighbors
	//sqrt of Vertices are the "new rows" EX: Of 9 vertices, the beginning index of each row is 0,3,6
	//Eg. 3x3, 0,3,6 are the first indices in their row

		//add the top and bottom neighbors
		if (index > keynum - 1)//if the vertex is in the top row, do not add upper neighbors
		addEdge(index, vertices.at(index - keynum).front());

		if (index < totalVertices - keynum)//if the vertex is on the bottom, do not add bottom neighbors
		addEdge(index, vertices.at(index + keynum).front());

		//add the side neighbors
		if (index % keynum != 0)//if the vertex is on the left side, do not add the left neighbors
		addEdge(index, vertices.at(index-1).front());

		if ((index + 1) % keynum != 0)//if the vertex is on the right side, do not add right neighbors
		addEdge(index, vertices.at(index+1).front());
			
}

//adds a specified edge to a vertex
void Graph::addEdge(int index, Vertex* v){
	try{
		vertices.at(index).push_back(v);
	}
	catch (std::out_of_range e){
		cout << "Out of range." << endl;
	}

}

void Graph::removeEdge(int index, Vertex* v){
	if (vertices.at(index).empty())
		cout << "Cannot remove, is already empty." << endl;
	else{
		iter = vertices.at(index).begin();
		while (iter != vertices.at(index).end()){
			//move iterator so isnt lost at deletion
			if (*iter == v)
				iter = vertices.at(index).erase(iter);
			
			else
				++iter;//advance(iter, 1);
		}
	}

}

string Graph::printNeighbors(int index){
	string list = " ";

	for (int i = 1; i < vertices.at(index).size(); i++){
		list += to_string(vertices.at(index).at(i)->getIdnty());
		list += ", ";
	}
	return list;
}

void Graph::printAdjList(){
	for (int i = 0; i < totalVertices; i++)
		cout << to_string(vertices.at(i).front()->getIdnty()) << ":    <" << printNeighbors(i) << ">" << endl;
	cout << "--------------------------  \n";
}
/*
void Graph::printGridSquare(){
		cout << endl;
		for (int x = 0; x <= keynum; x++) {
			cout << "   | ";
		}
		cout << endl;
		for (int x = 0; x <= keynum; x++) {
			cout << "---| ";
		}
		cout << endl;
}

void Graph::printGrid(){
		int row = 0;
		cout << endl << "TEST GRID:" << endl << endl;
		for (int r = 0; r <= keynum; r++) {
			for (int c = 0; c <= keynum; c++) {
				if ((r == 0) && (c != 0))
					cout << " " << c - 1 << " | ";
				else if ((c == 0) && (r != 0)){
					row = row + r - 1;
					cout << " " << row << " | ";
					row = row - r + 1;
				}
				else cout << " " << " " << " | ";
			}
			printGridLine();
		}
		cout << endl << endl;
	
}
*/
void Graph::test(){
	addEdge(coordToIndex(2, 0, keynum), vertices.at(0).back());
}