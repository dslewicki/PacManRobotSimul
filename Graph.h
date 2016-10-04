#include <vector>
#include "Entities.h"

/*
Graph will be represented as an adjacency list,
using std::vector, and possibly std::map, depending on
further progress.

Will be using intializer lists with constructor for faster initialization (or so I remember).  For those who aren't familiar with the syntax,

public classConstructor(){		is the same as			public classConstructor():this(that){}
this=that;						-------------->
}



*/


class Vertex{
	SuperPac *val;//set to null if there exists no entity in this space


public:
	Vertex(): val(NULL){}
		//neighbors=new vector<Vertex>

};

class Graph{
	int totalVertices; //number of vertices, should be 100
	std::vector<std::vector<Vertex>> neighbors;

public:
	Graph(int numOfVertices): neighbors(numOfVertices){}
	void addEdge();
	void BFS();  //breadth-first search, might be adjusted to accommodate for more general distance appromixation

};